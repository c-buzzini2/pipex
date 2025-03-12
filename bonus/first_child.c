/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 15:46:37 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_first_child(t_pipex *pipex, int pipefd[])
{
	int		infile;

	close(pipefd[0]);
	infile = open(pipex->infile, O_RDONLY);
	if (infile == -1)
	{
		perror("Error opening infile");
		exit(errno);
	}
	if (dup2(infile, STDIN_FILENO) < 0)
	{
		perror("Error duplicating infile");
		exit(errno);
	}
	close(infile);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		perror("Error duplicating writing end of pipe");
		exit(errno);
	}
	close(pipefd[1]);
	ft_execute(pipex->cmds[0], pipex->envp);
}

