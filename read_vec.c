/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:49:11 by mgrimes           #+#    #+#             */
/*   Updated: 2017/05/01 16:49:13 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_isnum(char c)
{
	if (c == '-' || c == '.' || ('0' <= c && c <= '9'))
		return (1);
	return (0);
}

char	*next_num(char *str)
{
	while (ft_isnum(*str))
		str++;
	while (!ft_isnum(*str))
		str++;
	return (str);
}

t_vec	read_vector(char *line)
{
	t_vec v;

	v.x = ft_atof(line);
	line = next_num(line);
	v.y = ft_atof(line);
	line = next_num(line);
	v.z = ft_atof(line);
	return (v);
}

t_color	read_color(char *line)
{
	t_color c;

	c.r = ft_atof(line);
	line = next_num(line);
	c.g = ft_atof(line);
	line = next_num(line);
	c.b = ft_atof(line);
	return (c);
}
