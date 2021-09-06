/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:28:32 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 16:28:33 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static size_t		ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r' ||
c == '\f');
}

int					ft_atoi(const char *str)
{
	unsigned int	value;
	int				sign;
	int				count;

	value = 0;
	sign = 1;
	count = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '-' ? -1 : 1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		value += *str - '0';
		str++;
		count++;
	}
	if (count >= 17)
		return (sign == -1 ? 0 : -1);
	return (value * sign);
}

size_t				ft_intlen(intmax_t n)
{
	size_t	len;

	len = 0;
	if (!n)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

double				ft_atof(char *str)
{
	float	atof;
	int		atoi;
	int		i;
	int		f;

	f = 1;
	atof = 0;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	str[i] == '-' ? f = -1 : 0;
	atoi = ft_atoi(str);
	i = ft_intlen(atoi);
	f == -1 ? i++ : 0;
	if (str[i] != '.')
		return (atoi);
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		f *= 10;
		atof = atof * 10 + str[i] - 48;
		i++;
	}
	atof = atof / f;
	return ((double)(atoi + atof));
}
