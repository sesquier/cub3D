/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:49:47 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 12:24:49 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_map_line(t_game *game, char *line);
void		parse_pass1(t_game *game, char *file);
void		parse_pass2(t_game *game, char *file);

void	parse(t_game *game, int ac, char **av)
{
	if (ac != 2)
	{
		ft_putendl_fd("Error: usage is ./cub3d <map.cub>", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	file_name_checker(av[1], game);
	parse_pass1(game, av[1]);
	check_config_complete(game);
	check_player(game);
	alloc_map(game);
	parse_pass2(game, av[1]);
	check_map_closed(game);
}

static void	process_map_line(t_game *game, char *line)
{
	int	i;

	i = 0;
	game->map.height += 1;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
		{
			ft_putendl_fd("Error: invalid character in map", 2);
			free_game(game);
			exit(EXIT_FAILURE);
		}
		if (ft_strchr("NSEW", line[i]))
		{
			if (game->player.dir != 0)
			{
				ft_putendl_fd("Error: multiple players in map", 2);
				free_game(game);
				exit(EXIT_FAILURE);
			}
			game->player.dir = line[i];
		}
		i++;
	}
	if (i > game->map.width)
		game->map.width = i;
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

static void	process_lines_pass1(t_game *game, int fd)
{
	char	*line;
	bool	map_started;

	map_started = false;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started && is_map_line(line))
			map_started = true;
		if (map_started)
			process_map_line(game, line);
		else
			line_parser(line, game);
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_pass1(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_incorrect_file(file);
	process_lines_pass1(game, fd);
	gnl_clear(fd);
	close(fd);
}
