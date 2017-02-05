/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 21:34:39 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/04 22:54:46 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flag_b(va_list ap, t_mod mod)
{
	long long int	nb;
	int				i;
	int				len;

	nb = va_arg(ap, long long int);
	len = nbrlen_base(nb, 2);
	i = 0;
	if (!mod.minus)
		i += print_pad(len, mod);
	i += print_prec(len, mod);
	print_base(nb, "01");
	return (len + i);
}

void	color(const char **str, int *final)
{
	int		dec;

	dec = 0;
	if (ft_strnequ(*str, "eoc}", (dec = 4)))
		*final += (write(1, "\033[0m", 4));
	else if (ft_strnequ(*str, "black}", (dec = 6)))
		*final += (write(1, "\033[30m", 5));
	else if (ft_strnequ(*str, "red}", (dec = 4)))
		*final += (write(1, "\033[31m", 5));
	else if (ft_strnequ(*str, "green}", (dec = 6)))
		*final += (write(1, "\033[32m", 5));
	else if (ft_strnequ(*str, "yellow}", (dec = 7)))
		*final += (write(1, "\033[33m", 5));
	else if (ft_strnequ(*str, "blue}", (dec = 5)))
		*final += (write(1, "\033[34m", 5));
	else if (ft_strnequ(*str, "magenta}", (dec = 8)))
		*final += (write(1, "\033[35m", 5));
	else if (ft_strnequ(*str, "cyan}", (dec = 5)))
		*final += (write(1, "\033[36m", 5));
	else if (ft_strnequ(*str, "white}", (dec = 6)))
		*final += (write(1, "\033[37m", 5));
	else if (!(dec = 0))
		*final += (write(1, "{", 1));
	(*str) += dec;
}
