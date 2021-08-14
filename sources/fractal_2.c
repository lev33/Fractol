/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:38:53 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/06/10 16:41:23 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandelbrot(double re, double im, t_screen *s)
{
	int			n;
	double		re0;
	double		im0;
	double		tmp;

	n = 0;
	re0 = re;
	im0 = im;
	while (re * re + im * im <= 4 && n < s->limit)
	{
		tmp = re;
		re = re * re - im * im + re0;
		im = 2.0 * tmp * im + im0;
		n++;
	}
	return (n);
}

int		cubic_mandelbrot(double re, double im, t_screen *s)
{
	int			n;
	double		re0;
	double		im0;
	double		tmp;

	n = 0;
	re0 = re;
	im0 = im;
	while (re * re + im * im <= 4 && n < s->limit)
	{
		tmp = re;
		re = (re * re - 3.0 * im * im) * re + re0;
		im = (3.0 * tmp * tmp - im * im) * im + im0;
		n++;
	}
	return (n);
}

int		p_mandelbrot(double re, double im, t_screen *s)
{
	int			n;
	double		re0;
	double		im0;
	double		tmp;

	n = 0;
	re0 = re;
	im0 = im;
	while (re * re + im * im <= 4 && n < s->limit)
	{
		tmp = re;
		re = re * re - im * im + re0;
		im = -2.0 * fabs(tmp) * im + im0;
		n++;
	}
	return (n);
}

int		c_mandelbrot(double re, double im, t_screen *s)
{
	int			n;
	double		re0;
	double		im0;
	double		tmp;

	n = 0;
	re0 = re;
	im0 = im;
	while (re * re + im * im <= 4 && n < s->limit)
	{
		tmp = re;
		re = fabs(re * re - im * im) + re0;
		im = 2.0 * tmp * im + im0;
		n++;
	}
	return (n);
}

int		heart_mandelbrot(double re, double im, t_screen *s)
{
	int			n;
	double		re0;
	double		im0;
	double		tmp;

	n = 0;
	re0 = re;
	im0 = im;
	while (re * re + im * im <= 4 && n < s->limit)
	{
		tmp = re;
		re = re * re - im * im + re0;
		im = 2.0 * fabs(tmp) * im + im0;
		n++;
	}
	return (n);
}
