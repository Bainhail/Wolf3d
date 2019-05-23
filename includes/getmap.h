/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:44:42 by naali             #+#    #+#             */
/*   Updated: 2019/05/23 09:29:02 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETMAP_H
# define GETMAP_H

int				tablen(char **tab);
void			free_useless(char ***tab, char **s1, int tmax);
char			**ft_pushback_str_to_tab(char ***tab, char **s1);

#endif
