/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:27:09 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/06/10 16:44:44 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# define SCREEN_SIZE    1000
# define MENU_WIDTH		250
# define THREADS	    10
# define SCREENS	    10
# define COLOR  		0xEAEAEA
# define COLOR1	        0xFFFF00

# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdint.h>

typedef struct		s_screen
{
	void			*mlx;
	void			*window;
	void			*image;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	double			r0;
	double			r1;
	double			i0;
	double			i1;
	int				y0;
	int				y1;
	int				limit;
	double			sizetore;
	double			sizetoim;
	double			julia_re;
	double			julia_im;
	int				is_mouse_on;
	int				rgb_shift;
	int				(*fractal)(double re, double im, struct s_screen *s);
}					t_screen;

typedef	struct		s_rgb
{
	int8_t			color[3];
}					t_rgb;

void				set_limits(t_screen *s);
void				draw_screen(t_screen *s);
int					mandelbrot(double re, double im, t_screen *s);
int					cubic_mandelbrot(double re, double im, t_screen *s);
int					julia(double re, double im, t_screen *s);
int					burning_ship(double re, double im, t_screen *s);
int					mandelbar(double re, double im, t_screen *s);
int					c_mandelbrot(double re, double im, t_screen *s);
int					c_mandelbar(double re, double im, t_screen *s);
int					c_perpendicular(double re, double im, t_screen *s);
int					heart_mandelbrot(double re, double im, t_screen *s);
int					p_mandelbrot(double re, double im, t_screen *s);
int					p_burning_ship(double re, double im, t_screen *s);
int					p_buffalo(double re, double im, t_screen *s);
t_rgb				get_rgb(double re, double im, t_screen *s);
int					win_close(void *param);
int					key_press(int key, t_screen *s);
int					mouse_press(int button, int x, int y, t_screen *s);
int					mouse_move(int x, int y, t_screen *s);
void				throw(char *str);

#endif
