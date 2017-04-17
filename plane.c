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

float	plane_intersection(t_vec v, t_window *w)
{

	if (dot(v, w->b.n) != 0.0 && dot(w->b.pos, w->b.n) / dot(v, w->b.n) > 0.0)
		return (dot(w->b.pos, w->b.n) / dot(v, w->b.n));
	return (0);
}

int		plane_color(t_vec v, t_window *w)
{
	t_color	color;
	float	t;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;

	color = w->b.m.amb;
	t = dot(w->b.pos, w->b.n) / dot(v, w->b.n);
	N = normalize(w->b.n);
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (!hit(sc_mult(t,v), Lm, w))
		color = color_add(color, color_scale(w->b.m.diff, dot(Lm, N)));
	color = color_add(color, color_scale(w->b.m.spec,
		pow(dot(Rm, normalize(v)), w->b.m.shine)));
	return (color_convert(color));
}
