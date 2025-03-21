/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/18 17:25:35 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "pipex_bonus.h"
#else
# include "pipex.h"
#endif

static void	ft_close_pipes_last(t_pipex *pipex, int prev_pipe[])
{
	int		i;

	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipex->fd[i][1]);
		if (pipex->fd[i] != prev_pipe)
			close(pipex->fd[i][0]);
		i++;
	}
}

static void	ft_last_child2(t_pipex *pipex, int prev_pipe[])
{
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

void	ft_last_child(t_pipex *pipex, int prev_pipe[])
{
	int		outfile;

	ft_close_pipes_last(pipex, prev_pipe);
	if (ft_strcmp(pipex->infile, "heredoc") == 0)
		outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
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
	ft_last_child2(pipex, prev_pipe);
}
