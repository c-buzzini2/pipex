/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/15 12:58:37 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_which_child(t_pipex *pipex, int forks)
{
	if (forks == 0)
		ft_first_child(pipex);
	else if (forks == pipex->cmd_count - 1)
		ft_last_child(pipex, pipex->fd[pipex->cmd_count - 2]);
	else
		ft_middle_child(pipex, pipex->fd[forks - 1], pipex->fd[forks], forks);
}

int	ft_parent(t_pipex *pipex, int last_pid)
{
	int		estatus;
	int		exited;
	int		last_status;
	int		i;

	i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
	while (1)
	{
		exited = waitpid(-1, &estatus, 0);
		if (exited == last_pid)
			last_status = estatus;
		if (exited <= 0)
			break ;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}

int	ft_fork(t_pipex *pipex)
{
	int		id;
	int		forks;

	forks = 0;
	while (forks < pipex->cmd_count)
	{
		id = fork();
		if (id == -1)
		{
			perror("Error in the fork");
			exit(errno);
		}
		if (id == 0)
			ft_which_child(pipex, forks);
		forks++;
	}
	return (ft_parent(pipex, id));
}

int	main(int argc, char *argv[], char *envp[])
{
	int				estatus;
	static t_pipex	pipex;

	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments.", 1);
		exit(1);
	}
	pipex.argc = argc;
	pipex.cmd_count = argc - 3; // needs if statement for heredoc (-4)
	pipex.cmds = argv + 2; //also inside if statement heredoc (+3)
	pipex.envp = envp;
	pipex.infile = argv[1];//not in heredoc. create a file and put in the same pointer
	pipex.outfile = argv[argc - 1];
	ft_create_arr_pipes(&pipex);
	estatus = ft_fork(&pipex);
	ft_deallocate_pipes(pipex.fd);
	return (estatus);
}
