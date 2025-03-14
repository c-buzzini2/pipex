/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/14 13:29:25 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "pipex.h"

void	ft_last_child(t_pipex *pipex, int prev_pipe[]) // TOO MANY LINES
{
	int		outfile;
	int		i;

	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipex->fd[i][1]);
		if (pipex->fd[i] != prev_pipe)
			close(pipex->fd[i][0]);
		i++;
	}
	outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Error opening outfile");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	if (dup2(outfile, STDOUT_FILENO) < 0)
	{
		perror("Error duplicating outfile");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	close(outfile);
	if (dup2(prev_pipe[0], STDIN_FILENO) < 0)
	{
		perror("Error duplicating reading end of pipe");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	close(prev_pipe[0]);
	ft_deallocate_pipes(pipex->fd);
	ft_execute(pipex->cmds[pipex->cmd_count - 1], pipex->envp);
}
