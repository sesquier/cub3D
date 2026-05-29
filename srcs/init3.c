/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:26:49 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/29 15:48:09 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir = 0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plan_x = 0.0;
	player->plan_y = 0.0;
	player->move_forward = 0;
	player->move_back = 0;
	player->move_left = 0;
	player->move_right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
}

void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->win_width = 0;
	game->win_height = 0;
	game->render.img_ptr = NULL;
	game->render.pixels = NULL;
	game->render.bits_per_pixels = 0;
	game->render.line_length = 0;
	game->render.endian = 0;
	init_texture(&game->north);
	init_texture(&game->south);
	init_texture(&game->west);
	init_texture(&game->east);
	game->floor_color[0] = -1;
	game->floor_color[1] = -1;
	game->floor_color[2] = -1;
	game->ceil_color[0] = -1;
	game->ceil_color[1] = -1;
	game->ceil_color[2] = -1;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	init_player(&game->player);
	game->last_time = get_current_time();
	game->delta_time = 0;
}

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "cub3D");
	game->render.img_ptr = mlx_new_image(game->mlx_ptr, 1920, 1080);
	game->render.pixels = mlx_get_data_addr(game->render.img_ptr,
			&game->render.bits_per_pixels,
			&game->render.line_length,
			&game->render.endian);
	return (0);
}
