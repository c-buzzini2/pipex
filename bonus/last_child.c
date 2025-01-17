/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/17 16:26:44 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include "pipex_bonus.h"

void	ft_last_child(char *argv[], char *envp[], int pipefd[], int exctd_cmds)
{
	int		outfile;

//if heredoc, exectd++ -
	close(pipefd[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Error opening outfile");
		exit(1);
	}
	if (dup2(outfile, STDOUT_FILENO) < 0)
	{
		perror("Error duplicating outfile");
		exit(1);
	}
	close(outfile);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("Error duplicating reading end of pipe");
		exit(1);
	}
	close(pipefd[0]);
	ft_execute(argv[exctd_cmds + 2], envp);
}

int	ft_last_fork(char *argv[], char *envp[], int *pipes[], int exctd_cmds)
{
	int		id2;
//	int		exitstatus2;
	int		pipe_index;

	pipe_index = exctd_cmds - 1;
	id2 = fork();
	if (id2 == -1)
	{
		perror("Error in the second fork");
		exit(1);
	}
	if (id2 == 0)
	{
		ft_last_child(argv, envp, pipes[pipe_index], exctd_cmds);
	}
/* 	waitpid(id2, &exitstatus2, 0);
	free(pipes[pipe_index]);
	if (WIFEXITED(exitstatus2) && WEXITSTATUS(exitstatus2) != 0)
		return (WEXITSTATUS(exitstatus2)); */
	return (0);
}