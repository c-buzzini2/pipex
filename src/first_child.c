/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/14 13:45:28 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "pipex.h"

void	ft_first_child2(t_pipex *pipex)
{
	if (dup2(pipex->fd[0][1], STDOUT_FILENO) < 0)
	{
		perror("Error duplicating writing end of pipe");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	close(pipex->fd[0][1]);
	ft_deallocate_pipes(pipex->fd);
	ft_execute(pipex->cmds[0], pipex->envp);
}

void	ft_first_child(t_pipex *pipex) //TOO MANY LINES
{
	int		infile;
	int		i;

	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipex->fd[i][0]);
		if (i != 0)
			close(pipex->fd[i][1]);
		i++;
	}
	infile = open(pipex->infile, O_RDONLY);
	if (infile == -1)
	{
		perror("Error opening infile");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	if (dup2(infile, STDIN_FILENO) < 0)
	{
		perror("Error duplicating infile");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
	close(infile);
	ft_first_child2(pipex);
}

