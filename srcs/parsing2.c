/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:01:51 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 16:34:18 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	line_parser(char *line, t_game *game, int fd)
{
	int	start;

	if (!line)
		return ;
	start = skip_spaces(line);
	if (ft_strncmp(line + start, "NO ", 3) == 0)
		take_infos(game, line + start, "NO");
	else if (ft_strncmp(line + start, "SO ", 3) == 0)
		take_infos(game, line + start, "SO");
	else if (ft_strncmp(line + start, "WE ", 3) == 0)
		take_infos(game, line + start, "WE");
	else if (ft_strncmp(line + start, "EA ", 3) == 0)
		take_infos(game, line + start, "EA");
	else if (ft_strncmp(line + start, "F ", 2) == 0)
		take_numbers(game, line + start, "F", fd);
	else if (ft_strncmp(line + start, "C ", 2) == 0)
		take_numbers(game, line + start, "C", fd);
}

void	fill_map_line(t_game *game, char *line, int row)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			game->player.pos_x = i + 0.5;
			game->player.pos_y = row + 0.5;
			game->player.dir = line[i];
		}
		game->map.grid[row][i] = line[i];
		i++;
	}
}

void	process_lines_pass2(t_game *game, int fd)
{
	char	*line;
	bool	map_started;
	int		row;

	map_started = false;
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started && is_map_line(line))
			map_started = true;
		if (map_started)
		{
			fill_map_line(game, line, row);
			row++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_pass2(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_incorrect_file(file);
	process_lines_pass2(game, fd);
	close(fd);
}
