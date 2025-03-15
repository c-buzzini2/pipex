/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:01:56 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/15 12:44:10 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_len_till_eol(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (c == '\0')
	{
		while (s[i] != '\0')
			i++;
	}
	if (c == '\n')
	{
		while (s[i] != '\0' && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			i++;
	}
	return (i);
}

unsigned int	ft_strlcat(char *dst, char *src, unsigned int size)
{
	unsigned int	len_s;
	unsigned int	len_d;
	unsigned int	i;

	len_d = ft_len_till_eol(dst, 0);
	len_s = ft_len_till_eol(src, '\n');
	i = 0;
	if (size <= len_d || size == 0)
		return (len_s + size);
	while (src[i] && (len_d + i < size - 1) && i < len_s)
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}

char	*ft_strdup(char *s, int fr)
{
	int		len;
	char	*dest;
	int		i;

	len = ft_len_till_eol(s, '\n');
	i = 0;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == 0)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		dest[i] = '\n';
		i++;
	}
	dest[i] = '\0';
	if (fr == 1)
		free(s);
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		len1;
	int		len2;
	int		joint_len;
	int		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2, 0));
	if (s2 == NULL)
		return (ft_strdup(s1, 1));
	i = 0;
	len1 = ft_len_till_eol (s1, 0);
	len2 = ft_len_till_eol (s2, '\n');
	joint_len = len1 + len2 + 1;
	join = (char *)malloc((joint_len) * sizeof(char));
	if (join == NULL)
		return (NULL);
	while (i < joint_len)
		join[i++] = 0;
	ft_strlcat (join, s1, joint_len);
	ft_strlcat (join, s2, joint_len);
	free(s1);
	return (join);
}

void	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size <= 0)
		return ;
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
