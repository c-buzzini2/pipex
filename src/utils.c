/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:10:15 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/18 17:30:17 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size)
{
	unsigned int	len_s;
	unsigned int	len_d;
	unsigned int	i;

	len_s = ft_strlen(src);
	len_d = ft_strlen(dst);
	i = 0;
	if (size <= len_d || size == 0)
	{
		return (len_s + size);
	}
	while (src[i] && (len_d + i < size - 1))
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)s;
	while (i < n)
		arr[i++] = 0;
	return ;
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;
	int		i;

	len = ft_strlen(s);
	i = 0;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == 0)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len1;
	int		len2;
	int		joint_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len1 = ft_strlen (s1);
	len2 = ft_strlen (s2);
	joint_len = len1 + len2 + 1;
	join = (char *)malloc((joint_len) * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_bzero(join, joint_len);
	ft_strlcat (join, s1, joint_len);
	ft_strlcat (join, s2, joint_len);
	return (join);
}
