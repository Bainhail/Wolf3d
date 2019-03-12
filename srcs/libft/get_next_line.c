/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 02:51:35 by naali             #+#    #+#             */
/*   Updated: 2018/11/23 12:48:06 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft.h"
#include "./get_next_line.h"

static void			delnode(t_list **buf, t_list *node)
{
	t_list		*tmp;

	tmp = *buf;
	if (node == *buf)
	{
		tmp = tmp->next;
		if (node->content != NULL)
			free(node->content);
		node->content = NULL;
		node->content_size = 0;
		free(node);
	}
	else
	{
		while (tmp->next != node)
			tmp = tmp->next;
		if (node->content != NULL)
			free(node->content);
		node->content = NULL;
		node->content_size = 0;
		tmp->next = node->next;
		free(node);
	}
}

static t_list		*init_filereader(t_list **buf, const int fd)
{
	t_list			*tmp;

	tmp = *buf;
	if (tmp == NULL)
	{
		tmp = ft_lstnew(NULL, 0);
		*buf = tmp;
	}
	else if (tmp != NULL && (tmp = ft_lstfindsize(tmp, fd)) == NULL)
	{
		tmp = ft_lstnew(NULL, 0);
		ft_lstlast(buf, tmp);
	}
	else
		return (tmp);
	if ((tmp->content = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
		return (NULL);
	ft_bzero(tmp->content, (BUFF_SIZE + 1));
	tmp->content_size = fd;
	return (tmp);
}

static int			writeline(void **src, char **line)
{
	int			flg;
	char		*end;
	char		*tmp;

	flg = 0;
	end = NULL;
	tmp = (char*)(*src);
	if ((end = ft_strchr(tmp, '\n')) != NULL)
	{
		flg = 1;
		*end = '\0';
	}
	if ((tmp = ft_strjoin(*line, tmp)) == NULL)
		return (-1);
	if (flg == 1)
	{
		ft_memmove(*src, (end + 1), ft_strlen(end + 1));
		ft_bzero(*src + ft_strlen(end + 1), BUFF_SIZE - ft_strlen(end + 1));
	}
	else
		ft_bzero(*src, BUFF_SIZE);
	if (*line != NULL)
		free(*line);
	*line = tmp;
	return (flg);
}

static int			readfromfile(t_list *node, char **line, ssize_t *nb_r)
{
	int			ret;
	char		*tmp;

	ret = 0;
	tmp = (char*)(node->content);
	if (tmp[0] != '\0')
	{
		if ((ret = writeline(&(node->content), line)) == 1)
			return (ret);
	}
	while ((*nb_r = read(node->content_size, node->content, BUFF_SIZE)) > 0)
	{
		if (*nb_r < BUFF_SIZE)
			tmp[*nb_r] = '\0';
		if ((ret = writeline(&(node->content), line)) == 1
			|| (*nb_r < BUFF_SIZE && *line != NULL && **line != '\0'))
			return (1);
	}
	if (*nb_r < 0)
		ret = *nb_r;
	return (ret);
}

int					get_next_line(const int fd, char **line)
{
	ssize_t			ret;
	ssize_t			nb_r;
	t_list			*tmp;
	static t_list	*buf = NULL;

	ret = 0;
	nb_r = 0;
	tmp = NULL;
	if (fd >= 0 && line != NULL && BUFF_SIZE > 0)
	{
		*line = NULL;
		if ((tmp = init_filereader(&buf, fd)) == NULL)
			return (-1);
		if ((ret = readfromfile(tmp, line, &nb_r)) == 1)
			return (1);
	}
	if (BUFF_SIZE <= 0 || ret == -1 || fd < 0 || line == NULL)
		return (-1);
	if (nb_r < BUFF_SIZE && *line != NULL && **line != '\0')
		return (1);
	if (buf != NULL && tmp != NULL)
		delnode(&buf, tmp);
	return (0);
}
