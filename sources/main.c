/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:33:50 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/06/10 22:52:07 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void				set_fractal(t_screen *s, char *name)
{
	if (ft_strequ(name, "Mandelbrot"))
		s->fractal = &mandelbrot;
	else if (ft_strequ(name, "Cubic Mandelbrot"))
		s->fractal = &cubic_mandelbrot;
	else if (ft_strequ(name, "Heart Mandelbrot"))
		s->fractal = &heart_mandelbrot;
	else if (ft_strequ(name, "Celtic Mandelbrot"))
		s->fractal = &c_mandelbrot;
	else if (ft_strequ(name, "Perpendicular Mandelbrot"))
		s->fractal = &p_mandelbrot;
	else if (ft_strequ(name, "Mandelbar"))
		s->fractal = &mandelbar;
	else if (ft_strequ(name, "Celtic Mandelbar"))
		s->fractal = &c_mandelbar;
	else if (ft_strequ(name, "Celtic Perpendicular"))
		s->fractal = &c_perpendicular;
	else if (ft_strequ(name, "Burning Ship"))
		s->fractal = &burning_ship;
	else if (ft_strequ(name, "Perpendicular Burning Ship"))
		s->fractal = &p_burning_ship;
	else if (ft_strequ(name, "Perpendicular Buffalo"))
		s->fractal = &p_buffalo;
	else if (ft_strequ(name, "Julia"))
		s->fractal = &julia;
}

void					set_limits(t_screen *s)
{
	s->limit = 50;
	s->r0 = -2.0;
	s->r1 = 2.0;
	s->i0 = -2.0;
	s->i1 = 2.0;
	s->julia_re = 0.2;
	s->julia_im = 0.6;
	s->rgb_shift = 0;
	s->is_mouse_on = 0;
}

static t_screen			*new_screen(void *mlx, char *name)
{
	t_screen	*s;

	if (!(s = (t_screen *)ft_memalloc(sizeof(t_screen))))
		throw("Mallloc error");
	if (!(s->window = mlx_new_window(mlx, MENU_WIDTH + SCREEN_SIZE,
					SCREEN_SIZE, "Fractol")))
		throw("MiniLibX initialization error");
	if (!(s->image = mlx_new_image(mlx, MENU_WIDTH + SCREEN_SIZE, SCREEN_SIZE)))
		throw("MiniLibX initialization error");
	s->data_addr = mlx_get_data_addr(s->image, &(s->bits_per_pixel),
			&(s->size_line), &(s->endian));
	s->mlx = mlx;
	set_limits(s);
	set_fractal(s, name);
	mlx_hook(s->window, 2, 0, key_press, s);
	mlx_hook(s->window, 17, 0, win_close, s);
	mlx_hook(s->window, 4, 0, mouse_press, s);
	mlx_hook(s->window, 6, 0, mouse_move, s);
	return (s);
}

static int				check_argv(int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strequ(argv[i], "Mandelbrot") && !ft_strequ(argv[i], "Julia") &&
				!ft_strequ(argv[i], "Cubic Mandelbrot") &&
				!ft_strequ(argv[i], "Heart Mandelbrot") &&
				!ft_strequ(argv[i], "Mandelbar") &&
				!ft_strequ(argv[i], "Perpendicular Buffalo") &&
				!ft_strequ(argv[i], "Celtic Mandelbar") &&
				!ft_strequ(argv[i], "Celtic Mandelbrot") &&
				!ft_strequ(argv[i], "Celtic Perpendicular") &&
				!ft_strequ(argv[i], "Perpendicular Burning Ship") &&
				!ft_strequ(argv[i], "Perpendicular Mandelbrot") &&
				!ft_strequ(argv[i], "Burning Ship"))
			return (0);
	}
	return (1);
}

int						main(int argc, char **argv)
{
	int			i;
	t_screen	*scrs[SCREENS];
	void		*mlx;

	if (argc > 1 && argc <= SCREENS + 1 && check_argv(argc, argv))
	{
		if (!(mlx = mlx_init()))
			throw("MiniLibX initialization error");
		i = -1;
		while (++i < argc - 1)
		{
			scrs[i] = new_screen(mlx, argv[i + 1]);
			draw_screen(scrs[i]);
		}
		mlx_loop(mlx);
	}
	ft_putendl("Usage: ./fractol <name>\nNames: Mandelbrot, Julia, "
			"Burning Ship, Heart Mandelbrot, Cubic Mandelbrot, "
			"Mandelbar, Celtic Mandelbrot, Celtic Mandelbar, "
			"Celtic Perpendicular, Perpendicular Mandelbrot, "
			"Perpendicular Burning Ship, Perpendicular Buffalo");
	return (0);
}
