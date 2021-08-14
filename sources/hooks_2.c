/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:38:14 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/06/10 22:53:04 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys.h"

int				mouse_press(int button, int x, int y, t_screen *s)
{
	double		re;
	double		im;
	double		zoom;

	if ((button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN) &&
			x > MENU_WIDTH && x < MENU_WIDTH + SCREEN_SIZE &&
			y > 0 && y < SCREEN_SIZE)
	{
		re = s->r0 + (s->r1 - s->r0) * (x - MENU_WIDTH) / (SCREEN_SIZE - 1);
		im = s->i1 - (s->i1 - s->i0) * y / (SCREEN_SIZE - 1);
		zoom = (button == MOUSE_SCROLL_UP) ? 1.2 : 0.8;
		s->r0 = re + (s->r0 - re) / zoom;
		s->r1 = re + (s->r1 - re) / zoom;
		s->i0 = im + (s->i0 - im) / zoom;
		s->i1 = im + (s->i1 - im) / zoom;
		draw_screen(s);
	}
	return (0);
}

int				mouse_move(int x, int y, t_screen *s)
{
	if (s->is_mouse_on && x >= MENU_WIDTH && x <= MENU_WIDTH + SCREEN_SIZE &&
			y >= 0 && y <= SCREEN_SIZE)
	{
		s->julia_re = 4 * ((double)(x - MENU_WIDTH) / SCREEN_SIZE - 0.5);
		s->julia_im = 4 * ((double)(SCREEN_SIZE - y) / SCREEN_SIZE - 0.5);
		draw_screen(s);
	}
	return (0);
}

int				win_close(void *param)
{
	(void)param;
	exit(0);
}

void			throw(char *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}
