/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:08:37 by skarim            #+#    #+#             */
/*   Updated: 2024/08/09 11:51:10 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
Create a 32-bit pixel value from RGBA components
*/
int	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*
Put a pixel in a specify x and y
*/
void	plot(int x, int y, t_cub *cub, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		mlx_put_pixel(cub->image, x, y, color);
	}
}

/*
Return absolute value of a number
*/
int	abs(int x)
{
	if (x >= 0)
		return (x);
	else
		return (-x);
}

/*
DDA algorithm, generate a line between two points.
*/
void	draw_line(t_point start_point, t_point end_point, t_cub *cub, int color)
{
	int		steps;
	float	xinc;
	float	yinc;
	float	x;
	float	y;

	if (abs(end_point.x - start_point.x) > abs(end_point.y - start_point.y))
		steps = abs(end_point.x - start_point.x);
	else
		steps = abs(end_point.y - start_point.y);
	xinc = (end_point.x - start_point.x) / (float)steps;
	yinc = (end_point.y - start_point.y) / (float)steps;
	x = start_point.x;
	y = start_point.y;
	while (--steps >= 0)
	{
		plot(round(x), round(y), cub, color);
		x += xinc;
		y += yinc;
	}
}
