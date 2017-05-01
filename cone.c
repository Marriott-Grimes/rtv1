/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 20:36:52 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/14 20:36:54 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	cone_intersection(t_vec base, t_vec v, int i, t_window *w)
{
	t_conevars	n;
	float		dist;

	n.p = vec_add(w->a[i].pos, sc_mult(-1.0, base));
	n.u = proj(v, w->a[i].axis);
	n.q = proj(n.p, w->a[i].axis);
	n.tn = sq(tan(w->a[i].radius));
	n.a = dot(n.u, n.u) - n.tn * sq(dot(w->a[i].axis, v));
	n.b = dot(n.q, n.u) - n.tn * dot(w->a[i].axis, v) * dot(w->a[i].axis, n.p);
	n.c = dot(n.q, n.q) - n.tn * sq(dot(w->a[i].axis, n.p));
	dist = 0;
	if (sq(n.b) > n.a * n.c)
		dist = quadratic_formula(n.a, n.b, n.c);
	return (dist);
}

t_vec	cone_normal(float t, t_vec v, int i, t_window *w)
{
	t_vec n;
	t_vec a;

	a = w->a[i].axis;
	v = vec_add(sc_mult(t, v), sc_mult(-1.0, w->a[i].pos));
	if (dot(a, v) < 0)
		a = sc_mult(-1.0, a);
	n = vec_add(sc_mult(-1.0 * dot(v, v), a),
		sc_mult(dot(a, v), v));
	return (normalize(n));
}
