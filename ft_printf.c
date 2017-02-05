/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:50:27 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/04 22:07:42 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		choose_flags2(const char **str, va_list ap, t_mod mod,
																	int final)
{
	if (**str == 'u' || **str == 'U')
		final += flag_u(ap, mod);
	else if (**str == '%')
		final += flag_prc(mod);
	else if (**str == 'f' || **str == 'F')
		final += flag_f(ap, mod);
	else if (**str == 'e' || **str == 'E')
		final += flag_e(ap, mod);
	else if (**str == 'g' || **str == 'G')
		final += flag_g(ap, mod);
	else if (**str == 'a' || **str == 'A')
		final += flag_a(ap, mod);
	else if (**str == 'n')
		final += flag_n(ap, final);
	else if (**str == 'b')
		final += flag_b(ap, mod);
	else
		(*str)--;
	return (final);
}

static int		choose_flags1(const char **str, va_list ap, int final)
{
	t_mod	mod;

	mod = search_mod(str, ap);
	if (**str == 's' && mod.l == 0)
		final += flag_s(ap, mod);
	else if ((**str == 's' && mod.l == 1) || **str == 'S')
		final += flag_ls(ap, mod);
	else if (**str == 'p')
		final += flag_p(ap, mod);
	else if (**str == 'd' || **str == 'i' || **str == 'D')
		final += flag_d(ap, mod);
	else if (**str == 'o' || **str == 'O')
		final += flag_o(ap, mod);
	else if (**str == 'x' || **str == 'X')
		final += flag_x(ap, mod);
	else if (**str == 'c' && mod.l == 0)
		final += flag_c(ap, mod);
	else if (**str == 'C' || (**str == 'c' && mod.l == 1))
		final += flag_lc(ap, mod);
	else
		final = choose_flags2(str, ap, mod, final);
	(*str)++;
	return (final);
}

int				ft_printf(const char *format, ...)
{
	int		final;
	va_list	ap;
	char	*ptr;
	char	*acc;

	va_start(ap, format);
	final = 0;
	while (*format)
	{
		ptr = ft_strchr(format, '%');
		acc = ft_strchr(format, '{');
		if (!ptr && !acc)
			return (final + ft_putstr(format));
		if (acc && (acc < ptr || !ptr))
			ptr = acc;
		final += write(1, format, ptr - format);
		format = ptr + 1;
		if (ptr == acc)
			color(&format, &final);
		else
			final = choose_flags1(&format, ap, final);
	}
	va_end(ap);
	return (final);
}
