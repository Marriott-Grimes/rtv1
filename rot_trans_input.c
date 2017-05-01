/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_trans_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 15:54:38 by mgrimes           #+#    #+#             */
/*   Updated: 2017/05/01 15:54:40 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	trans(t_window *w)
{
	char	*line;
	int		i;

	ft_putstr("Choose the object you want to translate, ");
	ft_putstr("with a number between zero and ");
	ft_putnbr(NUM - 1);
	ft_putstr("\n");
	get_next_line(0, &line);
	i = ft_atoi(line);
	while (i < 0 || i >= NUM)
	{
		ft_putstr("Error: Bad number\n");
		free(line);
		get_next_line(0, &line);
		i = ft_atoi(line);
	}
	ft_putstr("type in the vector you wish to translate by:\n");
	get_next_line(0, &line);
	w->a[i].pos = vec_add(w->a[i].pos, read_vector(line));
	free(line);
}

int		rot_part_one(void)
{
	char	*line;
	int		i;

	ft_putstr("Choose the object you want to rotate, ");
	ft_putstr("with a number between zero and ");
	ft_putnbr(NUM - 1);
	ft_putstr("\n");
	get_next_line(0, &line);
	i = ft_atoi(line);
	while (i < 0 || i >= NUM)
	{
		ft_putstr("Error: Bad number\n");
		free(line);
		get_next_line(0, &line);
		i = ft_atoi(line);
	}
	free(line);
	return (i);
}

void	rot(t_window *w)
{
	char	*line;
	int		i;
	char	xyz;

	i = rot_part_one();
	ft_putstr("Choose the axis (x, y, or z)\n");
	get_next_line(0, &line);
	xyz = line[0];
	while (line[0] != 'x' && line[0] != 'y' && line[0] != 'z')
	{
		ft_putstr("Error: Bad answer\n");
		free(line);
		get_next_line(0, &line);
		xyz = line[0];
	}
	ft_putstr("How many degrees?\n");
	free(line);
	get_next_line(0, &line);
	w->a[i].axis = rotate(xyz, ft_atoi(line) * PI / 180.0, w->a[i].axis);
	free(line);
}

void	rot_tr(t_window *w)
{
	char	*line;

	ft_putstr("Would you like to [r]otate or [t]ranslate?\n");
	get_next_line(0, &line);
	if (line[0] == 't')
		trans(w);
	else if (line[0] == 'r')
		rot(w);
	free(line);
}
