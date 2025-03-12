/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:34:44 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 14:41:50 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_child	*ft_lstnew(int index, char *cmd)
{
	t_child	*new_node;

	new_node = malloc(1 * sizeof (t_child));
	if (new_node == NULL)
		return (NULL);
	new_node->index = index;
	new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}
