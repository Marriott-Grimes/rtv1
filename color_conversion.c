/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 16:15:04 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/09 16:15:05 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		color_scale(t_color c, double i)
{
	if (i < 0)
		i *= -1.0;
	c.r *= i;
	if (c.r > 1.0)
		c.r = 1.0;
	c.g *= i;
	if (c.g > 1.0)
		c.g = 1.0;
	c.b *= i;
	if (c.b > 1.0)
		c.b = 1.0;
	return (c);
}

t_color		color_add(t_color a, t_color b)
{
	a.r += b.r;
	if (a.r > 1.0)
		a.r = 1.0;
	a.g += b.g;
	if (a.g > 1.0)
		a.g = 1.0;
	a.b += b.b;
	if (a.b > 1.0)
		a.b = 1.0;
	return (a);
}

int			color_convert(t_color c)
{
	int	red;
	int	grn;
	int	blu;

	c.r *= 255.0;
	if (c.r > 255.0)
		c.r = 255.0;
	c.g *= 255.0;
	if (c.g > 255.0)
		c.g = 255.0;
	c.b *= 255.0;
	if (c.b > 255.0)
		c.b = 255.0;
	red = (int)c.r;
	red = red * 0x00010000;
	grn = (int)c.g;
	grn = grn * 0x00000100;
	blu = (int)c.b;
	return (red + grn + blu);
}
