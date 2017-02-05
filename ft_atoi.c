/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 21:29:23 by gricquie          #+#    #+#             */
/*   Updated: 2016/11/21 21:29:24 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	i;
	unsigned int	result;
	int				sign;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) && str[i])
	{
		result = result * 10 + (str[i] - 48) * sign;
		i++;
	}
	return (result);
}
