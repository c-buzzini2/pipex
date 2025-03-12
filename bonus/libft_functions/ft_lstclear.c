/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:34:44 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 14:28:08 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* 
static void    ft_del_content(void *content)
{
    free(content);
    return ;
}
 */

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp_lst;

	if (!lst || !del || *lst == NULL)
		return ;
	while (*lst)
	{
		temp_lst = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp_lst;
	}
	return ;
}

/*
int     main (void)
{
    char    *cont1 = ft_strdup("World");
    char    *cont2 = ft_strdup("Hello");
    char    *cont3 = ft_strdup("Life");
    t_list  *node = ft_lstnew(cont1);
    t_list  *node2 = ft_lstnew(cont2);
    t_list  *node3 = ft_lstnew(cont3);
    t_list  *curr_lst;

    ft_lstadd_back(&node, node2);
    ft_lstadd_back(&node, node3);
    curr_lst = node;
    while (curr_lst != NULL)
    {
        printf("%s\n", (char *)(curr_lst->content));
        curr_lst = curr_lst->next;
    }
    ft_lstclear(&node, ft_del_content);
    return (0);
}
*/