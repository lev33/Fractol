/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:36:28 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/08/07 19:00:44 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys.h"

static void	move(int key, t_screen *s)
{
	double		re;
	double		im;

	re = s->r1 - s->r0;
	im = s->i1 - s->i0;
	if (key == ARROW_LEFT || key == ARROW_RIGHT)
	{
		s->r0 -= (key == ARROW_RIGHT) ? re * 0.05 : -re * 0.05;
		s->r1 -= (key == ARROW_RIGHT) ? re * 0.05 : -re * 0.05;
	}
	else
	{
		s->i0 -= (key == ARROW_UP) ? im * 0.05 : -im * 0.05;
		s->i1 -= (key == ARROW_UP) ? im * 0.05 : -im * 0.05;
	}
}

static void	change_limit(int key, t_screen *s)
{
	if (key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS)
	{
		if (s->limit < 40)
			s->limit += 1;
		else if (s->limit < 1000000000)
			s->limit = (int)(s->limit * 1.05);
	}
	else
	{
		if (s->limit > 40)
			s->limit = (int)(s->limit * 0.95);
		else if (s->limit > 1)
			s->limit -= 1;
	}
}

static void	change_fractal(int key, t_screen *s)
{
	if (key == MAIN_PAD_M)
		s->fractal = &mandelbrot;
	else if (key == MAIN_PAD_J)
		s->fractal = &julia;
	else if (key == MAIN_PAD_1)
		s->fractal = &cubic_mandelbrot;
	else if (key == MAIN_PAD_2)
		s->fractal = &c_mandelbrot;
	else if (key == MAIN_PAD_3)
		s->fractal = &p_mandelbrot;
	else if (key == MAIN_PAD_4)
		s->fractal = &mandelbar;
	else if (key == MAIN_PAD_5)
		s->fractal = &c_mandelbar;
	else if (key == MAIN_PAD_6)
		s->fractal = &c_perpendicular;
	else if (key == MAIN_PAD_7)
		s->fractal = &burning_ship;
	else if (key == MAIN_PAD_8)
		s->fractal = &p_burning_ship;
	else if (key == MAIN_PAD_9)
		s->fractal = &p_buffalo;
	else if (key == MAIN_PAD_0)
		s->fractal = &heart_mandelbrot;
	set_limits(s);
}

int			key_press(int key, t_screen *s)
{
	if (key == MAIN_PAD_ESC)
		exit(0);
	else if (key == MAIN_PAD_1 || key == MAIN_PAD_2 || key == MAIN_PAD_3 ||
			key == MAIN_PAD_4 || key == MAIN_PAD_5 || key == MAIN_PAD_6 ||
			key == MAIN_PAD_7 || key == MAIN_PAD_8 || key == MAIN_PAD_9 ||
			key == MAIN_PAD_0 || key == MAIN_PAD_M || key == MAIN_PAD_J)
		change_fractal(key, s);
	else if (key == MAIN_PAD_SPACE)
		set_limits(s);
	else if (key == MAIN_PAD_MINUS || key == NUM_PAD_MINUS
			|| key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS)
		change_limit(key, s);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
			|| key == ARROW_UP || key == ARROW_DOWN)
		move(key, s);
	else if (key == MAIN_PAD_C)
		s->rgb_shift = (s->rgb_shift + 1) % 3;
	else if (key == MAIN_PAD_B)
		s->is_mouse_on = (s->is_mouse_on) ? 0 : 1;
	draw_screen(s);
	return (0);
}
