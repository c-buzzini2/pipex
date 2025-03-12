/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 11:03:53 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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