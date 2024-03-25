/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:56:03 by moel-fat          #+#    #+#             */
/*   Updated: 2024/01/15 15:27:56 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_overflow(const char *str, int sign)
{
	long int	nbr;
	long int	nb;
	size_t		i;

	nb = 0;
	nbr = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nbr * 10 + (str[i] - '0');
		if (nb < nbr && sign == 1)
			return (-1);
		else if (nb < nbr && sign == -1)
			return (0);
		nbr = nb;
		i++;
	}
	return (nbr * sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	rest;

	i = 0;
	sign = 1;
	rest = 0;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	rest = ft_overflow(str + i, sign);
	return (rest);
}
