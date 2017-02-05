/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 05:14:44 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/05 03:45:28 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flag_s(va_list ap, t_mod mod)
{
	char	*tmp;
	int		i;
	int		len;

	tmp = va_arg(ap, char *);
	len = ft_strlen(tmp);
	if (mod.pad.prec != -1 && mod.pad.prec < len)
		len = mod.pad.prec;
	mod.pad.prec = 0;
	if (!mod.minus)
		i = print_pad(len, mod);
	if (tmp)
		write(1, tmp, len);
	else
		len = ft_putstr("(null)");
	if (mod.minus)
		i = print_pad(len, mod);
	return (i + len);
}

int		flag_p(va_list ap, t_mod mod)
{
	void	*addr;
	int		i;
	int		len;

	addr = va_arg(ap, void *);
	len = 0;
	if (addr || mod.pad.prec)
		len = nbrlen_base((long int)addr, 16);
	i = print_pad(len + 2, mod);
	ft_putstr("0x");
	if (addr || mod.pad.prec)
		print_base((long int)addr, "0123456789abcdef");
	return (i + len + 2);
}

#include <stdio.h>

int		flag_d(va_list ap, t_mod mod)
{
	long long int	nb;
	unsigned int	i;
	int				len;

	i = 0;
	nb = type(ap, mod);
	len = 0;
	if (nb || mod.pad.prec)
		len = nbrlen_base(ABS(nb), 10);
	len += (mod.apos * (len - 1) / 3);
	if (!mod.minus && !mod.zero)
		i = print_pad(ft_max(mod.pad.prec, len) + CHAR_BEFORE, mod);
	if (nb < 0)
		i += ft_putchar('-');
	if ((mod.plus || mod.space) && nb >= 0)
		i += ft_putchar(mod.plus ? '+' : ' ');
	if (mod.zero)
		i += print_pad(ft_max(mod.pad.prec, len) + CHAR_BEFORE, mod);
	i += print_prec(len, mod);
	if (nb || mod.pad.prec)
		print_apos(ABS(nb), mod);
	if (mod.minus)
		i += print_pad(ft_max(mod.pad.prec, len) + CHAR_BEFORE, mod);
	return (i + len);
}

int		flag_o(va_list ap, t_mod mod)
{
	long long int	nb;
	int				i;
	int				len;

	nb = type(ap, mod);
	if (mod.l == 0)
		nb = nb + U_INTMAX % U_INTMAX;
	else if (mod.l == -1)
		nb = (nb + 65536) % 65536;
	else if (mod.l == -2)
		nb = nb + 256 % 256;
	len = mod.sharp;
	if (nb)
		len = nbrlen_base(nb, 8) + mod.sharp;
	i = 0;
	if (mod.minus)
		mod.zero = 0;
	if (!mod.minus)
		i = print_pad(len, mod);
	if (mod.sharp)
		ft_putchar('0');
	i += print_prec(len, mod);
	if (nb || mod.pad.prec)
		len = print_base(nb, "01234567") + mod.sharp;
	if (mod.minus)
		i += print_pad(len, mod);
	return (len + i);
}

int		flag_u(va_list ap, t_mod mod)
{
	unsigned long long int	nb;
	int						i;
	int						len;

	i = 0;
	nb = type(ap, mod);
	if (!mod.l)
		nb = nb + U_INTMAX % U_INTMAX;
	else if (mod.l == -1)
		nb = nb + 65536 % 65536;
	else if (mod.l == -2)
		nb = nb + 256 % 256;
printf("%llu\n", nb);
	len = nbrlen_base(nb, 10);
	if (!mod.minus)
		i = print_pad(len + mod.apos * (len - 1) / 3, mod);
	i += print_prec(len + mod.apos * (len - 1) / 3, mod);
	if (nb || mod.pad.prec)
		len = print_apos(nb, mod);
	if (mod.minus)
		i += print_pad(len, mod);
	return (len + i);
}
