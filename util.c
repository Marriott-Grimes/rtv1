/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 13:26:07 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/09 13:26:09 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	rotate_z(float a, t_vec v)
{
	t_vec temp;

	temp.x = cos(a) * v.x - sin(a) * v.y;
	temp.y = sin(a) * v.x + cos(a) * v.y;
	temp.z = v.z;
	return (temp);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec temp;

	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	temp.z = a.z + b.z;
	return (temp);
}

t_vec	sc_mult(float a, t_vec v)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
	return (v);
}

float	get_dist(t_vec a, t_vec b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)
				 + (a.z - b.z) * (a.z - b.z)));
}

float	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	normalize(t_vec v)
{
	float	len;

	len = dot(v, v);
	if (len == 1.0)
		return (v);
	return (sc_mult(1.0 / sqrt(len), v));
}

float	sq(float a)
{
	return (a * a);
}

