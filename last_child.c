/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:06:27 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/16 14:19:16 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_last_child(char *argv[], char *envp[], int pipefd[])
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
	ft_execute(argv[3], envp);
}