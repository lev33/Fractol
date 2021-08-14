/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:25:17 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/06/10 16:25:32 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandelbar(double re, double im, t_screen *s)
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
		im = -2.0 * tmp * im + im0;
		n++;
	}
	return (n);
}

int		c_mandelbar(double re, double im, t_screen *s)
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
		im = -2.0 * tmp * im + im0;
		n++;
	}
	return (n);
}
