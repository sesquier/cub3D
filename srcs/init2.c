/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:25:25 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/29 16:07:38 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_north(t_game *game)
{
	game->north.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->north.path,
			&game->north.tex_width, &game->north.tex_height);
	if (!game->north.img_ptr)
		return (1);
	game->north.pixels = mlx_get_data_addr(game->north.img_ptr,
			&game->north.bits_per_pixels, &game->north.line_length,
			&game->north.endian);
	return (0);
}

int	init_south(t_game *game)
{
	game->south.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->south.path,
			&game->south.tex_width, &game->south.tex_height);
	if (!game->south.img_ptr)
		return (1);
	game->south.pixels = mlx_get_data_addr(game->south.img_ptr,
			&game->south.bits_per_pixels, &game->south.line_length,
			&game->south.endian);
	return (0);
}

int	init_west(t_game *game)
{
	game->west.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->west.path,
			&game->west.tex_width, &game->west.tex_height);
	if (!game->west.img_ptr)
		return (1);
	game->west.pixels = mlx_get_data_addr(game->west.img_ptr,
			&game->west.bits_per_pixels, &game->west.line_length,
			&game->west.endian);
	return (0);
}

int	init_east(t_game *game)
{
	game->east.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->east.path,
			&game->east.tex_width, &game->east.tex_height);
	if (!game->east.img_ptr)
		return (1);
	game->east.pixels = mlx_get_data_addr(game->east.img_ptr,
			&game->east.bits_per_pixels, &game->east.line_length,
			&game->east.endian);
	return (0);
}

// void	init_tex(t_game *game)
// {
// 	t_parse_error	err;
// 	if (init_north(game))
// 	{
// 		err.fd = -1;
// 		err.line = NULL;
// 		err.grid_copy = NULL;
// 		parse_error(game, "Error: failed to load north texture", err);
// 	}
// 	if (init_south(game))
// 	{
// 		err.fd = -1;
// 		err.line = NULL;
// 		err.grid_copy = NULL;
// 		parse_error(game, "Error: failed to load south texture", err);
// 	}
// 	if (init_west(game))
// 	{
// 		err.fd = -1;
// 		err.line = NULL;
// 		err.grid_copy = NULL;
// 		parse_error(game, "Error: failed to load west texture", err);
// 	}
// 	if (init_east(game))
// 	{
// 		err.fd = -1;
// 		err.line = NULL;
// 		err.grid_copy = NULL;
// 		parse_error(game, "Error: failed to load east texture", err);
// 	}
// }

void	init_tex(t_game *game)
{
	t_parse_error	err;

	if (init_north(game) || init_south(game) || init_west(game)
		|| init_east(game))
	{
		err.fd = -1;
		err.line = NULL;
		err.grid_copy = NULL;
		parse_error(game, "Error: failed to load a texture", err);
	}
}
