/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:57:04 by naali             #+#    #+#             */
/*   Updated: 2018/11/19 12:25:52 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void		ft_lstlast(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = NULL;
	if (alst != NULL)
		tmp = *alst;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp != NULL && new != NULL)
		tmp->next = new;
}
