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

float	cone_intersection(t_vec base, t_vec v, t_window *w)
{
	t_vec	p;
	t_vec	ax;
	t_vec	u;
	t_vec	q;
	float	tn;
	float	a;
	float	b;
	float	c;
	float	dist;

	p = vec_add(w->a[3].pos, sc_mult(-1.0, base));
	ax = w->a[3].axis;
	u = proj(v, ax);
	q = proj(p, ax);
	tn = sq(tan(w->a[3].radius));
	a = dot(u, u) - tn * sq(dot(ax, v));
	b = dot(q, u) - tn * dot(ax, v) * dot(ax, p);
	c = dot(q, q) - tn * sq(dot(ax, p));
	dist = 0;
	if (sq(b) > a * c)
		dist = quadratic_formula(a, b, c);
	return (dist);
}

t_vec	cone_normal(float t, t_vec v, t_window *w)
{
	t_vec n;
	t_vec a;

	a = w->a[3].axis;
	v = vec_add(sc_mult(t, v), sc_mult(-1.0, w->a[3].pos));
	if (dot(a, v) < 0)
		a = sc_mult(-1.0, a);
	n = vec_add(sc_mult(-1.0 * dot(v, v), a),
		sc_mult(dot(a, v), v));
	return (normalize(n));
}

int		cone_color(t_vec v, t_window *w)
{
	t_color	color;
	float	t;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;
	color = w->a[3].m.amb;
	t = cone_intersection((t_vec){0, 0, 0}, v, w);
	N = cone_normal(t, v, w);
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (!hit(sc_mult(t,v), Lm, w) && dot(Lm, N) > 0.0)
		color = color_add(color, color_scale(w->a[3].m.diff, dot(Lm, N)));
	if (dot(Lm, N) > 0.0)
		color = color_add(color, color_scale(w->a[3].m.spec,
		pow(dot(Rm, normalize(v)), w->a[3].m.shine)));
	return (color_convert(color));
}
