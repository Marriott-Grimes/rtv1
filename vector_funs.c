/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 15:53:02 by mgrimes           #+#    #+#             */
/*   Updated: 2017/05/01 15:53:08 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

float	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	proj(t_vec v, t_vec perp)
{
	return (vec_add(v, sc_mult(-1.0 * dot(perp, v), perp)));
}
