/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 13:26:07 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/09 13:26:09 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	normalize(t_vec v)
{
	double	len;

	len = dot(v, v);
	if (len == 1.0)
		return (v);
	return (sc_mult(1.0 / sqrt(len), v));
}

double	sq(double a)
{
	return (a * a);
}

double	quadratic_formula(double a, double b, double c)
{
	double t1;
	double t2;

	t1 = (b + sqrt(sq(b) - a * c)) / a;
	t2 = (b - sqrt(sq(b) - a * c)) / a;
	if (0.0 < t2 && t2 < 0.0001)
		t2 = c / a / t1;
	else if (0.0 < t1 && t1 < 0.0001)
		t1 = c / a / t2;
	if (t2 < 0.0)
		return (t1);
	if (t1 < 0.0)
		return (t2);
	return (t1 < t2 ? t1 : t2);
}
