/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:45:26 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:28:42 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp1;
	t_list	*tmp2;
	t_list	*cpy;
	t_list	*n_lst;

	cpy = NULL;
	n_lst = NULL;
	if (lst != NULL && f != NULL)
	{
		tmp1 = lst->next;
		cpy = (*f)(lst);
		n_lst = ft_lstnew(cpy->content, cpy->content_size);
		lst = tmp1;
		tmp2 = n_lst;
		while (lst != NULL)
		{
			tmp1 = lst->next;
			cpy = (*f)(lst);
			tmp2->next = ft_lstnew(cpy->content, cpy->content_size);
			lst = tmp1;
			tmp2 = tmp2->next;
		}
	}
	return (n_lst);
}
