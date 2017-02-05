/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 01:42:13 by gricquie          #+#    #+#             */
/*   Updated: 2017/01/29 02:10:20 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			flag_f(va_list ap, t_mod mod)
{
	int			len;
	long double	n;

	if (mod.pad.prec < 0)
		mod.pad.prec = 6;
	n = va_arg(ap, long double);
	len = nbrlen_base((int)n, 10);
	if (!mod.minus)
		len += print_pad(len + (mod.pad.prec != 0 ? mod.pad.prec + 1 : 0), mod);
	ft_putnbr((int)n);
	len += print_double_prec(n, mod.pad.prec);
	if (mod.minus)
		len += print_pad(len + (mod.pad.prec != 0 ? mod.pad.prec + 1 : 0), mod);
	return (len);
}

int			flag_e(va_list ap, t_mod mod)
{
	int			len;
	int			exp;
	long double	n;

	n = va_arg(ap, long double);
	len = 1;
	if (mod.pad.prec < 0)
		mod.pad.prec = 6;
	exp = calc_exp(&n);
	if (!mod.minus)
		len += print_pad((mod.pad.prec != 0 ? mod.pad.prec + 2 : 0), mod);
	ft_putnbr((int)n);
	n -= (int)n;
	len += print_double_prec(n, mod.pad.prec);
	ft_putchar((mod.maj ? 'E' : 'e'));
	len += ft_printf("%+03d", exp);
	if (mod.minus)
		len += print_pad((mod.pad.prec != 0 ? mod.pad.prec + 2 : 0), mod);
	return (len + 1);
}

static int	flag_a2(double n, t_mod mod, int sign, int exp)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if ((mod.pad.prec == -1 ? n != 0 : mod.pad.prec == 0) && ++len)
		ft_putchar('.');
	while ((mod.pad.prec != -1 ? i < mod.pad.prec : n != 0))
	{
		print_base((int)n, (mod.maj ? "0123456789ABCDEF" : "0123456789abcdef"));
		n = (n - (int)n) * 16;
		i++;
	}
	len++;
	ft_putstr((mod.maj ? "P" : "p"));
	len += ft_printf((sign < 0 ? "%+d" : "%d"), exp) + i + len;
	if (mod.minus)
		len += print_pad((mod.pad.prec != 0 ? mod.pad.prec + 2 : 0), mod);
	return (len + i);
}

int			flag_a(va_list ap, t_mod mod)
{
	int			exp;
	int			len;
	int			sign;
	long double	n;

	n = va_arg(ap, long double);
	len = 0;
	exp = 0;
	sign = 1;
	if (n < 0)
	{
		len += write(1, "-", 1);
		n = -n;
		sign = -1;
	}
	while (n < 1 && --exp)
		n *= 2;
	while (n >= 2 && ++exp)
		n /= 2;
	if (!mod.minus)
		len += print_pad((mod.pad.prec != 0 ? mod.pad.prec + 2 : 0), mod);
	len += write(1, (mod.maj ? "0X" : "0x"), 2) + 1;
	ft_putnbr((int)n);
	n = (n - (int)n) * 16;
	return (len + flag_a2(n, mod, sign, exp));
}

int			flag_n(va_list ap, int final)
{
	int		*n;

	n = va_arg(ap, int *);
	*n = final;
	return (0);
}
