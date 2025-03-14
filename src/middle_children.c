/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/14 14:50:31 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_pipes_middle(t_pipex *pipex, int prev_pipe[], int next_pipe[])
{
	int		i;

	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		if (pipex->fd[i] != next_pipe)
			close(pipex->fd[i][1]);
		if (pipex->fd[i] != prev_pipe)
			close(pipex->fd[i][0]);
		i++;
	}
}

void	ft_middle_child(t_pipex *pipex, int prev_pipe[], int next_pipe[],
					int forks)
{
	ft_close_pipes_middle(pipex, prev_pipe, next_pipe);
	if (dup2(prev_pipe[0], STDIN_FILENO) < 0)
	{
		perror("Error duplicating reading end of pipe");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	if (dup2(next_pipe[1], STDOUT_FILENO) < 0)
	{
		perror("Error duplicating writing end of pipe");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	close(prev_pipe[0]);
	close(next_pipe[1]);
	ft_deallocate_pipes(pipex->fd);
	ft_execute(pipex->cmds[forks], pipex->envp);
}
