/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:11:46 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 15:08:20 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(t_flood *f, int x, int y, t_game *game, char **grid_copy)
{
	if (x < 0 || y < 0 || x >= f->width || y >= f->height)
		parse_error(game, -1, NULL, grid_copy, "Error: map is not closed");
	if (f->grid[y][x] == '1' || f->grid[y][x] == 'V')
		return ;
	if (f->grid[y][x] == ' ')
		parse_error(game, -1, NULL, grid_copy, "Error: map is not closed");
	f->grid[y][x] = 'V';
	flood_fill(f, x + 1, y, game, grid_copy);
	flood_fill(f, x - 1, y, game, grid_copy);
	flood_fill(f, x, y + 1, game, grid_copy);
	flood_fill(f, x, y - 1, game, grid_copy);
}

static void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

static void	search_and_flood(t_flood *f, char **grid_copy, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			if (ft_strchr("NSEW", grid_copy[y][x]))
			{
				flood_fill(f, x, y, game, grid_copy);
				free_grid(grid_copy);
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	find_and_flood(t_game *game, char **grid_copy)
{
	t_flood	f;

	f.grid = grid_copy;
	f.width = game->map.width;
	f.height = game->map.height;
	search_and_flood(&f, grid_copy, game);
}

void	check_map_closed(t_game *game)
{
	char	**grid_copy;

	grid_copy = alloc_grid_copy(game);
	find_and_flood(game, grid_copy);
}
