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

int		gradient(int startcolor, int endcolor, float i)
{
	int alp;
	int red;
	int grn;
	int blu;

	alp = (int)((startcolor & 0xFF000000) * i +
		(endcolor & 0xFF000000) * (1.0 - i)) & 0xFF000000;
	red = (int)((startcolor & 0x00FF0000) * i +
		(endcolor & 0x00FF0000) * (1.0 - i)) & 0x00FF0000;
	blu = (int)((startcolor & 0x0000FF00) * i +
		(endcolor & 0x0000FF00) * (1.0 - i)) & 0x0000FF00;
	grn = (int)((startcolor & 0x000000FF) * i +
		(endcolor & 0x000000FF) * (1.0 - i)) & 0x000000FF;
	return (alp + red + blu + grn);
}

int		color_scale(int color, float i)
{
	int alp;
	int red;
	int grn;
	int blu;

	alp = (int)((color & 0xFF000000) * i) & 0xFF000000;
	red = (int)((color & 0x00FF0000) * i) & 0x00FF0000;
	blu = (int)((color & 0x0000FF00) * i) & 0x0000FF00;
	grn = (int)((color & 0x000000FF) * i) & 0x000000FF;
	return (alp + red + blu + grn);
}

int color_add(int a, int b)
{
	// int alp;
	int red;
	int grn;
	int blu;

	// alp = (a >> 6) + (b >> 6);
	// if (alp > 0x000000FF)
	// 	alp = 0xFF000000;
	// else
	// 	alp = alp << 6;
	red = (a & 0x00FF0000) + (b & 0x00FF0000);
	if (red >= 0x01000000)
		red = 0x00FF0000;
	blu = (a & 0x0000FF00) + (b & 0x0000FF00);
	if (blu >= 0x00010000)
		blu = 0x0000FF00;
	grn = (a & 0x000000FF) + (b & 0x000000FF);
	if (grn >= 0x00000100)
		grn = 0x000000FF;
	return ((red & 0x00FF0000) + (blu & 0x0000FF00) + (grn & 0x000000FF));
}
