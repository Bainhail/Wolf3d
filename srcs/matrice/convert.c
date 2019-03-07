/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:07:08 by naali             #+#    #+#             */
/*   Updated: 2018/12/15 15:43:42 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_struct.h"

double		conv_deg_to_rad(double degree)
{
	return ((degree * M_PI) / 180);
}

double		conv_rad_to_deg(double radian)
{
	return ((radian / M_PI) * 180);
}
