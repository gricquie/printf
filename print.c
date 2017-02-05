/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 19:41:54 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/04 23:58:41 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		nbrlen_base(unsigned long long int n, int base)
{
	unsigned long long int	factor;
	int						len;

	factor = 1;
	len = 1;
	if (base < 2)
		return (0);
	if (n == 0)
		return (1);
	while (factor <= n / base)
	{
		factor *= base;
		len++;
	}
	return (len);
}

int		print_pad(int len, t_mod mod)
{
	int		totlen;

	totlen = 0;
	while (mod.pad.width > len && mod.pad.width > mod.pad.prec)
	{
		ft_putchar(mod.zero == 1 ? '0' : ' ');
		mod.pad.width--;
		totlen++;
	}
	return (totlen);
}

int		print_prec(int len, t_mod mod)
{
	int		i;

	i = 0;
	while (mod.pad.prec - i > len)
	{
		i++;
		ft_putchar('0');
	}
	return (i);
}

int		print_base(unsigned long long int n, char *base)
{
	unsigned long long int	factor;
	int						len;
	int						baselen;

	factor = 1;
	len = 0;
	baselen = ft_strlen(base);
	if (baselen <= 1)
		return (0);
	while (factor <= n / baselen)
		factor *= baselen;
	while (factor > 0)
	{
		len++;
		ft_putchar(base[n / factor]);
		n = n % factor;
		if (factor == 1)
			factor = 0;
		factor /= baselen;
	}
	return (len);
}

int		print_apos(unsigned long long int n, t_mod mod)
{
	int						len;
	unsigned long long int	factor;
	int						i;

	factor = 1;
	len = nbrlen_base(n, 10);
	i = len;
	while (factor <= n / 10)
		factor *= 10;
	while (len > 0)
	{
		ft_putchar(n / factor + 48);
		n = n % factor;
		factor /= 10;
		if (factor == 0)
			factor = 1;
		if (len % 3 == 1 && n > 10 && mod.apos)
			ft_putchar(',');
		len--;
	}
	return (i + mod.apos * (i - 1) / 3);
}
