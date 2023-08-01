/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:55:59 by huolivei          #+#    #+#             */
/*   Updated: 2022/12/18 23:13:04 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_hold(char *str)
{
	int		i;
	int		i1;
	char	*hold;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	hold = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	i++;
	i1 = 0;
	while (str[i])
		hold[i1++] = str[i++];
	free(str);
	return (hold);
}

static char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n' || str[i] == '\0')
		line[i] = str[i];
	return (line);
}

static char	*ft_free(char *str, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(str, buf);
	free(str);
	return (tmp);
}

static char	*ft_buffer_reader(int fd, char *str)
{
	char	*buffer;
	int		i;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	i = 1;
	while (!ft_strchr(buffer, '\n') && i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		str = ft_free(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str = ft_buffer_reader(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	left_str = ft_hold(left_str);
	return (line);
}

int main()
{
	char *line;
	int fd = open("multiple_line_no_nl", O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
}
