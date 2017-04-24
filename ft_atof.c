#include "rtv1.h"

float	ft_atof(char *str)
{
	float	ans;
	float	counter;
	float	sign;

	counter = 0.1;
	sign = 1.0;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	ans = (float)ft_atoi(str);
	while ('0' <= *str && *str <= '9')
		str++;
	if (*str == '.')
	{
		str++;
		while ('0' <= *str && *str <= '9')
		{
			if (counter > counter * 0.1)
				ans += counter * (float)(*str - '0');
			counter /= 10.0;
			str++;
		}
	}
	return (ans * sign);
}
