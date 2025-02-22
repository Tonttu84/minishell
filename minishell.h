/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:39:37 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/21 19:15:16 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
#ifndef MAX_VARS
#define MAX_VARS (100)
#endif
#ifndef MAX_LENGTH
#define MAX_LENGTH (400)
#endif
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h> 
# include "libft/libft.h"

#define ENV_SIZE 4096

#define RED             "\x1b[31m"
#define GREEN           "\x1b[32m"  // Used for variable expansion
#define YELLOW          "\x1b[33m"
#define BLUE            "\x1b[34m"
#define MAGENTA         "\x1b[35m"
#define CYAN            "\x1b[36m"
#define WHITE           "\x1b[37m"
#define BRIGHT_BLACK    "\x1b[90m"
#define BRIGHT_RED      "\x1b[91m"
#define BRIGHT_GREEN    "\x1b[92m"
#define BRIGHT_YELLOW   "\x1b[93m"
#define BRIGHT_BLUE     "\x1b[94m"
#define BRIGHT_MAGENTA  "\x1b[95m"
#define BRIGHT_CYAN     "\x1b[96m"
#define BRIGHT_WHITE    "\x1b[97m"
#define RESET           "\x1b[0m"

//ghost variable marks removed quotes that only act as delimiter for $expansion
//DEBUG ILLEGAL SWITCH

const char* token_to_string(t_token token);

//DEBUG

typedef struct s_data
{
    int     duh;
    char    **history;
    int     his_i;
    char    env[MAX_VARS + 1][MAX_LENGTH + 1];
    int     env_count;   
    t_list  tokens;
}   t_data;



typedef struct s_point
{
	t_node	*node; 
	int		start;
	int		end;
}	t_point;

void test(t_data data[]);
typedef void (*node_func)(t_list *list, t_node *node);
void		ft_exit(t_data *data, char *message, int exit_code);
void		*ft_xcalloc(size_t nmemb, size_t size, t_data *data);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
size_t		ft_wrdlen(t_char *str, t_data *data);
const char	*find_env(t_char *source, t_data *data);
void		create_list(t_data *data, t_char *line);
void 		iterate_list(t_list *list, node_func func);

void debug_print(t_char *array, t_data *data);
void print_node(t_list *list, t_node *node);


