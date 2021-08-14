/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:31:09 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/08/07 18:59:39 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

t_rgb						get_rgb(double re, double im, t_screen *s)
{
	t_rgb	rgb;
	double	t;

	t = (double)s->fractal(re, im, s) / s->limit;
	rgb.color[s->rgb_shift % 3] =
		(int8_t)(9 * (1 - t) * pow(t, 3) * 255);
	rgb.color[(s->rgb_shift + 1) % 3] =
		(int8_t)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	rgb.color[(s->rgb_shift + 2) % 3] =
		(int8_t)(8.5 * pow((1 - t), 3) * t * 255);
	return (rgb);
}

static void					set_color(int x, int y, t_screen *s, t_rgb rgb)
{
	int	i;

	i = (x * s->bits_per_pixel / 8) + (y * s->size_line);
	s->data_addr[i] = rgb.color[2];
	s->data_addr[++i] = rgb.color[1];
	s->data_addr[++i] = rgb.color[0];
}

static void					*thread_func(void *arg)
{
	int			y;
	int			x;
	double		re;
	double		im;
	t_screen	*s;

	s = (t_screen*)arg;
	y = s->y0 - 1;
	while (++y < s->y1)
	{
		im = s->i1 - y * s->sizetoim;
		x = -1;
		while (++x < SCREEN_SIZE)
		{
			re = s->r0 + x * s->sizetore;
			set_color(x + MENU_WIDTH, y, s, get_rgb(re, im, s));
		}
	}
	return (NULL);
}

static void					print_menu(int y, void *mlx, void *win)
{
	mlx_string_put(mlx, win, 75, y += 20, COLOR1, "Keyboard");
	mlx_string_put(mlx, win, 15, y += 35, COLOR, "Esc        exit");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "Arrows     move");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "+ -    change precision");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "C        change color");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "B       coords in Julia");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "Space   reset fractal");
	mlx_string_put(mlx, win, 75, y += 45, COLOR1, "Fractals");
	mlx_string_put(mlx, win, 15, y += 35, COLOR, "M       Mandelbrot");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "J          Julia");
	mlx_string_put(mlx, win, 15, y += 35, COLOR, "1    Cubic Mandelbrot");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "2   Celtic Mandelbrot");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "3    Perp. Mandelbrot");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "4        Mandelbar");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "5    Celtic Mandelbar");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "6  Celtic Perpendicular");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "7       Burning Ship");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "8    Perp. Burning Ship");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "9        Perp. Buffalo");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "0      Heart Mandelbrot");
	mlx_string_put(mlx, win, 85, y += 40, COLOR1, "Mouse");
	mlx_string_put(mlx, win, 15, y += 30, COLOR, "Scroll        zoom");
}

void						draw_screen(t_screen *s)
{
	pthread_t	threads[THREADS];
	t_screen	scrs[THREADS];
	int			i;

	s->sizetore = (s->r1 - s->r0) / (SCREEN_SIZE - 1);
	s->sizetoim = (s->i1 - s->i0) / (SCREEN_SIZE - 1);
	ft_bzero(s->data_addr,
			(MENU_WIDTH + SCREEN_SIZE) * SCREEN_SIZE * (s->bits_per_pixel / 8));
	i = -1;
	while (++i < THREADS)
	{
		scrs[i] = *s;
		scrs[i].y0 = i * (SCREEN_SIZE / THREADS);
		scrs[i].y1 = (i + 1) * (SCREEN_SIZE / THREADS);
		if (pthread_create(&threads[i], NULL, thread_func, (void *)&scrs[i]))
			throw("Pthread error");
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			throw("Pthread error");
	mlx_put_image_to_window(s->mlx, s->window, s->image, 0, 0);
	print_menu(0, s->mlx, s->window);
}
