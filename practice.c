/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:56:23 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/13 15:31:53 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		main (void)
{
	int		pipefd1[2];
	int		id1;
	
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
        char    buffer[6];

		close(pipefd1[0]);
		infile = open("file1", O_RDONLY);
		if (infile == -1)
		{
			perror("Error opening infile");
			exit(1);
		}	
        read(infile, &buffer, 5);
        buffer[5] = '\0';
        close(infile);
        write(pipefd1[1], &buffer, 5);
        close(pipefd1[1]);
    }
    if (id1 > 0) // PARENT
    {
        int		outfile;
        char    buffer[6];

		close(pipefd1[1]);
		outfile = open("file2", O_WRONLY);
		if (outfile == -1)
		{
			perror("Error opening outfile");
			exit(1);
		}	
        read(pipefd1[0], &buffer, 5);
        buffer[5] = '\0';
        write(outfile, &buffer, 5);
        close(outfile);
        close(pipefd1[0]);
    }
}