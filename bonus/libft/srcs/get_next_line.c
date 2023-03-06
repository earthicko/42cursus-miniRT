/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:08:41 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:50 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static int	read_line(t_list *buff_stored, int fd, char *buff_read)
{
	int		l_read;
	char	*temp;

	l_read = 1;
	while (l_read != 0 && ft_strchr(loc_fdbuff(buff_stored)->buff, '\n') == 0)
	{
		l_read = read(fd, buff_read, BUFFER_SIZE);
		if (l_read == -1)
			return (CODE_ERROR_IO);
		buff_read[l_read] = '\0';
		temp = ft_strjoin(loc_fdbuff(buff_stored)->buff, buff_read);
		free(loc_fdbuff(buff_stored)->buff);
		if (!temp)
			return (CODE_ERROR_MALLOC);
		loc_fdbuff(buff_stored)->buff = temp;
	}
	return (CODE_OK);
}

static char	*extract_line(t_list *buff_stored)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!loc_fdbuff(buff_stored)->buff[i])
		return (NULL);
	while (!ft_iseol(loc_fdbuff(buff_stored)->buff[i]))
		i++;
	new_line = malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	while (1)
	{
		new_line[i] = loc_fdbuff(buff_stored)->buff[i];
		if (ft_iseol(loc_fdbuff(buff_stored)->buff[i]))
			break ;
		i++;
	}
	i++;
	new_line[i] = '\0';
	return (new_line);
}

static void	update_buff(t_list **buff_list, t_list *buff_stored)
{
	size_t	len;
	size_t	len_new;
	size_t	i;
	char	*new_buff;

	len = 0;
	i = 0;
	while (!ft_iseol(loc_fdbuff(buff_stored)->buff[i]))
		i++;
	len_new = ft_strlen(loc_fdbuff(buff_stored)->buff) - i + 1;
	new_buff = malloc(len_new);
	if (loc_fdbuff(buff_stored)->buff[i] == '\0' || !new_buff)
	{
		del_fdlist(buff_list, buff_stored);
		if (new_buff)
			free(new_buff);
		return ;
	}
	i++;
	while (loc_fdbuff(buff_stored)->buff[i] != '\0')
		new_buff[len++] = loc_fdbuff(buff_stored)->buff[i++];
	new_buff[len] = '\0';
	free(loc_fdbuff(buff_stored)->buff);
	loc_fdbuff(buff_stored)->buff = new_buff;
}

static t_list	*assign_buff(t_list **buff_list, int fd)
{
	t_list	*cursor;

	cursor = *buff_list;
	while (cursor != NULL)
	{
		if (loc_fdbuff(cursor)->fd == fd)
			break ;
		cursor = cursor->next;
	}
	if (cursor == NULL)
	{
		cursor = init_fdlist(buff_list, fd);
		if (!cursor)
			return (NULL);
	}
	if (loc_fdbuff(cursor)->buff == NULL)
	{
		loc_fdbuff(cursor)->buff = malloc(sizeof(char));
		if (!loc_fdbuff(cursor)->buff)
			return (del_fdlist(buff_list, cursor));
		loc_fdbuff(cursor)->buff[0] = '\0';
	}
	return (cursor);
}

char	*get_next_line(int fd)
{
	char			*new_line;
	char			*buff_read;
	static t_list	*buff_list;
	t_list			*buff_stored;
	int				res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff_stored = assign_buff(&buff_list, fd);
	if (!buff_stored)
		return (NULL);
	buff_read = malloc((sizeof(char) * (BUFFER_SIZE + 1)));
	if (!buff_read)
		return (NULL);
	res = read_line(buff_stored, fd, buff_read);
	free(buff_read);
	if (res < 0)
		return (del_fdlist(&buff_list, buff_stored));
	new_line = extract_line(buff_stored);
	update_buff(&buff_list, buff_stored);
	return (new_line);
}
