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

	if (dot(v, w->a[1].axis) != 0.0 && dot(w->a[1].pos, w->a[1].axis) / dot(v, w->a[1].axis) > 0.0)
		return (dot(w->a[1].pos, w->a[1].axis) / dot(v, w->a[1].axis));
	return (0);
}

int		plane_color(t_vec v, t_window *w)
{
	t_color	color;
	float	t;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;

	color = w->a[1].m.amb;
	t = dot(w->a[1].pos, w->a[1].axis) / dot(v, w->a[1].axis);
	N = normalize(w->a[1].axis);
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (!hit(sc_mult(t,v), Lm, w))
		color = color_add(color, color_scale(w->a[1].m.diff, dot(Lm, N)));
	color = color_add(color, color_scale(w->a[1].m.spec,
		pow(dot(Rm, normalize(v)), w->a[1].m.shine)));
	return (color_convert(color));
}
