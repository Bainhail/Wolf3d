/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:45:56 by naali             #+#    #+#             */
/*   Updated: 2018/11/16 01:28:38 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

static void		*cpy_content(void const *src, size_t src_size)
{
	size_t			i;
	void			*dst;
	unsigned char	*srcc;
	unsigned char	*dstc;

	i = 0;
	dst = NULL;
	srcc = (unsigned char*)src;
	if ((dstc = (unsigned char*)malloc(sizeof(unsigned char)
												* src_size)) == NULL)
		return (NULL);
	while (i < src_size)
	{
		dstc[i] = srcc[i];
		i = i + 1;
	}
	dst = (void*)dstc;
	return (dst);
}

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*tmp;

	if ((tmp = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		tmp->content = NULL;
		tmp->content_size = 0;
	}
	else
	{
		tmp->content = cpy_content(content, content_size);
		tmp->content_size = content_size;
	}
	tmp->next = NULL;
	return (tmp);
}
