/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 04:42:18 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/05 02:35:53 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static long long int	change_range(int nb, int range)
{
	nb = nb % range;
	if (nb >= range / 2)
		return (nb - range);
	if (nb < -range / 2)
		return (nb + range);
	return (nb);
}

long long int			type(va_list ap, t_mod mod)
{
	long long int	i;

	i = 0;
	if (mod.l == -2)
		i = (change_range(va_arg(ap, int), 256));
	if (mod.l == -1)
		i = (change_range(va_arg(ap, int), 65536));
	if (!mod.l)
		i = va_arg(ap, int);
	if (mod.l == 1)
		i = va_arg(ap, long);
	if (mod.l == 2)
		i = va_arg(ap, long long);
	return (i);
}
