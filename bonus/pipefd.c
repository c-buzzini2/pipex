/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipefd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:44:18 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 15:17:22 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_deallocate_pipes(int **pipefd, int i)
{
	while (i >= 0)
		free(pipefd[i--]);
	free(pipefd);
}

static void	 ft_create_pipes(t_pipex *pipex, int **pipefd)
{
	int	i;
	
	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		pipefd[i] = malloc (2 * sizeof(int));
		if (!pipefd[i])
		{
			perror("Error allocating pipe"); //number of the pipe to debug?
			ft_deallocate_pipes(pipefd, i - 1);
			exit(errno);
		}
		if (pipe(pipefd[i]) == -1)
		{
			perror("Error opening pipe");
			ft_deallocate_pipes(pipefd, i);
			exit(errno);
		}
		i++;
	}
}

int	 **ft_create_arr_pipes(t_pipex *pipex)
{
	int		**pipefd;

	pipefd = malloc((pipex->cmd_count - 1) * sizeof(int[2]));
	if (!pipefd)
	{
		perror("Error allocating array of pipes");
		exit(errno);
	}
	ft_create_pipes(pipex, pipefd);
	return (pipefd);
}