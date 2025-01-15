/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:46:33 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/15 15:07:08 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void		ft_second_child (char *argv[], char *envp[], int pipefd[])
{
		int		outfile;

		close(pipefd[1]);
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
		{
			perror("Error duplicating reading end of pipe");
			exit(1);
		}
		close(pipefd[0]);
		char *args[] = {"/bin/sh", "-c", argv[3], NULL};
		execve("/bin/sh", args, envp);
}

int		ft_second_fork (char *argv[], char *envp[], int pipefd[], int id1)
{	
	int		id2;
	int		exitstatus2;
	
	id2 = fork();
	if (id2 == -1)
	{
		perror("Error in the second fork");
		exit(1);
	}	
	if (id2 == 0) // child 2
	{
		ft_second_child(argv, envp, pipefd);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, &exitstatus2, 0);
 	if (WIFEXITED(exitstatus2) && WEXITSTATUS(exitstatus2) != 0) 
    	return WEXITSTATUS(exitstatus2);
	return (0);
}

void		ft_first_child (char *argv[], char *envp[], int pipefd[])
{
		int		infile;

		close(pipefd[0]);
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
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("Error duplicating writing end of pipe");
			exit(1);
		}
		close(pipefd[1]);
		char *args[] = {"/bin/sh", "-c", argv[2], NULL};
		execve("/bin/sh", args, envp); //child exits here anyways
}

int		ft_first_fork (char *argv[], char *envp[], int pipefd[]) // for bonus, receive int cmds for number of commands (argc -3)
{
	int		id1;
	
	id1 = fork();
	if (id1 == -1)
	{
		perror("Error in the first fork");
		exit(1);
	}
	// BONUS: create while loop WHILE there are commands to run
	//	int		pipefd2[2];
	if (id1 == 0) // child 1
	{
		ft_first_child(argv, envp, pipefd);
	}
	return(ft_second_fork(argv, envp, pipefd, id1));
}

int		main (int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	
	if (argc != 5)
	{
		ft_putstr_fd("Too few arguments.", 1);
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Error opening pipe");
		exit(1);
	}
	return (ft_first_fork(argv, envp, pipefd));
}