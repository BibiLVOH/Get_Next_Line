/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfleming <tfleming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 11:52:59 by tfleming          #+#    #+#             */
/*   Updated: 2018/05/22 12:38:06 by bvigne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	int		sep;
	int		res;
	char	*line;

	sep = 1;
	res = 1;
	if (argc < 3)
		return (0);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	// printf("fd1 = %d // fd2 = %d\n", fd1, fd2);
	while (res == 1)
	{
		if (sep % 3 == 0)
		{
			res = get_next_line(fd1, &line);
			// printf("line fd1 : %s\n", line);
		}
		else
		{
			res = get_next_line(fd2, &line);
			// printf("line fd2 : %s\n", line);
		}
		free(line);
		sep++;
	}
	printf("res = %d\n", res);
	close(fd1);
	close(fd2);
	return (0);
}
