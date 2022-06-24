/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:50:11 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/05/23 10:06:15 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char		*buffer_static[FOPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer_static[fd] = ft_read_file(buffer_static[fd], fd);
	if (!buffer_static[fd])
		return (NULL);
	line = ft_get_line(buffer_static[fd]);
	buffer_static[fd] = ft_place_buffer(buffer_static[fd]);
	return (line);
}	

char	*ft_read_file(char	*buffer_static, int fd)
{
	char	*buffer_file;
	int		num_bytes_read;

	buffer_file = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer_file)
		return (NULL);
	num_bytes_read = 1;
	while (num_bytes_read > 0)
	{
		num_bytes_read = read(fd, buffer_file, BUFFER_SIZE);
		if (num_bytes_read == -1)
		{
			free(buffer_file);
			return (NULL);
		}
		buffer_file[num_bytes_read] = 0;
		buffer_static = ft_concatenation(buffer_static, buffer_file);
		if (ft_strchr(buffer_file, '\n'))
			break ;
	}
	free (buffer_file);
	return (buffer_static);
}

char	*ft_concatenation(char *buff_static, char *buff_file)
{
	char	*res;

	res = ft_strjoin(buff_static, buff_file);
	free(buff_static);
	return (res);
}

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_place_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free (buffer);
	return (new_buffer);
}
