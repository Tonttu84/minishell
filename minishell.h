/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:50:22 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/16 18:31:37 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
# include <limits.h>
# include <unistd.h>
#include <errno.h>
#include <stdbool.h> 

#define ENV_SIZE 4096



typedef struct s_char
{
    char c;        
    bool escaped;  
} t_char;


typedef enum e_token
{
	
    SINGLE_QUOTE, // 0
    DOUBLE_QUOTE, // 1
    NORMAL,			//2
	RAW,			//3
	DELIMIT,		//4
	ARGUMENT
}   t_token;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	char *str;
	char *original;
	t_token type;
}	t_node;

typedef struct s_stack
{
	t_node	*first;
	t_node	*last;
}	t_stack;

typedef struct s_data
{
	int duh;
	char **history;
	int his_i;
	char **env;
	t_stack tokens;
} t_data;


typedef struct s_point
{
	t_node	*node; 
	int		start;
	int		end;
}	t_point;


char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size, t_data *data);
void	ft_exit(t_data *data, char *errormessage, int exit_code);
void	*ft_calloc(size_t nmemb, size_t size, t_data *data);
void	*ft_memset(void *s, int c, size_t n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlen(const char *s);
int find_env(const char *str, t_data *data);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int export(t_data *data, char **tokens);
char	*ft_strchr(const char *s, int c);
void	ft_lstadd_back(t_stack *stack, t_node *new);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
t_node *create_node(char *setstr, t_token set_type, t_data *data);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char *ft_strndup(const char *s, size_t start, size_t end);
void add_behind(t_node *target, t_node *new, t_data *data);
char *get_own_env(t_data *data, char *str);
int	tokenize(t_data *data, const char *startp, int length, t_token t_type);
