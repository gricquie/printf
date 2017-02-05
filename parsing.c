/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:22:44 by gricquie          #+#    #+#             */
/*   Updated: 2017/01/15 08:21:24 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	valid_mod(t_mod mod, const char c)
{
	if (mod.pad.prec != -1 && c == 'p')
		return (-1);
	if (ft_strchr("#0+ ", c) && (ft_strchr("scp", ft_tolower(c))))
		return (-1);
	if (mod.sharp && ft_strchr("ucdi", ft_tolower(c)))
		return (-1);
	if ((mod.h > 1 || mod.l > 1) && (c == 's' || c == 'p'))
		return (-1);
	if (mod.l > 0 && ((ft_isupper(c) && c != 'X') || c == 'p'))
		return (-1);
	return (0);
}

int			parsing(const char *str)
{
	t_mod mod;

	while (*str)
	{
		if (*str == '%')
		{
			if (str[1] == '%')
				str++;
			mod = search_mod(&str);
			if (valid_mod(mod, *str))
				return (-1);
		}
		str++;
	}
	return (1);
}
