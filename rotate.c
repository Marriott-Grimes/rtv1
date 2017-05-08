/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 19:28:39 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/28 19:28:42 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	rotate_x(double a, t_vec v)
{
	t_vec temp;

	temp.x = v.x;
	temp.y = cos(a) * v.y - sin(a) * v.z;
	temp.z = sin(a) * v.y + cos(a) * v.z;
	return (temp);
}

t_vec	rotate_y(double a, t_vec v)
{
	t_vec temp;

	temp.x = cos(a) * v.x - sin(a) * v.z;
	temp.y = v.y;
	temp.z = sin(a) * v.x + cos(a) * v.z;
	return (temp);
}

t_vec	rotate_z(double a, t_vec v)
{
	t_vec temp;

	temp.x = cos(a) * v.x - sin(a) * v.y;
	temp.y = sin(a) * v.x + cos(a) * v.y;
	temp.z = v.z;
	return (temp);
}

t_vec	rotate(char ax, double a, t_vec v)
{
	if (ax == 'x')
		return (rotate_x(a, v));
	if (ax == 'y')
		return (rotate_y(a, v));
	else
		return (rotate_z(a, v));
}
