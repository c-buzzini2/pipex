/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/13 14:04:39 by cbuzzini         ###   ########.fr       */
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
		ft_first_child(pipex, pipefd[0], pipefd);
	else if (forks == pipex->cmd_count - 1)
		ft_last_child(pipex, pipefd[pipex->cmd_count - 2], pipefd);
	else
		ft_middle_child(pipex, pipefd[forks - 1], pipefd[forks], forks, pipefd); //Make sure that these indices are ok
}

int	ft_fork(t_pipex *pipex, int **pipefd)
{
	int		id;
	int		estatus;
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
			ft_which_child(pipex, pipefd, forks);
		forks++;
	}
	int i = 0;
	while (i < (pipex->cmd_count - 1))
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
//	close(pipefd[0]); CLOSE ALL PIPES IN A LOOP (BOTH ENDS)
//	close(pipefd[1]);
	pid_t child_pid;
    while ((child_pid = waitpid(-1, &estatus, 0)) > 0) 
	{
        if (WIFEXITED(estatus))
            printf("Child PID %d exited with status %d\n", child_pid, WEXITSTATUS(estatus));
		else 
		    printf("Child PID %d terminated abnormally\n", child_pid);
    }
	ft_deallocate_pipes(pipefd, pipex->cmd_count - 1);
    printf("All children have finished.\n");
    return 0;
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
	//ft_deallocate_pipes(pipefd, pipex.cmd_count - 1);
	return (estatus);
	}
