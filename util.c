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

float	quadratic_formula(float a, float b, float c)
{
	if (b > sqrt(sq(b) - a * c))
		return ((b - sqrt(sq(b) - a * c)) / a);
	else if (b + sqrt(sq(b) - a * c) > 0)
		return ((b + sqrt(sq(b) - a * c)) / a);
	else
		return (0);
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec ans;

	ans.x = a.y * b.z - a.z * b.y;
	ans.y = a.z * b.x - a.x * b.z;
	ans.z = a.x * b.y - a.y * b.x;
	return (ans);
}
