/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/16 14:19:19 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *cmd, char *envp[])
{
	char	*args[4];

	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve("/bin/sh", args, envp);
}

int	ft_second_fork(char *argv[], char *envp[], int pipefd[])
{
	int		id2;
	int		exitstatus2;

	id2 = fork();
	if (id2 == -1)
	{
		perror("Error in the second fork");
		exit(1);
	}
	if (id2 == 0)
	{
		ft_last_child(argv, envp, pipefd);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(id2, &exitstatus2, 0);
	if (WIFEXITED(exitstatus2) && WEXITSTATUS(exitstatus2) != 0)
		return (WEXITSTATUS(exitstatus2));
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	int		estatus;
	int		commands;

	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments.", 1);
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Error opening pipe");
		exit(1);
	}
	commands = 0;
	ft_first_fork(argv, envp, pipefd);
	estatus = ft_second_fork(argv, envp, pipefd);
	return (estatus);
}
