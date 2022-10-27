/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:21:22 by absaid            #+#    #+#             */
/*   Updated: 2022/10/27 14:01:55 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

char	*read_line(int fd, char *buffer, char *hold)
{
	ssize_t	ret;
	char	*str;

	ret = 1;
	while (ret != 0 && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[ret] = 0;
		str = ft_strjoin(hold, buffer);
		free(hold);
		hold = str;
	}
	free(buffer);
	return (hold);
}

char	*get_line(char *hold)
{
	int		i;
	char	*s;

	i = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	s = ft_substr(hold, 0, i + 1);
	return (s);
}

char	*update_hold(char *hold)
{
	char	*s;
	int		i;

	i = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (hold[i] == '\n')
		i++;
	s = ft_substr(hold, i, ft_strlen(hold + i));
	free(hold);
	return (s);
}

char	*get_next_line_bonus(int fd)
{
	char		*line;
	static char	*hold[10241];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(hold[fd]);
		return (NULL);
	}
	buffer[0] = 0;
	hold[fd] = read_line(fd, buffer, hold[fd]);
	if (!hold[fd])
		return (NULL);
	if (!*hold[fd])
	{
		free(hold[fd]);
		return (hold[fd] = 0, NULL);
	}
	return (line = get_line(hold[fd]), hold[fd] = update_hold(hold[fd]), line);
}
