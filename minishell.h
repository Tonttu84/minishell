/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:39:37 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/19 19:36:08 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
#ifndef MAX_VARS
#define MAX_VARS (100)
#endif
#ifndef MAX_LENGHT
#define MAX_LENGHT (200)
#endif
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h> 
# include "libft/libft.h"

#define ENV_SIZE 4096

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"

//ghost variable marks removed quotes that only act as delimiter for $expansion


typedef struct s_data
{
	int		duh;
	char	**history;
	int		his_i;
	char	env[MAX_VARS + 1][MAX_LENGHT + 1];
	t_list tokens;
}	t_data;


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


void print_node(t_list *list, t_node *node);


