/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 14:51:18 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/05 02:37:41 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		calc_pad(const char **str, va_list ap)
{
	int		width;

	if (**str == '*')
		return (va_arg(ap, int));
	width = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	(*str)--;
	return (width);
}

static int		calc_prec(const char **str, va_list ap)
{
	int		prec;

	if (**str != '.')
		return (0);
	(*str)++;
	if (**str == '*')
		return (va_arg(ap, int));
	prec = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	(*str)--;
	return (prec);
}

t_mod			init_mod(void)
{
	t_mod	mod;

	mod.pad.width = 0;
	mod.pad.prec = -1;
	mod.maj = 0;
	mod.zero = 0;
	mod.sharp = 0;
	mod.minus = 0;
	mod.plus = 0;
	mod.space = 0;
	mod.l = 0;
	mod.apos = 0;
	mod.ml = 0;
	mod.valid = 1;
	return (mod);
}

static t_mod	fill_mod(t_mod mod, const char **str, va_list ap)
{
	if ((ft_isdigit(**str) && **str != '0') || **str == '*')
		mod.pad.width = calc_pad(str, ap);
	else if (**str == '.')
		mod.pad.prec = calc_prec(str, ap);
	else if (**str == '#')
		mod.sharp += 1;
	else if (**str == '0')
		mod.zero = 1;
	else if (**str == '-')
		mod.minus += 1;
	else if (**str == '+')
		mod.plus = 1;
	else if (**str == ' ')
		mod.space += 1;
	else if (**str == 'h' && mod.l <= 0)
		mod.l--;
	else if (**str == 'l' || **str == 'j' || **str == 'z')
		mod.l++;
	else if (**str == *"'")
		mod.apos++;
	else if (**str == 'L')
		mod.ml++;
	else
		mod.valid = 0;
	return (mod);
}

t_mod			search_mod(const char **str, va_list ap)
{
	t_mod	mod;

	mod = init_mod();
	while (**str && **str != '%' && (**str == 'l' || **str == 'h' ||
		**str == 'j' || **str == 'z' || **str == 'L' || ft_isdigit(**str) ||
		**str == '.' || **str == '0' || **str == '#' || **str == '-' ||
		**str == '+' || **str == ' ' || **str == *"'"))
	{
		mod = fill_mod(mod, str, ap);
		(*str)++;
	}
	if (mod.minus)
		mod.zero = 0;
	if (mod.pad.prec > 0)
		mod.zero = 0;
	if (ft_isupper(**str))
		mod.maj = 1;
	if (**str == 'D' || **str == 'O' || **str == 'U')
		mod.l = 1;
	return (mod);
}
