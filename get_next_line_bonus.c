/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:52:52 by vdecleir          #+#    #+#             */
/*   Updated: 2023/11/28 17:06:54 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*leftover(char	*stock)
{
	unsigned int	i;
	char			*temp;

	i = 0;
	if (!stock)
		return (NULL);
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock[i] == '\n')
	{
		temp = ft_substr(stock, i + 1);
		stock = temp;
	}
	else
		stock[0] = '\0';
	return (stock);
}

static char	*clean_stock(char *stock, unsigned int i)
{
	char			*next_line;

	if (!stock)
		return (NULL);
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock[i] == '\n')
		i++;
	next_line = ft_calloc(i + 1, sizeof(char));
	if (!next_line)
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i])
	{
		next_line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
	{
		next_line[i] = '\n';
		i++;
	}
	next_line[i] = '\0';
	return (next_line);
}

static char	*add_stock(int fd, char *stock, int char_read)
{
	char	buf[BUFFER_SIZE + 1];

	if (!stock)
		stock = ft_calloc(1, 1);
	while (char_read > 0)
	{
		if (ft_strchr(stock, '\n') != 0)
			break ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(stock);
			stock = NULL;
			buf[0] = '\0';
			return (NULL);
		}
		buf[char_read] = '\0';
		stock = ft_strjoin(stock, buf, 0, 0);
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock[OPEN_MAX];
	char		*next_line;

	if (fd < 0)
		return (NULL);
	stock[fd] = add_stock(fd, stock[fd], 1);
	if (!stock[fd] || stock[fd][0] == '\0')
	{
		free(stock[fd]);
		stock[fd] = NULL;
		return (NULL);
	}
	next_line = clean_stock(stock[fd], 0);
	if (!next_line)
	{
		free(stock[fd]);
		stock[fd] = NULL;
	}
	stock[fd] = leftover(stock[fd]);
	return (next_line);
}
