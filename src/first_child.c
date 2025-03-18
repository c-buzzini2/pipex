/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/18 17:41:11 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "pipex_bonus.h"
#else
# include "pipex.h"
#endif

void	ft_delete_heredoc(t_pipex *pipex)
{
	if (unlink(pipex->infile) != 0)
	{
		perror("Could not delete heredoc file");
		ft_deallocate_pipes(pipex->fd);
		exit(errno);
	}
}

static void	ft_close_pipes_first(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipex->fd[i][0]);
		if (i != 0)
			close(pipex->fd[i][1]);
		i++;
	}
}

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

void	ft_first_child(t_pipex *pipex)
{
	int		infile;

	ft_close_pipes_first(pipex);
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
	if (ft_strcmp(pipex->infile, "heredoc") == 0)
		ft_delete_heredoc(pipex);
	ft_first_child2(pipex);
}
