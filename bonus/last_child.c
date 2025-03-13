/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/13 14:11:08 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_first_child(t_pipex *pipex, int next_pipe[], int **pipefd)
{
	int		infile;

	//close(next_pipe[0]);
	infile = open(pipex->infile, O_RDONLY); // infile correct?
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
	if (dup2(next_pipe[1], STDOUT_FILENO) < 0)
	{
		perror("Error duplicating writing end of pipe");
		exit(errno);
	}
	//close(next_pipe[1]);
	int i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	ft_deallocate_pipes(pipefd, pipex->cmd_count - 1);
	ft_execute(pipex->cmds[0], pipex->envp); //indices correct?
}


void	ft_middle_child(t_pipex *pipex, int prev_pipe[], int next_pipe[], int forks, int **pipefd)
{
	
	int i;
    for (i = 0; i < pipex->cmd_count - 1; i++) {
        // Skip the pipes we need
        if (i == forks - 1) {
            close(prev_pipe[1]); // Close write end of previous pipe
        } else if (i == forks) {
            close(next_pipe[0]); // Close read end of next pipe
        } else if (i < pipex->cmd_count - 1) {
            // Close both ends of pipes we don't need
            close(pipefd[i][0]);
            close(pipefd[i][1]);
        }
    }
	
	//close(prev_pipe[1]);
	//close(next_pipe[0]);
	if (dup2(prev_pipe[0], STDIN_FILENO) < 0)
	{
		perror("Error duplicating reading end of pipe");
		exit(errno);
	}
	if (dup2(next_pipe[1], STDOUT_FILENO) < 0)
	{
		perror("Error duplicating writing end of pipe");
		exit(errno);
	}
	close(prev_pipe[0]);
	close(next_pipe[1]);
	ft_deallocate_pipes(pipefd, pipex->cmd_count - 1);
	ft_execute(pipex->cmds[forks], pipex->envp);
}

void	ft_last_child(t_pipex *pipex, int prev_pipe[], int **pipefd)
{
	int		outfile;

	//close(prev_pipe[1]);
	outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); //outfile correct?
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
	if (dup2(prev_pipe[0], STDIN_FILENO) < 0)
	{
		perror("Error duplicating reading end of pipe");
		exit(errno);
	}
	//close(prev_pipe[0]);
	int i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	ft_deallocate_pipes(pipefd, pipex->cmd_count - 1);
	ft_execute(pipex->cmds[pipex->cmd_count - 1], pipex->envp); // indices correct?
}