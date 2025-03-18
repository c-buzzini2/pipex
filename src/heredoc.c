/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:35:08 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/18 17:35:41 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_error_heredoc(t_pipex *pipex, int fd)
{
	perror("Error opening outfile");
	close (fd);
	free(pipex->limiter);
	exit(errno);
}

static void	ft_read_heredoc(t_pipex *pipex)
{
	int		fd;
	char	*str;

	fd = open(pipex->infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error_heredoc(pipex, fd);
	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
			break ;
		if (ft_strcmp(str, pipex->limiter) == 0)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	close (fd);
	free(pipex->limiter);
	return ;
}

void	ft_heredoc(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 6)
	{
		ft_putstr_fd("Not enough arguments\n", 1);
		exit(1);
	}
	pipex->cmd_count = argc - 4;
	pipex->cmds = argv + 3;
	pipex->infile = "heredoc";
	pipex->limiter = ft_strjoin(argv[2], "\n");
	ft_read_heredoc(pipex);
}
