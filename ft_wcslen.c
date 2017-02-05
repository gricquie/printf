/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcslen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:59:04 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/04 23:35:00 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wcslen(wchar_t *wcs)
{
	int		len;

	len = 0;
	while (wcs && wcs[len])
		len++;
	return (len);
}
