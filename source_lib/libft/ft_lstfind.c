/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 11:32:20 by naali             #+#    #+#             */
/*   Updated: 2018/11/18 11:42:36 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list			*ft_listfind(t_list *alst, void *content, size_t c_size)
{
	t_list	*tmp;

	tmp = NULL;
	if (alst != NULL)
	{
		tmp = alst;
		while (tmp != NULL)
		{
			if (ft_memcmp(tmp->content, content, c_size) == 0)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (tmp);
}
