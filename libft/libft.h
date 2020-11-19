/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:08:42 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/28 20:01:51 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>

# define BUFFER_SIZE 10

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char				*ft_strrchr(const char *s, int c);

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

char				*ft_strdup(const char *s1);
void				*ft_calloc(size_t count, size_t size);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_nbdigit(long long int n);
char				*ft_itoa(long long int n);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
											void (*del)(void *));

char				*ft_strljoin(char const *s1, char const *s2,
								size_t n1, size_t n2);
void				ft_putnstr(char *s, size_t n);
void				ft_putrep(char c, int nb);
void				ft_putunbr(unsigned int n);
int					ft_unbdigit(unsigned int n);
char				*ft_itouhex(unsigned int n);
char				*ft_lltohex(unsigned long long int n);
int					ft_nbdigit16(unsigned int n);
int					ft_nbdigitll16(unsigned long long int n);
char				*ft_strrem(char *str, int c);

int					get_next_line(int fd, char **line);
int					mallocage(char **line, char *str);
int					gnl_test(int check, char *str, char **line, int fd);
int					gnl_rec(int check, char *str, char **line, int fd);

unsigned int		ft_atoui(const char *str);
char				*ft_strjoin_c(char const *s1, char const *s2, char c);
size_t				ft_strafter(char **str);

#endif
