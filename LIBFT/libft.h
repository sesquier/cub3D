/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:21:23 by sesquier          #+#    #+#             */
/*   Updated: 2026/05/27 15:25:42 by sesquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define SIZE_MAX 2147483647
# define SIZE_MIN -2147483648

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <bsd/string.h>
# include <stddef.h>
# include <limits.h>
# include <ctype.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/uio.h>

int		ft_atoi(const char *nptr);
long	ft_atol(const char *str);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
bool	ft_iswhitespace(char c);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
int		ft_strlen(const char *s);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*GNL*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_MAX 1048576

char	*get_next_line(int fd);
char	*ft_substr1(char *s, unsigned int start, size_t len);
char	*ft_strdup1(char *s);
size_t	ft_strlen1(char *s);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strchr1(char *s, int c);

/*ft_printf*/
int		ft_printf(const char *format, ...);
int		ft_intputstr(char *s);
int		ft_intputnbr(int n);
int		ft_intputchar(int c);
int		ft_intputunsignedint(unsigned int n);
int		ft_intputpadress(void *p);
int		ft_intputnbrbase(unsigned long long nbr, char *base);
int		ft_intputlowhex(unsigned long long n);
int		ft_intputupphex(unsigned long long n);

#endif
