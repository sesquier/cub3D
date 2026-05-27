/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:11:46 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 19:04:39 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(int x, int y, t_game *game, char **grid_copy)
{
	t_parse_error	err;

	err.fd = -1;
	err.line = NULL;
	err.grid_copy = grid_copy;
	if (x < 0 || y < 0 || x >= game->f->width || y >= game->f->height)
		parse_error(game, "Error: map is not closed", err);
	if (game->f->grid[y][x] == '1' || game->f->grid[y][x] == 'V')
		return ;
	if (game->f->grid[y][x] == ' ')
		parse_error(game, "Error: map is not closed", err);
	game->f->grid[y][x] = 'V';
	flood_fill(x + 1, y, game, grid_copy);
	flood_fill(x - 1, y, game, grid_copy);
	flood_fill(x, y + 1, game, grid_copy);
	flood_fill(x, y - 1, game, grid_copy);
}

static void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

static void	search_and_flood(char **grid_copy, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->f->height)
	{
		x = 0;
		while (x < game->f->width)
		{
			if (ft_strchr("NSEW", grid_copy[y][x]))
			{
				flood_fill(x, y, game, grid_copy);
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

	game->f = NULL;
	f.grid = grid_copy;
	f.width = game->map.width;
	f.height = game->map.height;
	game->f = &f;
	search_and_flood(grid_copy, game);
	game->f = NULL;
}

void	check_map_closed(t_game *game)
{
	char	**grid_copy;

	grid_copy = alloc_grid_copy(game);
	find_and_flood(game, grid_copy);
}
