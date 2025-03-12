/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/16 12:43:43 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include "pipex_bonus.h"

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