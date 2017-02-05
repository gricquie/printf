/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 01:49:48 by gricquie          #+#    #+#             */
/*   Updated: 2017/01/29 01:57:47 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

long double	cut_double(long double n, int prec)
{
	int		i;

	i = prec;
	while (prec-- > 0)
		n *= 10;
	if ((n - (int)n) >= 0.5)
		n += 1;
	n = (int)n;
	while (i-- > 0)
		n /= 10;
	return (n);
}

int			print_double_prec(long double n, int prec)
{
	int		i;

	i = 0;
	n -= (int)n;
	if (prec != 0 && n != 0)
		i += write(1, ".", 1);
	while (i <= prec && n != 0)
	{
		n *= 10;
		ft_putnbr((int)n);
		n -= (int)n;
		i++;
	}
	return (i + (prec == 0 ? 0 : 1));
}

int			calc_exp(long double *n)
{
	int		exp;

	exp = 0;
	if (n == 0)
		return (0);
	while ((*n < 0 ? -*n : *n) < 1)
	{
		exp--;
		*n *= 10;
	}
	while ((*n < 0 ? -*n : *n) >= 10)
	{
		*n /= 10;
		exp++;
	}
	return (exp);
}
