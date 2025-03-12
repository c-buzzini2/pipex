/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 15:49:51 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execute(char *cmd, char *envp[])
{
	char	*args[4];

	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve("/bin/sh", args, envp);
}

void ft_which_child(t_pipex *pipex, int **pipefd, int forks)
{
	if (forks == 0)
		ft_first_child(pipex, pipefd[0]);
	else if (forks == pipex->cmd_count - 1)
		ft_last_child(pipex, pipefd[pipex->cmd_count - 2]);
	else
		ft_middle_child(pipex, pipefd[forks], pipefd[forks + 1]);

}

int	ft_fork(t_pipex *pipex, int **pipefd)
{
	int		id;
	int		estatus;
	int		forks;

	forks = 0;
	id = -2;
	while (forks < pipex->cmd_count)
	{
		if (id != 0)
		{
			id = fork();
			if (id == -1)
			{
				perror("Error in the fork");
				exit(errno);
			}
		}
		if (id == 0)
			ft_which_child(pipex, pipefd, forks);
		forks++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id_last, &estatus, 0);
	if (WIFEXITED(estatus))
		return (WEXITSTATUS(estatus));
	return (1);
}


int	main(int argc, char *argv[], char *envp[])
{
	int				**pipefd;
	int				estatus;
	static t_pipex	pipex;

	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments.", 1);
		exit(1);
	}
	pipex.argc = argc;
	pipex.cmd_count = argc - 3; // needs if statement for heredoc (-5)
	pipex.cmds = argv + 2; //also inside if statement heredoc
	pipex.envp = envp;
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	pipefd = ft_create_arr_pipes(&pipex);
	int i = 0;
	while (i < (pipex.cmd_count - 1))
	{
		printf("%d\n", pipefd[i][0]);
		i++;
	}
	estatus = ft_fork(&pipex, pipefd);
	return (estatus);
	}
