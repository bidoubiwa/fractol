/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palettes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:40:03 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/09 16:40:06 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fill_palettes(unsigned int ***palettes)
{
	(*palettes)[0][0] = 0xffffff;
	(*palettes)[0][1] = 0xe6e6e6;
	(*palettes)[0][2] = 0xcccccc;
	(*palettes)[0][3] = 0xb3b3b3;
	(*palettes)[0][4] = 0x999999;
	(*palettes)[1][0] = 0x119DA4;
	(*palettes)[1][1] = 0x14b5bd;
	(*palettes)[1][2] = 0x119da4;
	(*palettes)[1][3] = 0x0e858a;
	(*palettes)[1][4] = 0x0c6c71;
	(*palettes)[2][0] = 0xffffff;
	(*palettes)[2][1] = 0xC57B57;
	(*palettes)[2][2] = 0xF1AB86;
	(*palettes)[2][3] = 0xF7DBA7;
	(*palettes)[2][4] = 0x9CAFB7;
	(*palettes)[3][0] = 0xA09ABC;
	(*palettes)[3][1] = 0xB6A6CA;
	(*palettes)[3][2] = 0xD5CFE1;
	(*palettes)[3][3] = 0xD4BEBE;
	(*palettes)[3][4] = 0xB9FFB7;
	(*palettes)[4][0] = 0xB9FFB7;
	(*palettes)[4][1] = 0xABEDC6;
	(*palettes)[4][2] = 0x98D9C2;
	(*palettes)[4][3] = 0xF19A3E;
	(*palettes)[4][4] = 0x2589BD;
}

int			set_palettes(t_env *env)
{
	int				i;

	i = 0;
	if (!(env->palettes = malloc(sizeof(unsigned int*) * 5)))
		return (0);
	while (i < 5)
	{
		if (!(env->palettes[i] = malloc(sizeof(unsigned int) * 5)))
			return (0);
		i++;
	}
	fill_palettes(&env->palettes);
	return (1);
}
