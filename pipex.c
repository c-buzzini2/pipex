/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/23 14:57:06 by cbuzzini         ###   ########.fr       */
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

int	ft_fork(char *argv[], char *envp[], int pipefd[])
{
	int		id1;
	int		id_last;
	int		estatus;

	id1 = fork();
	id_last = -2;
	if (id1 != 0)
		id_last = fork();
	if (id1 == -1 || id_last == -1)
	{
		perror("Error in the fork");
		exit(errno);
	}
	if (id1 == 0)
		ft_first_child(argv, envp, pipefd);
	if (id_last == 0)
		ft_last_child(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id_last, &estatus, 0);
	if (WIFEXITED(estatus))
		return (WEXITSTATUS(estatus));
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	int		estatus;

	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments.", 1);
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Error opening pipe");
		exit(errno);
	}
	estatus = ft_fork(argv, envp, pipefd);
	return (estatus);
	}
