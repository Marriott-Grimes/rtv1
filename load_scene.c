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

char	*next_car(char *s, char c)
{
	while (*s != c)
		s++;
	s++;
	return (s);
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

void	read_shape(char *line, int i, t_window *w)
{
	w->a[i].pos = read_vector(line);
	line = next_car(line, '/');
	w->a[i].axis = normalize(read_vector(line));
	line = next_car(line, '/');
	w->a[i].radius = ft_atof(line);
	line = next_car(line, '/');
	w->a[i].m.spec = read_color(line);
	line = next_car(line, '/');
	w->a[i].m.diff = read_color(line);
	line = next_car(line, '/');
	w->a[i].m.amb = read_color(line);
	line = next_car(line, '/');
	w->a[i].m.shine = ft_atoi(line);
	line = next_car(line, '/');
	w->a[i].type = ft_atoi(line);
}

void	load_scene(int fd, t_window *w)
{
	int		eof;
	char	*line;
	int		i;
	char test;

	eof = 1;
	i = 0;
	test = 0;
	if (fd < 0 || read(fd, &test, 0) == -1)
	{
		ft_putstr("bad file :(\n");
		exit(0);
	}
	eof = get_next_line(fd, &line);
	w->light = read_vector(line);
	while (eof && i < NUM)
	{
		eof = get_next_line(fd, &line);
		read_shape(line, i, w);
		i++;
	}
}
