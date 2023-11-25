/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:01:19 by vdecleir          #+#    #+#             */
/*   Updated: 2023/11/23 21:42:15 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
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
	static char	*stock;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	stock = add_stock(fd, stock, 1);
	if (stock == NULL || stock[0] == '\0')
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	next_line = clean_stock(stock, 0);
	stock = leftover(stock);
	return (next_line);
}

// #include <fcntl.h>
// #include <stdio.h>


// int main()
// {
// 	int fd = open("big", O_RDONLY);
// 	char	*str;
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	close(fd);
// }