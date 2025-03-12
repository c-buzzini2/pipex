/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:34:44 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 14:28:19 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr_lst;

	if (lst == NULL)
		return (NULL);
	curr_lst = lst;
	while (curr_lst->next != NULL)
		curr_lst = curr_lst->next;
	return (curr_lst);
}

/* 
int     main (void)
{
    char    *cont2 = "Hello";
    char    *cont1 = "World";
    char    *cont3 = "Life";
    t_list  *node = ft_lstnew(cont1);
    node->next = ft_lstnew(cont2);
    node->next->next = ft_lstnew(cont3);

    printf("%s", (char *)ft_lstlast(node)->content);
    free(node->next->next);
    free(node->next);
    free(node);
    return (0);
}
 */

//FREEING LISTS
/*
while (curr_lst != NULL)
    {
        t_list *temp = curr_lst;
        curr_lst = curr_lst->next;
        free(temp);
    }
*/