#include "rtv1.h"
// #include <stdio.h>

// int				ft_atoi(char *str)
// {
// 	long long	answer;
// 	int			sign;
// 	int			i;

// 	answer = 0;
// 	i = 0;
// 	sign = 1;
// 	while (WHITE(str[i]))
// 		i++;
// 	if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
// 	{
// 		sign = -1;
// 		i++;
// 	}
// 	if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
// 		i++;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 			break ;
// 		answer *= 10;
// 		answer += str[i] - '0';
// 		i++;
// 	}
// 	return ((int)(answer * sign));
// }

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

// int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return 0;
// 	printf("%f", ft_atof(argv[1]));
// 	return 0;
// }