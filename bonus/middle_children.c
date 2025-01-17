/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/17 16:26:39 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include "pipex_bonus.h"

void	ft_middle_children(char *argv[], char *envp[], int *pipes[], int exctd_cmds)
{
	int		prev_pipe_index;
	int		next_pipe_index;
//if heredoc, exectd++ 

	prev_pipe_index = exctd_cmds - 1;
	next_pipe_index = exctd_cmds;
	close(pipes[prev_pipe_index][1]);
	close(pipes[next_pipe_index][0]);
	if (dup2(pipes[prev_pipe_index][0], STDIN_FILENO) < 0)
	{
		perror("Error duplicating reading end of pipe");
		exit(1);
	}
	if (dup2(pipes[next_pipe_index][1], STDOUT_FILENO) < 0)
	{
		perror("Error duplicating writing end of pipe");
		exit(1);
	}
	close(pipes[prev_pipe_index][0]);
	close(pipes[next_pipe_index][1]);
	ft_execute(argv[exctd_cmds + 2], envp);
}

int	ft_middle_fork(char *argv[], char *envp[], int *pipes[], int exctd_cmds)
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
		ft_middle_children(argv, envp, pipes, exctd_cmds);
	}
/* 	waitpid(id2, &exitstatus2, 0);
	free(pipes[pipe_index]);
	if (WIFEXITED(exitstatus2) && WEXITSTATUS(exitstatus2) != 0)
		return (WEXITSTATUS(exitstatus2)); */
	return (0);
}