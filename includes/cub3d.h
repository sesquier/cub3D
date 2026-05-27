/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:26:44 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 18:52:47 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../LIBFT/libft.h"

# define WIDTH	2560
# define HEIGHT	1440
# define MOVE_SPEED 3.0
# define ROT_SPEED 3.0
# define PLAYER_RADIUS 0.2

typedef struct s_game t_game;
typedef struct s_parse_error t_parse_error;
typedef struct s_flood t_flood;

typedef struct s_image
{
	void	*img_ptr;
	char	*pixels;
	int		bits_per_pixels;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_parse_error
{
	int		fd;
	char	*line;
	char	**grid_copy;
}	t_parse_error;

typedef struct s_map
{
	char	**grid;
	int		width; // largeur
	int		height; // hauteur  
}	t_map;

typedef struct s_flood
{
	char	**grid;
	int		width;
	int		height;
}	t_flood;

typedef struct s_texture
{
	char	*path;
	char	*pixels;
	void	*img_ptr;
	int		tex_width;
	int		tex_height;
	int		bits_per_pixels;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plan_x;
	double	plan_y;
	int		move_forward;
	int		move_back;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	wall_dist;
	double	wall_hit;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		wall_height;
	int		tex_col;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;
	t_image		render;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	int			floor_color[3];
	int			ceil_color[3];
	t_map		map;
	t_player	player;
	double		last_time;
	double		delta_time;
	t_flood		*f;
}	t_game;

// Parsing
void		parse(t_game *game, int ac, char **av);
void		file_name_checker(char *file, t_game *game);
void		parse_pass1(t_game *game, char *file);
void		parse_pass2(t_game *game, char *file);
void		parse_error(t_game *game, char *msg, t_parse_error err);
bool		is_map_line(char *line);
void		line_parser(char *line, t_game *game, int fd);
void		put_infos(t_game *game, char *idx, char *infos);
void		take_infos(t_game *game, char *line, char *idx);
void		check_config_complete(t_game *game);
void		check_player(t_game *game);
void		alloc_map(t_game *game);
void		check_map_closed(t_game *game);
void		colors_infos(t_game *game, int fd, char *line, char *idx, char *num, int count);
void		take_numbers(t_game *game, char *line, char *idx, int fd);
void		fill_map_line(t_game *game, char *line, int row);
void		process_lines_pass2(t_game *game, int fd);
int			skip_spaces(char *line);

// Init
int			handle_close(void *param);
int			handle_keypress(int keysym, void *param);
int			handle_keyrelease(int keysym, void *param);
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
void		init_texture(t_texture *tex);
void		init_player(t_player *player);
void		init_game(t_game *game);
int			init_mlx(t_game *game);
int			init_north(t_game *game);
int			init_south(t_game *game);
int			init_west(t_game *game);
int			init_east(t_game *game);
void		init_tex(t_game *game);
void		init_player_vectors(t_game *game);
double		get_current_time(void);
void		set_delta_time(t_game *game, double current);

// DDA
void		init_ray(t_game *game, t_ray *ray, int x);
void		dda_loop(t_game *game, t_ray *ray);
void		calc_wall_dist(t_ray *ray);
void		calc_wall_height(t_game *game, t_ray *ray);
void		calc_text_col(t_ray *ray, t_texture *texture, t_game *game);
t_texture	*choose_tex(t_game *game, t_ray *ray);
int			read_pix(t_texture *texture, int tex_col, int tex_row);
void		write_pix(t_image *render, int x, int y, int color);
void		draw_col(t_game *game, t_ray *ray, int x);
int			rgb_to_int(int *color);
char		**alloc_grid_copy(t_game *game);

// Render
void		cast_ray(t_game *game, t_ray *ray, int x);
int			render(void *param);
int			is_walkable(t_game *game, double x, double y);
void		move_forward(t_game *game);
void		move_back(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);
void		update_player(t_game *game);

// Errors & debug
void		err_incorrect_file(char *file);
void		free_game(t_game *game);
void		debug_game(t_game *game);

#endif