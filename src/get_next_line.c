/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/15 12:43:59 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_next_line(int fd)
{
	char		*joined;
	static char	buffer[BUFFER_SIZE + 1];
	int			read_bytes;

	joined = NULL;
	while (fd >= 0 && BUFFER_SIZE > 0)
	{
		if (buffer[0])
		{
			joined = ft_strjoin(joined, buffer);
			if (joined == NULL)
				return (NULL);
			ft_strlcpy(buffer, buffer + ft_len_till_eol(buffer, '\n'), \
						BUFFER_SIZE - ft_len_till_eol(buffer, '\n') + 1);
			if (joined[ft_len_till_eol(joined, '\n') - 1] == '\n')
				return (joined);
		}
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(joined), NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
	}
	return (joined);
}
