/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 12:09:03 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/12 12:26:40 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			get_x_min(int order)
{
	if (order == 1)
		return (0);
	else
		return (WIDTH_SCREEN - (WIDTH_SCREEN / 5));
}


int			get_x_max(int order)
{
	//if (order == 1)
//		return (WIDTH_SCREEN - (WIDTH_SCREEN / 5));
//	else
		return (WIDTH_SCREEN);
}

int			get_y_min(int order)
{
	if (order == 1 || order == 2)
		return (0);
	else if (order == 3)
		return (HEIGHT_SCREEN / 3);
	else
		return (HEIGHT_SCREEN - (HEIGHT_SCREEN / 3));
}

int			get_y_max(int order)
{
	if (order == 1 || order == 4)
		return (HEIGHT_SCREEN);
	else if (order == 2)
		return (HEIGHT_SCREEN / 3);
	else
		return (HEIGHT_SCREEN - (HEIGHT_SCREEN / 3));
}
