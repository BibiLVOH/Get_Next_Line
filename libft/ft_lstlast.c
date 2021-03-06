/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvigne <bvigne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:15:40 by bvigne            #+#    #+#             */
/*   Updated: 2017/12/06 18:47:25 by bvigne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *list)
{
	int		i;

	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	return (list);
}
