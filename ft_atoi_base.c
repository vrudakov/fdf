/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudakov <vrudakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 22:05:21 by vrudakov          #+#    #+#             */
/*   Updated: 2017/06/02 18:54:46 by vrudakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_atoi_base(char *str)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	if (__builtin_strlen(str) == 0)
		return (0);
	if (str[0] == '0' && str[1] == 'x')
		i = 2;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'f')
			num = (num * 16) + (str[i] - 87);
		else if (str[i] >= 'A' && str[i] <= 'F')
			num = (num * 16) + (str[i] - 55);
		else if (str[i] >= '0' && str[i] <= '9')
			num = (num * 16) + (str[i] - 48);
		else
		{
			write(1, "usage: color must be in hex\n", 28);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (num);
}
