/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 15:51:24 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_middle_child(t_pipex *pipex, int prev_pipe[], int next_pipe[])
{
	
}

void	ft_last_child(t_pipex *pipex, int pipefd[])
{
	int		outfile;

	close(pipefd[1]);
	outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Error opening outfile");
		exit(errno);
	}
	if (dup2(outfile, STDOUT_FILENO) < 0)
	{
		perror("Error duplicating outfile");
		exit(errno);
	}
	close(outfile);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("Error duplicating reading end of pipe");
		exit(errno);
	}
	close(pipefd[0]);
	ft_execute(pipex->cmds[pipex->cmd_count - 1], pipex->envp);
}