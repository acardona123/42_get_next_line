/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:49:27 by acardona          #+#    #+#             */
/*   Updated: 2022/11/24 11:55:32 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

typedef struct s_buffer
{
	char	t[BUFFER_SIZE];
	ssize_t	s;
	ssize_t	e;
}	t_buffer;

char	*get_next_line(int fd);
ssize_t	ft_idn(char *str, ssize_t max);
char	*ft_join(char *s1, char *s2, size_t s2_start, size_t s2_len);
int		ft_buffinit(int fd, t_buffer *b, char **rtn );
int		ft_newbuff(t_buffer *b, char **rtn, int fd);

#endif
