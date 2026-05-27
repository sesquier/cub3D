/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_loop3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:43:25 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/26 19:04:34 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		write_pix(&game->render, x, y, rgb_to_int(game->ceil_color));
		y++;
	}
}

static void	draw_wall(t_game *game, t_ray *ray, t_texture *tex, int x)
{
	int		y;
	int		relative_pos;
	double	ratio;
	int		tex_row;

	if (ray->draw_start < 0)
		y = 0;
	else
		y = ray->draw_start;
	while (y <= ray->draw_end && y < game->win_height)
	{
		relative_pos = y - ray->draw_start;
		ratio = (double)relative_pos / (double)ray->wall_height;
		tex_row = (int)(ratio * tex->tex_height);
		if (tex_row >= tex->tex_height)
			tex_row = tex->tex_height - 1;
		write_pix(&game->render, x, y, read_pix(tex, ray->tex_col, tex_row));
		y++;
	}
	while (y < game->win_height)
	{
		write_pix(&game->render, x, y, rgb_to_int(game->floor_color));
		y++;
	}
}

void	draw_col(t_game *game, t_ray *ray, int x)
{
	t_texture	*texture;

	texture = choose_tex(game, ray);
	if (!texture || !texture->pixels)
		return ;
	calc_text_col(ray, texture, game);
	draw_ceiling(game, ray, x);
	draw_wall(game, ray, texture, x);
}
