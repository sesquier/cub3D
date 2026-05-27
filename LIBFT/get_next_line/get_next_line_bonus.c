/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:58:32 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 16:04:40 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*append_char(char *line, char c)
{
	char	*new_line;
	size_t	len;
	size_t	i;

	len = 0;
	if (line)
		len = ft_strlen(line);
	new_line = malloc(len + 2);
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i++] = c;
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

static char	*read_line(int fd)
{
	char		*line;
	char		c;
	ssize_t		status;
	char		*tmp;

	line = NULL;
	status = 1;
	while (status > 0)
	{
		status = read(fd, &c, 1);
		if (status < 0)
			return (free(line), NULL);
		if (status == 0)
			break ;
		tmp = append_char(line, c);
		if (!tmp)
			return (free(line), NULL);
		line = tmp;
		if (c == '\n')
			break ;
	}
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	return (read_line(fd));
}
