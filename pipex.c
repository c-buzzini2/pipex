/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/14 15:30:42 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//int		ft_pipe_and_fork (void) // for bonus, receive int cmds for number of commands (argc -3)
int		main (int argc, char *argv[], char *envp[])
{
	int		pipefd1[2];
	int		id1;
	
	if (argc != 5)
	{
		ft_putstr_fd("Too few arguments.", 1);
		exit(1);
	}
		return 0;
	if (pipe(pipefd1) == -1)
	{
		perror("Error opening pipe");
		exit(1);
	}
	id1 = fork();
	if (id1 == -1)
	{
		perror("Error in the first fork");
		exit(1);
	}
	if (id1 == 0) // child 1
	{
		int		infile;

		close(pipefd1[0]);
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
		{
			perror("Error opening infile");
			exit(1);
		}	
		if (dup2(infile, STDIN_FILENO) < 0)
		{
			perror("Error duplicating infile");
			exit(1);
		}
		close(infile);
		if (dup2(pipefd1[1], STDOUT_FILENO) < 0)
		{
			perror("Error duplicating writing end of pipe");
			exit(1);
		}
		close(pipefd1[1]);
		char *args[] = {"/bin/sh", "-c", argv[2], NULL};
		execve("/bin/sh", args, envp); //child exits here anyways
	}
	// BONUS: create while loop WHILE there are commands to run
	//	int		pipefd2[2];
	int		id2;
	id2 = fork();
	if (id2 == -1)
	{
		perror("Error in the second fork");
		exit(1);
	}	
	if (id2 == 0) // child 2
	{
		int		outfile;

		close(pipefd1[1]);
		outfile = open(argv[4], O_WRONLY);
		if (outfile == -1)
		{
			perror("Error opening outfile");
			exit(1);
		}	
		if (dup2(outfile, STDOUT_FILENO) < 0)
		{
			perror("Error duplicating outfile");
			exit(1);
		}
		close(outfile);
		if (dup2(pipefd1[0], STDIN_FILENO) < 0)
		{
			perror("Error duplicating reading end of pipe");
			exit(1);
		}
		close(pipefd1[0]);
		char *args[] = {"/bin/sh", "-c", argv[3], NULL};
		execve("/bin/sh", args, envp);
	}
	close(pipefd1[0]);
	close(pipefd1[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	return 0;
}
/* int		main (int argc, char *argv[], char *envp[])
{
	
} */