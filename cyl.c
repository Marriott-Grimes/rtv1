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

float	cyl_intersection(t_vec base, t_vec v, int i, t_window *w)
{

	t_vec	p;
	float	dist;

	p = vec_add(w->a[i].pos, sc_mult(-1.0, base));
	p = proj(p, w->a[i].axis);
	v = proj(v, w->a[i].axis);
	dist = 0;
	if (sq(dot(p, v)) > dot(v, v) * (dot(p, p) - sq(w->a[i].radius)) + 0.01)
		dist = quadratic_formula(dot(v, v), dot(p, v), dot(p, p) - sq(w->a[i].radius));
	return (dist);
}

int		cyl_color(t_vec v, int i, t_window *w)
{
	t_color	color;
	float	t;
	t_vec	temp_pos;
	t_vec	temp_ray;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;

	color = w->a[i].m.amb;
	temp_pos = vec_add(w->a[i].pos, sc_mult(-1.0 * dot(w->a[i].pos, w->a[i].axis), w->a[i].axis));
	temp_ray = vec_add(v, sc_mult(-1.0 * dot(v, w->a[i].axis), w->a[i].axis));
	t = quadratic_formula(dot(temp_ray, temp_ray), dot(temp_pos, temp_ray), dot(temp_pos, temp_pos) - sq(w->a[i].radius));
	N = normalize(vec_add(sc_mult(t, temp_ray), sc_mult(-1.0, temp_pos)));
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (mini_hit(sc_mult(t,v), Lm, w) == -1 && dot(Lm, N) > 0.0)
	{
		color = color_add(color, color_scale(w->a[i].m.diff, dot(Lm, N)));
		color = color_add(color, color_scale(w->a[i].m.spec,
		pow(dot(Rm, normalize(v)), w->a[i].m.shine)));
	}
	return (color_convert(color));
}
