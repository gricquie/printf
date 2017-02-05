/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 08:50:24 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/05 02:34:42 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		flag_x(va_list ap, t_mod mod)
{
	unsigned long long int	nb;
	int						i;
	int						len;

	i = 0;
	nb = type(ap, mod);
	if (!mod.l)
		nb %= U_INTMAX;
	len = nbrlen_base(nb, 16);
	if (!nb)
		len = 0;
	mod.pad.width -= mod.sharp * 2;
	if (mod.minus)
		mod.zero = 0;
	if (mod.zero && mod.pad.prec < mod.pad.width)
		mod.pad.prec = mod.pad.width;
	if (!mod.minus)
		i += print_pad(len, mod);
	if (mod.sharp && nb)
		i += write(1, (mod.maj ? "0X" : "0x"), 2);
	i += print_prec(len, mod);
	if (nb || mod.pad.prec)
		len = print_base(nb, (mod.maj ? "0123456789ABCDEF" :
										"0123456789abcdef"));
	if (mod.minus)
		i += print_pad(len, mod);
	return (len + i);
}

int		flag_c(va_list ap, t_mod mod)
{
	unsigned char	c;
	int				i;

	i = 0;
	c = (unsigned char)va_arg(ap, int);
	if (!mod.minus)
		i += print_pad(1, mod);
	ft_putchar(c);
	if (mod.minus)
		i += print_pad(1, mod);
	return (i + 1);
}

int		flag_ls(va_list ap, t_mod mod)
{
	wchar_t	*tmp;
	int		i;
	int		len;

	tmp = va_arg(ap, wchar_t *);
	len = ft_wcslen(tmp);
	if (!tmp)
		len = 6;
	if (mod.pad.prec != -1 && mod.pad.prec < len)
		len = mod.pad.prec;
	i = 0;
	if (!mod.minus)
		i += print_pad(len, mod);
	ft_wcswrite(tmp, len);
	if (mod.minus)
		i += print_pad(len, mod);
	return (len + i);
}

int		flag_lc(va_list ap, t_mod mod)
{
	wchar_t	tmp;
	int		i;

	tmp = va_arg(ap, wchar_t);
	i = 0;
	if (!mod.minus)
		i = print_pad(1, mod);
	ft_wcswrite(&tmp, 1);
	if (mod.minus)
		i += print_pad(1, mod);
	return (i + 1);
}

int		flag_prc(t_mod mod)
{
	int		i;

	i = 0;
	if (!mod.minus)
		i = print_pad(1, mod);
	write(1, "%", 1);
	if (mod.minus)
		i = print_pad(1, mod);
	return (i + 1);
}
