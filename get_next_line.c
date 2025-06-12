/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusliu <yusliu@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:56:23 by yusliu            #+#    #+#             */
/*   Updated: 2025/03/03 19:31:40 by yusliu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_from_fd(int fd, char *buffer, ssize_t *bytes_read)
{
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read < 0)
	{
		free(buffer);
		return (-1);
	}
	buffer[*bytes_read] = '\0';
	return (0);
}

static int	read_and_store(int fd, char **remainder)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = 1;
	if (!*remainder)
		*remainder = ft_strdup("");
	while (!ft_strchr(*remainder, '\n') && bytes_read != 0)
	{
		if (read_from_fd(fd, buffer, &bytes_read) == -1)
			return (-1);
		temp = ft_strjoin(*remainder, buffer);
		if (!temp)
		{
			free(buffer);
			return (-1);
		}
		free(*remainder);
		*remainder = temp;
	}
	free(buffer);
	return (0);
}

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*temp;
	size_t	len;

	len = 0;
	while ((*remainder)[len] && (*remainder)[len] != '\n')
		len++;
	if ((*remainder)[len] == '\n')
		len++;
	line = ft_substr(*remainder, 0, len);
	if (!line)
		return (NULL);
	temp = ft_strdup(*remainder + len);
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	free(*remainder);
	*remainder = temp;
	return (line);
}

static void	cleanup_remainder(char **remainder)
{
	if (*remainder)
	{
		free(*remainder);
		*remainder = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_and_store(fd, &remainder) == -1)
	{
		cleanup_remainder(&remainder);
		return (NULL);
	}
	if (!remainder || *remainder == '\0')
	{
		cleanup_remainder(&remainder);
		return (NULL);
	}
	line = extract_line(&remainder);
	if (!line)
		cleanup_remainder(&remainder);
	return (line);
}
