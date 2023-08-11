/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:55:50 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 20:07:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft00.h"

t_list	*ft_lstnew_free(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (free(content), NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elm;
	t_list	*nwlst;

	if (!lst)
		return (NULL);
	nwlst = ft_lstnew_free(f(lst->content));
	if (!nwlst)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		elm = ft_lstnew_free(f(lst->content));
		if (!elm)
		{
			ft_lstclear(&nwlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nwlst, elm);
		lst = lst->next;
	}
	return (nwlst);
}
