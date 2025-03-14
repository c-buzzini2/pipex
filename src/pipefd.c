/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipefd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:44:18 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/14 13:31:47 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "pipex.h"

void	ft_deallocate_pipes(int **pipefd)
{
	int		i;

	i = 0;
	while (pipefd[i] != NULL)
		free(pipefd[i++]);
	free(pipefd);
}

static void	ft_create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		pipex->fd[i] = malloc (2 * sizeof(int));
		if (!pipex->fd[i])
		{
			perror("Error allocating pipe");
			ft_deallocate_pipes(pipex->fd);
			exit(errno);
		}
		if (pipe(pipex->fd[i]) == -1)
		{
			perror("Error opening pipe");
			ft_deallocate_pipes(pipex->fd);
			exit(errno);
		}
		i++;
	}
}

void	ft_create_arr_pipes(t_pipex *pipex)
{
	pipex->fd = malloc((pipex->cmd_count) * sizeof(int *));
	if (!pipex->fd)
	{
		perror("Error allocating array of pipes");
		exit(errno);
	}
	ft_create_pipes(pipex);
	pipex->fd[pipex->cmd_count - 1] = NULL;
}
