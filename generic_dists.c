/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_dists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:01:13 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/24 17:01:15 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	choose_dist(t_vec v, int i, t_window *w)
{
	t_vec z;

	z = (t_vec){0, 0, 0};
	if (w->a[i].type == 0)
		return (sphere_intersection(z, v, i, w));
	if (w->a[i].type == 1)
		return (plane_intersection(z, v, i, w));
	if (w->a[i].type == 2)
		return (cyl_intersection(z, v, i, w));
	else
		return (cone_intersection(z, v, i, w));
}

t_vec	choose_normal(float t, t_vec v, int i, t_window *w)
{
	t_vec z;

	z = (t_vec){0, 0, 0};
	if (w->a[i].type == 0)
		return (normalize(vec_add(sc_mult(t, v), sc_mult(-1.0, w->a[i].pos))));
	if (w->a[i].type == 1)
		return (normalize(w->a[i].axis));
	if (w->a[i].type == 2)
		return (cyl_normal(t, v, i, w));
	else
		return (cone_normal(t, v, i, w));
}

float	intersection(t_vec base, t_vec ray, int i, t_window *w)
{
	if (w->a[i].type == 0)
		return (sphere_intersection(base, ray, i, w));
	if (w->a[i].type == 1)
		return (plane_intersection(base, ray, i, w));
	if (w->a[i].type == 2)
		return (cyl_intersection(base, ray, i, w));
	else
		return (cone_intersection(base, ray, i, w));
}

int		color(t_vec v, int i, t_window *w)
{
	t_color	color;
	float	t;
	t_cvars	c;
	float	ltdist;
	int		index;

	color = w->a[i].m.amb;
	t = choose_dist(v, i, w);
	c.n = choose_normal(t, v, i, w);
	c.lm = vec_add(w->light, sc_mult(-t, v));
	ltdist = sqrt(dot(c.lm, c.lm));
	c.lm = normalize(c.lm);
	c.rm = vec_add(sc_mult(2.0 * dot(c.lm, c.n), c.n), sc_mult(-1.0, c.lm));
	index = mini_hit(sc_mult(t, v), c.lm, w);
	if ((index == -1 ||
		intersection(sc_mult(t, v), c.lm, index, w) > ltdist) &&
		dot(c.lm, c.n) > 0)
		color = color_add(color, color_scale(w->a[i].m.diff, dot(c.lm, c.n)));
	color = color_add(color, color_scale(w->a[i].m.spec,
		pow(dot(c.rm, normalize(v)), w->a[i].m.shine)));
	return (color_convert(color));
}
