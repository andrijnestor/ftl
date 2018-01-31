/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 21:09:28 by anestor           #+#    #+#             */
/*   Updated: 2018/01/31 22:41:45 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		color_grad(int start, int end, double perc)
{
	if (start == end)
		return (start);
	return ((int)((double)start + (end - start) * perc));
}

int		color(int c1, int c2, double perc)
{
	int r;
	int g;
	int b;

	if (c1 == c2)
		return (c1);
	r = color_grad((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, perc);
	g = color_grad((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc);
	b = color_grad(c1 & 0xFF, c2 & 0xFF, perc);
	return (r << 16 | g << 8 | b);
}

double	test_color(int i, t_ftl *ftl)
{
	double k;
	double j;

	j = i % 256;
	if (j < 100)
		k = j / 100;
	else
		k = j / 1000;
//	if (k >= 1)
//	printf("%f ", fmod(k * ftl->colDepth, 1.0));
	return (fmod(k / 100 *ftl->colDepth, 1.0));
}

void	img_pixel_put(t_ftl *ftl, int x, int y, int col)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	*(int *)(ftl->img->addr + ((x + y * WIN_W) * ftl->img->bpp)) = color(0xFF0000, 0x00FFFF, col / 30.0);
}

void	put_img(t_ftl *ftl)
{
	mlx_put_image_to_window(ftl->mlx, ftl->win, ftl->img->image, 0, 0);
}

void	create_img(t_ftl *ftl)
{
	ftl->img = ft_memalloc(sizeof(t_img));
	ftl->img->image = mlx_new_image(ftl->mlx, WIN_W, WIN_H);
	ftl->img->addr = mlx_get_data_addr(ftl->img->image, &ftl->img->bpp, 
			&ftl->img->size_line, &ftl->img->endian);
	ftl->img->bpp /= 8;
}
