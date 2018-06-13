/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvigne <bvigne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:41:19 by bvigne            #+#    #+#             */
/*   Updated: 2018/05/22 13:06:32 by bvigne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*get_end(t_file *file, char **line)
{
	int		nl;
	char	*tmp;

	if ((nl = ft_strclen(file->buf, '\n')) != -1)
	{
		file->endline = 1;
		*line = ft_strndup(file->buf, nl - 1);
		tmp = ft_strdup(file->buf + nl + 1);
		ft_strdel(&file->buf);
		return (tmp);
	}
	else if (file->eof == 1)
	{
		*line = ft_strdup(file->buf);
		ft_strdel(&file->buf);
		return (NULL);
	}
	return (file->buf);
}

int					get_line(t_file *file, char **line)
{
	int		len;
	char	add[BUFF_SIZE + 1];

	len = 1;
	printf("fd : %d\n", file->fd);
	printf("test\n");
	if (file->buf == NULL)
		file->buf = ft_strdup("");
	printf("test\n");
	while (len > 0 && file->buf != NULL && file->endline != 1)
	{
		if ((len = read(file->fd, add, BUFF_SIZE)) == -1)
		{
			file->error = 1;
			return (0);
		}
		// printf("test\n");
		if (len == 0)
			file->eof = 1;
		add[len] = '\0';
		file->buf = ft_strjoinfree(file->buf, add);
		file->buf = get_end(file, line);
		// printf("endline : %d\n", file->endline);
		printf("buf : %s\n", file->buf);
		if (file->endline == 1)
			return (1);
		else if (file->eof && file->buf == NULL)
			return (0);
	}
	return (0);
}

static t_file		*new_fd(t_file **file, int len, int fd)
{
	t_file		*new;
	int 		i;

	i = 0;
	if (!(new = (t_file*)malloc(sizeof(t_file) * len + 1)))
		return (NULL);
	while (file[i])
	{
		new[i].idx = file[i]->idx;
		new[i].fd = file[i]->fd;
		new[i].buf = file[i]->buf;
		new[i].endline = file[i]->endline;;
		new[i].eof = file[i]->eof;;
		new[i].error = file[i]->error;;
		i++;
	}
	new[i].idx = len + 1;
	new[i].fd = fd;
	new[i].buf = NULL;
	new[i].endline = 0;
	new[i].eof = 0;
	new[i].error = 0;
	new[i + 1].idx = 0;
	return (new);
}

int					get_next_line(const int fd, char **line)
{
	static t_file		*files = NULL;
	int					cur;

	printf("newline\n");
	if (fd < 0 || line == NULL)
		return (-1);
	cur = 0;
	while (files && files[cur].idx)
	{
		if (files[cur].fd == fd && files[cur].eof != 1)
		{
			files[cur].endline = 0;
			if (get_line(&files[cur], line) == 0)
				return (files[cur].error) ? -1 : 0;
			return (1);
		}
		cur++;
	}
	files = new_fd(&files, cur, fd);
	printf("files[0] : %d\n", files[0].fd);
	printf("files[1] : %d\n", files[1].fd);
	printf("cur = %d\n", cur);
	if (get_line(&files[cur], line) == 0)
		return (files->error) ? -1 : 0;
	return (1);
}
