/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcswrite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:59:26 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/04 23:33:38 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	printwc2(wchar_t wc)
{
	int c;

	c = wc / 0x40 + 0xc0;
	ft_putchar(c);
	wc = wc % 0x40 + 0x80;
	ft_putchar(wc);
}

static void	printwc3(wchar_t wc)
{
	int c;

	c = wc / 0x1000 + 0xe0;
	ft_putchar(c);
	wc = wc % 0x1000;
	c = wc / 0x40 + 0x80;
	ft_putchar(c);
	wc = wc % 0x40 + 0x80;
	ft_putchar(wc);
}

static void	printwc4(wchar_t wc)
{
	int c;

	c = wc / 0x100000 + 0xf0;
	ft_putchar(c);
	wc = wc % 0x100000;
	c = wc / 0x800 + 0x80;
	ft_putchar(c);
	wc = wc % 0x80;
	c = wc / 0x40 + 0x80;
	ft_putchar(c);
	wc = wc % 0x40 + 0x80;
	ft_putchar(wc);
}

int			ft_wcswrite(wchar_t *wcs, int len)
{
	int		i;

	i = 0;
	if (!wcs)
		return (ft_putstr("(null)"));
	while (i < len)
	{
		if (wcs[i] < 0x80)
			ft_putchar(wcs[i]);
		else if (wcs[i] < 0x800)
			printwc2(wcs[i]);
		else if (wcs[i] < 0x10000)
			printwc3(wcs[i]);
		else
			printwc4(wcs[i]);
		i++;
	}
	return (i);
}
