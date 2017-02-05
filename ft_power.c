/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gricquie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 01:06:04 by gricquie          #+#    #+#             */
/*   Updated: 2017/02/05 01:11:12 by gricquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long	ft_power(unsigned long long nb, unsigned pow)
{
	if (pow <= 0)
		return (1);
	return (nb * ft_power(nb, pow - 1));
}
