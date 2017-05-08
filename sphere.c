/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:28:15 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/14 17:28:17 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	sphere_intersection(t_vec base, t_vec v, int i, t_window *w)
{
	t_vec	p;
	double	dist;

	p = vec_add(w->a[i].pos, sc_mult(-1.0, base));
	dist = 0;
	if (sq(dot(p, v)) > dot(v, v) * (dot(p, p) - sq(w->a[i].radius)) + 0.001)
		dist = quadratic_formula(dot(v, v), dot(p, v),
				dot(p, p) - sq(w->a[i].radius));
	return (dist);
}
