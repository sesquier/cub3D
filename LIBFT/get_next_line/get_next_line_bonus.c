/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:58:32 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 11:56:24 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_feed_my_line(int fd, char *stash, char *buffer);
static char	*ft_clean_strings(char *line);

static char	*stash[FD_MAX];

void	gnl_clear(int fd)
{
    if (fd < 0 || fd >= FD_MAX)
        return ;
    free(stash[fd]);
    stash[fd] = NULL;
}

char	*get_next_line(int fd)
{
    char	*line;
    char	*buffer;

    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
        gnl_clear(fd);
        free(buffer);
        return (NULL);
    }
    line = ft_feed_my_line(fd, stash[fd], buffer);
    free(buffer);
    if (!line)
        return (NULL);
    stash[fd] = ft_clean_strings(line);
    return (line);
}

// char	*get_next_line(int fd)
// {
// 	static char	*stash[FD_MAX];
// 	char		*line;
// 	char		*buffer;

// 	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
// 	{
// 		free(stash[fd]);
// 		free(buffer);
// 		stash[fd] = NULL;
// 		buffer = NULL;
// 		return (NULL);
// 	}
// 	if (!buffer)
// 		return (NULL);
// 	line = ft_feed_my_line(fd, stash[fd], buffer);
// 	free(buffer);
// 	buffer = NULL;
// 	if (!line)
// 		return (NULL);
// 	stash[fd] = ft_clean_strings(line);
// 	return (line);
// }

static char	*ft_feed_my_line(int fd, char *stash, char *buffer)
{
	ssize_t	rd_bytes;
	char	*tmp;

	rd_bytes = 1;
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, buffer, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (rd_bytes == 0)
			break ;
		buffer[rd_bytes] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*ft_clean_strings(char *line)
{
	ssize_t	i;
	char	*stash;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*stash == 0)
	{
		free(stash);
		stash = NULL;
	}
	line[i + 1] = 0;
	return (stash);
}
