/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:21 by cbuzzini          #+#    #+#             */
/*   Updated: 2024/11/15 15:31:49 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	if (!fd)
		return ;
	write (fd, &c, 1);
}

/*
int	main (void)
{
	int fd = open("/home/cbuzzini/libft/old_functions/test", O_WRONLY);
	if (fd == -1)
	{
    	perror("Error opening file");
    	return 1;
	}
	ft_putchar_fd('a', fd);
	close(fd);
	return (0);
}
*/

// int	main()
// {
// 	int fd = open("txt.txt", O_CREAT | O_WRONLY, 0644);
// 	ft_putchar_fd('a', fd);
// 	close(fd);
// }