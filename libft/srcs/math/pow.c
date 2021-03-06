/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblet <mblet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 09:30:22 by mblet             #+#    #+#             */
/*   Updated: 2016/03/02 09:37:26 by mblet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_pow(int base, int pow)
{
	int		i;

	i = 0;
	if (pow <= 0)
		return (1);
	while (i <= pow)
	{
		base *= base;
		++i;
	}
	return (base);
}
