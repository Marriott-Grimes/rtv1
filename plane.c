/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:27:50 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/14 17:27:52 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	plane_intersection(t_vec base, t_vec v, int i, t_window *w)
{
	t_vec	p;

	p = vec_add(w->a[i].pos, sc_mult(-1.0, base));
	if (dot(v, w->a[i].axis) != 0.0 && dot(p, w->a[i].axis) / dot(v, w->a[i].axis) > 0.0)
		return (dot(p, w->a[i].axis) / dot(v, w->a[i].axis));
	return (0);
}

int		plane_color(t_vec v, int i, t_window *w)
{
	t_color	color;
	float	t;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;

	color = w->a[i].m.amb;
	t = dot(w->a[i].pos, w->a[i].axis) / dot(v, w->a[i].axis);
	N = normalize(w->a[i].axis);
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (mini_hit(sc_mult(t,v), Lm, w) == -1)
		color = color_add(color, color_scale(w->a[i].m.diff, dot(Lm, N)));
	color = color_add(color, color_scale(w->a[i].m.spec,
		pow(dot(Rm, normalize(v)), w->a[i].m.shine)));
	return (color_convert(color));
}
