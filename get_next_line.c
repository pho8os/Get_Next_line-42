/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 08:56:33 by absaid            #+#    #+#             */
/*   Updated: 2022/10/26 17:19:12 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

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

char	*get_next_line(int fd)
{
	char		*line;
	static char	*hold;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(hold);
		return (NULL);
	}
	buffer[0] = 0;
	hold = read_line(fd, buffer, hold);
	if (!hold)
		return (NULL);
	if (!*hold)
	{
		free(hold);
		return (hold = 0, NULL);
	}
	return (line = get_line(hold), hold = update_hold(hold), line);
}
