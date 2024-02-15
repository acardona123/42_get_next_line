/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:46:46 by acardona          #+#    #+#             */
/*   Updated: 2022/12/17 18:48:57 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_buffer	buff[1024];
	t_buffer		*b;
	char			*rtn;
	char			*tmp;

	if (fd < 0)
		return (0);
	b = buff + fd;
	if (ft_buffinit(fd, b, &rtn) == -1)
		return (0);
	while (rtn && b->e > 0
		&& ft_idn(b->t + b->s, b->e - b->s) == b->e - b->s)
		if (ft_newbuff(b, &rtn, fd) == -1)
			return (0);
	if (rtn && b->e > 0)
	{
		tmp = ft_join(rtn, b->t, b->s, ft_idn(b->t + b->s, b->e - b->s) + 1);
		free(rtn);
		rtn = tmp;
		b->s += ft_idn(b->t + b->s, b->e - b->s) + 1;
	}
	return (rtn);
}
