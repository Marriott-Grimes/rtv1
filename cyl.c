/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@4i.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:27:41 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/14 17:27:43 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cyl_intersection(t_vec base, t_vec v, int i, t_window *w)
{
	t_vec	p;
	double	dist;

	p = vec_add(w->a[i].pos, sc_mult(-1.0, base));
	p = proj(p, w->a[i].axis);
	v = proj(v, w->a[i].axis);
	dist = 0;
	if (sq(dot(p, v)) > dot(v, v) * (dot(p, p) - sq(w->a[i].radius)))
		dist = quadratic_formula(dot(v, v), dot(p, v),
								dot(p, p) - sq(w->a[i].radius));
	return (dist);
}

t_vec	cyl_normal(double t, t_vec v, int i, t_window *w)
{
	t_vec	p;

	p = proj(w->a[i].pos, w->a[i].axis);
	v = proj(v, w->a[i].axis);
	return (normalize(vec_add(sc_mult(t, v), sc_mult(-1.0, p))));
}
