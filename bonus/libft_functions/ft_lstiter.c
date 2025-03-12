/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:34:44 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/12 14:28:16 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* static void    ft_del_content(void *content)
{
    free(content);
    return ;
}

static void    ft_test(void *content)
{
    *(int *)content = 42;
    return ;
}
 */

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	t_list	*temp_lst;

	if (!lst || !f)
		return ;
	while (lst)
	{
		temp_lst = lst->next;
		f(lst->content);
		lst = temp_lst;
	}
	return ;
}

/* 
int     main (void)
{
    int *cont1 = malloc(sizeof(int));
    int *cont2 = malloc(sizeof(int));
    int *cont3 = malloc(sizeof(int));
	if (!cont1 || !cont2 || !cont3)
        return (0);
	
	*cont1 = 1;
    *cont2 = 2;
    *cont3 = 3;
 	
	t_list  *node = ft_lstnew(cont1);
    t_list  *node2 = ft_lstnew(cont2);
    t_list  *node3 = ft_lstnew(cont3);
    t_list  *curr_lst;
    
	ft_lstadd_back(&node, node2);
    ft_lstadd_back(&node, node3);
    curr_lst = node;
    while (curr_lst != NULL)
    {
        printf("%d\n", *(int *)(curr_lst->content));
        curr_lst = curr_lst->next;
    }
    ft_lstiter(node, ft_test);
    curr_lst = node;
    while (curr_lst != NULL)
    {
        printf("%d\n", *(int *)(curr_lst->content));
        curr_lst = curr_lst->next;
    }
    ft_lstclear(&node, ft_del_content);
    return (0);
}
 */