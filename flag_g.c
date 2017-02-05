/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:58:20 by gricquie          #+#    #+#             */
/*   Updated: 2017/01/29 01:57:26 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int		flag_g_f(long double n, t_mod mod)
{
	int		len;
	int		i;

	len = 0;
	n = cut_double(n, mod.pad.prec - nbrlen_base((int)n, 10));
	if (!mod.minus)
		len += print_pad(nbrlen_base((int)n, 10) +
					(mod.pad.prec != 0 ? mod.pad.prec + 1 : 0), mod);
	i = ft_putnbr((int)n);
	n -= (int)n;
	if (mod.pad.prec != 0 && n != 0)
		len += ft_putchar('.');
	while ((int)(n * 10) == 0 && n != 0)
	{
		n *= 10;
		len += ft_putchar('0');
	}
	while (i <= mod.pad.prec && n != 0)
	{
		i += ft_putchar((int)(n = n * 10) + 48);
		n -= (int)n;
	}
	if (mod.minus)
		len += print_pad(len + i, mod);
	return (len + i);
}

int		flag_g_e(long double n, int exp, t_mod mod)
{
	int		len;
	int		i;

	n = cut_double(n, mod.pad.prec - 1);
	len = 0;
	if (!mod.minus)
		len += print_pad(mod.pad.prec + 1 + 4, mod);
	i = ft_putnbr((int)n);
	n -= (int)n;
	if (mod.pad.prec > 1 && n != 0)
		len += ft_putchar('.');
	while (n != 0 && i < mod.pad.prec)
	{
		n *= 10;
		i += ft_putchar((int)n + 48);
		n -= (int)n;
	}
	if (mod.pad.prec != 0)
		len += ft_printf("e%+03d", exp);
	if (mod.minus)
		len += print_pad(len + i, mod);
	return (len + i);
}

int		flag_g(va_list ap, t_mod mod)
{
	int			exp;
	long double	n;
	long double	nb;

	if (mod.pad.prec < 0)
		mod.pad.prec = 6;
	n = va_arg(ap, long double);
	nb = n;
	exp = calc_exp(&nb);
	if (exp < -4 || exp >= mod.pad.prec)
		return (flag_g_e(nb, exp, mod));
	return (flag_g_f(n, mod));
}
