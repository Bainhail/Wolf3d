/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfindsize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:18:22 by naali             #+#    #+#             */
/*   Updated: 2018/11/19 12:26:49 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list		*ft_lstfindsize(t_list *alst, size_t c_size)
{
	t_list		*tmp;

	tmp = NULL;
	if (alst != NULL)
	{
		tmp = alst;
		while (tmp != NULL)
		{
			if (tmp->content_size == c_size)
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (tmp);
}
