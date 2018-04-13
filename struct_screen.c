/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:29:55 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/13 19:35:44 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		free_screens(t_screen **screens)
{
	t_screen	*scr_tmp;
	int			i;

	i = 0;
	while (i < 4)
	{
		scr_tmp = screens[i];
		free(scr_tmp);
		screens[i] = NULL;
		i++;
	}
	free(screens);
}

int			get_order(char p, int i)
{
	if ((i == 1 && p == 'j') || (i == 2 && p != 'j'))
		return (2);
	else if ((i == 1 && p == 'b') || (i == 3 && p != 'b'))
		return (3);
	else if ((i == 1 && p == 'a') ||( i == 4 && p != 'a'))
		return (4);
	else 	
		return (1);
}

int		is_in_true_screen(t_screen *scr, int x, int y)
{
	if (x > scr->min_x && x < scr->max_x
				&& y > scr->min_y && y < scr->max_y)
		return (1);
	else
		return (0);
}

int		is_in_screen(t_screen *scr, int x, int y)
{
	if (x > scr->min_scr_x && x < scr->max_scr_x
				&& y > scr->min_scr_y && y < scr->max_scr_y)
		return (1);
	else
		return (0);
}
