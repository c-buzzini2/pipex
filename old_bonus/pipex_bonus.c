/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/17 17:42:22 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*int		ft_array_size(char *arr[])
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return(i);
} */

void	ft_execute(char *cmd, char *envp[])
{
	char	*args[4];

	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve("/bin/sh", args, envp);
}

void	ft_create_pipe(int *pipes[], int i)
{
	if (pipe(pipes[i]) == -1)
	{
 		perror("Error creating pipe");
             while (i-- >= 0)
                free(pipes[i]);
            free(pipes);
            exit (1);
    }
}

int	**ft_allocate_pipes(int total_pipes)
{
	int		**pipes;
	int		i;

	pipes = malloc (1 * sizeof(int *) * total_pipes);
	if (!pipes)
	{
		ft_putstr_fd("Error allocating pipes.", 1);
		exit (1);
	}
	i = 0;
	while (i < total_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            while (--i >= 0)
                free(pipes[i]);
            free(pipes);
			ft_putstr_fd("Error allocating pipe %i.", 1);
            exit (1);
		}
		ft_create_pipe(pipes, i);
		i++;
	}
	return (pipes);
}

void	ft_close_and_free(int *pipes[], int total_pipes)
{
	int		i;

	i = 0;
	while (i < total_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		estatus;
	int		total_cmds;
	int		exctd_cmds;
	int		**pipes;
	int		pid;

	printf("Hello");
	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments.", 1);
		exit(1);
	}
	total_cmds = argc - 3; // if heredoc, --
	pipes = ft_allocate_pipes(total_cmds - 1);
	ft_first_fork(argv, envp, pipes[0]);
	exctd_cmds = 1;
	while (exctd_cmds < argc - 3)
	{
		if (exctd_cmds == total_cmds - 1)
		{
			ft_last_fork(argv, envp, pipes, exctd_cmds);
			exctd_cmds++;
		}
		else
		{
			ft_middle_fork(argv, envp, pipes, exctd_cmds);
			exctd_cmds++;
		}
	}
	while ((pid = wait(&estatus)) > 0);
	ft_close_and_free(pipes, total_cmds - 1); // !!!!!START HERE, NEED TO CLOSE ALL PIPES ENDS AT THE PARENT;Side
	return (estatus);
}
