/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:59:21 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/29 16:19:35 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, ray, x);
	dda_loop(game, ray);
	calc_wall_dist(ray);
	calc_wall_height(game, ray);
	draw_col(game, ray, x);
}

int	render(void *param)
{
	int		x;
	t_ray	ray;
	t_game	*game;
	double	current;

	x = 0;
	game = (t_game *)param;
	current = get_current_time();
	set_delta_time(game, current);
	update_player(game);
	while (x < game->win_width)
	{
		cast_ray(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->render.img_ptr, 0, 0);
	return (0);
}
