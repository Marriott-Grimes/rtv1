/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:27:41 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/14 17:27:43 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	cyl_intersection(t_vec base, t_vec v, t_window *w)
{

	t_vec	p;
	float	dist;

	p = vec_add(w->a[2].pos, sc_mult(-1.0, base));
	p = proj(p, w->a[2].axis);
	v = proj(v, w->a[2].axis);
	dist = 0;
	if (sq(dot(p, v)) > dot(v, v) * (dot(p, p) - sq(w->a[2].radius)) + 0.01)
		dist = quadratic_formula(dot(v, v), dot(p, v), dot(p, p) - sq(w->a[2].radius));
	return (dist);
}

int		cyl_color(t_vec v, t_window *w)
{
	t_color	color;
	float	t;
	t_vec	temp_pos;
	t_vec	temp_ray;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;

	color = w->a[2].m.amb;
	temp_pos = vec_add(w->a[2].pos, sc_mult(-1.0 * dot(w->a[2].pos, w->a[2].axis), w->a[2].axis));
	temp_ray = vec_add(v, sc_mult(-1.0 * dot(v, w->a[2].axis), w->a[2].axis));
	t = quadratic_formula(dot(temp_ray, temp_ray), dot(temp_pos, temp_ray), dot(temp_pos, temp_pos) - sq(w->a[2].radius));
	N = normalize(vec_add(sc_mult(t, temp_ray), sc_mult(-1.0, temp_pos)));
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (!hit(sc_mult(t,v), Lm, w) && dot(Lm, N) > 0.0)
		color = color_add(color, color_scale(w->a[2].m.diff, dot(Lm, N)));
	if (!hit(sc_mult(t,v), Lm, w) && dot(Lm, N) > 0.0)
		color = color_add(color, color_scale(w->a[2].m.spec,
		pow(dot(Rm, normalize(v)), w->a[2].m.shine)));
	return (color_convert(color));
}
