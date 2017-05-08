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

double	plane_intersection(t_vec base, t_vec v, int i, t_window *w)
{
	t_vec	p;

	p = vec_add(w->a[i].pos, sc_mult(-1.0, base));
	if (dot(v, w->a[i].axis) != 0.0 &&
		dot(p, w->a[i].axis) / dot(v, w->a[i].axis) > 0.0)
		return (dot(p, w->a[i].axis) / dot(v, w->a[i].axis));
	return (0);
}
