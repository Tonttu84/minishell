/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:39:37 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/18 20:35:46 by jrimpila         ###   ########.fr       */
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


//ghost variable marks removed quotes that only act as delimiter for $expansion
typedef struct s_char
{
    char c;        
    bool esc;
	bool com;
	bool var;
	bool blok;
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
	char			*str;
	char			*original;
	t_token			type;
}	t_node;

typedef struct s_stack
{
	t_node	*first;
	t_node	*last;
}	t_stack;

typedef struct s_data
{
	int		duh;
	char	**history;
	int		his_i;
	char	env[MAX_VARS + 1][MAX_LENGHT + 1];
	t_stack tokens;
}	t_data;


typedef struct s_point
{
	t_node	*node; 
	int		start;
	int		end;
}	t_point;

void test(t_data data[]);

void ft_exit(t_data *data, char *message, int exit_code);
void	*ft_xcalloc(size_t nmemb, size_t size, t_data *data);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
int		ft_isalpha(int c);
int	ft_isalnum(int c);

