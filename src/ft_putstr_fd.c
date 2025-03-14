/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/14 13:29:01 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "pipex.h"

static void	ft_putchar_fd(char c, int fd)
{
	if (!fd)
		return ;
	if (write(fd, &c, 1) == -1)
		exit(errno);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	n;

	n = 0;
	if (!s || !fd)
		return ;
	while (s[n] > 0)
	{
		ft_putchar_fd(s[n], fd);
		n++;
	}
}
