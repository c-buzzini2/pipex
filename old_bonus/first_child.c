/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/17 16:25:14 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include "pipex_bonus.h"

void	ft_first_child(char *argv[], char *envp[], int pipefd[])
{
	int		infile;
//if heredoc, exectd++ -

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
	ft_execute(argv[2], envp);
}

void	ft_first_fork(char *argv[], char *envp[], int pipefd[])
{
	int		id1;

	id1 = fork();
	if (id1 == -1)
	{
		perror("Error in the first fork");
		exit(1);
	}
	if (id1 == 0)
	{
		ft_first_child(argv, envp, pipefd);
	}
	return ;
}