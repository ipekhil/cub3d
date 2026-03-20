/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:43:13 by hiipek            #+#    #+#             */
/*   Updated: 2024/12/28 18:32:22 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd, int mode);
char	*ft_read_line(char *dst, int fd);
char	*ft_get_line(char *dst);
char	*ft_get_left_line(char *buff);

size_t	ft_gnl_strlen(const char *str);
char	*ft_gnl_strchr(const char *str, int c);
char	*ft_gnl_strjoin(char *s1, char const *s2);

#endif