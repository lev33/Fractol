/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:38:35 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/06/10 11:41:58 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		burning_ship(double re, double im, t_screen *s)
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
		im = -2.0 * fabs(tmp * im) + im0;
		n++;
	}
	return (n);
}

int		p_burning_ship(double re, double im, t_screen *s)
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
		im = -2.0 * tmp * fabs(im) + im0;
		n++;
	}
	return (n);
}

int		p_buffalo(double re, double im, t_screen *s)
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
		im = -2.0 * tmp * fabs(im) + im0;
		n++;
	}
	return (n);
}

int		c_perpendicular(double re, double im, t_screen *s)
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
		im = -2.0 * fabs(tmp) * im + im0;
		n++;
	}
	return (n);
}

int		julia(double re, double im, t_screen *s)
{
	int			n;
	double		tmp;

	n = 0;
	while (re * re + im * im <= 4 && n < s->limit)
	{
		tmp = re;
		re = re * re - im * im + s->julia_re;
		im = 2.0 * tmp * im + s->julia_im;
		n++;
	}
	return (n);
}
