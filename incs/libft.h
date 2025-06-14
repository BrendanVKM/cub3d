/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:01:01 by bvkm              #+#    #+#             */
/*   Updated: 2025/05/07 01:38:39 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <bsd/string.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_free_tab(char ***tab);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *ptr, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				*ft_memset(void *ptr, int value, size_t count);
void				*ft_memchr(const void *ptr, int c, size_t len);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isnum(char *str);
int					ft_lstsize(t_list *lst);
int					ft_atoi(const char *str);
int					ft_white_space(const char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t n);

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t len);

char				*ft_itoa(int n);
char				*ft_strdup(const char *src);
char				**ft_split(const char *s, char c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);

t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif