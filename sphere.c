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

float	sphere_intersection(t_vec base, t_vec v, t_window *w)
{
	t_vec	p;
	float	dist;

	p = vec_add(w->a[0].pos, sc_mult(-1.0, base));
	dist = 0;
	if (sq(dot(p, v)) > dot(v, v) * (dot(p, p) - sq(w->a[0].radius)) + 0.01)
		dist = quadratic_formula(dot(v, v), dot(p, v), dot(p, p) - sq(w->a[0].radius));
	return (dist);
}

int		sphere_color(t_vec v, t_window *w)
{
	t_color		color;
	float		t;
	t_shape		sphere;
	t_vec		N;
	t_vec		Lm;
	t_vec		Rm;

	sphere = w->a[0];
	color = sphere.m.amb;
	t = quadratic_formula(dot(v, v), dot(sphere.pos, v), dot(sphere.pos, sphere.pos) - sq(sphere.radius));
	N = normalize(vec_add(sc_mult(t, v), sc_mult(-1.0, sphere.pos)));
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (!hit(sc_mult(t,v), Lm, w) && dot(Lm, N) > 0.0)
		color = color_add(color, color_scale(sphere.m.diff, dot(Lm, N)));
	color = color_add(color, color_scale(sphere.m.spec,
			pow(dot(Rm, normalize(v)), sphere.m.shine)));
	return (color_convert(color));
}
