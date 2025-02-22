/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:33:26 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/21 19:26:52 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BASE32 "0123456789abcdefghijklmnopqrstuxz"
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h> 

typedef struct s_char
{
    char c;        
    bool esc;
	bool com;
	bool var;
	bool blok;
	bool ghost;
	bool added;
} t_char;


typedef enum e_token
{
	DELIMIT,		
	ARG,
	CMD,
	OUT_FILE,
	IN_FILE,
	CTRL,
	PIPE
	
}   t_token;

typedef struct s_ldiv
{
	long int		quot;
	long int		rem;
}					t_ldiv;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	t_char			*str;
	t_token			type;
}	t_node;

typedef struct s_list
{
	t_node	*first;
	t_node	*last;
}	t_list;

char				*ft_ltostr(long val, unsigned int base);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnstr(char *str, char *sub, size_t len);
char				**ft_split(char const *s, char c);

double				ft_atof(const char *s);

int					ft_atoi(const char *nptr);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);

long				ft_abs(long nbr);

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);

void				ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list *stack, t_node *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_ldiv				ft_ldiv(long nbr, unsigned int base);

int					ft_printf(const char *fmt, ...);
int					writer(char *str, int len, int written);
int					handle_specifier(va_list ap, const char fmt);
int					handle_s(va_list ap);
int					handle_ptr(va_list ap);
int					handle_dec(va_list ap);
int					handle_udec(va_list ap);
int					handle_hex_lf(va_list ap);
int					handle_hex_uf(va_list ap);

#endif
