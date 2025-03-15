/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:35:08 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/15 12:52:46 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int     ft_heredoc(void)
{
	int	fd;
	int i = 0;

	fd = open ("/home/cbuzzini/get_next_line/test_REMOVE", O_RDONLY);
		if (fd == -1)
		{
			printf("Cannot read file.\n");
			return (0);
		}

	while (1)
	{
		char *str = get_next_line(fd);
		printf("line: |%s\n", str);
		i++;
		if (str == NULL)
			return 0;
		free(str);
	}
	close (fd);
	return (0);
}          