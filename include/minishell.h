/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:39:37 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/26 11:37:44 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# ifndef MAX_VARS
#  define MAX_VARS (100)
# endif
# ifndef MAX_LENGTH
#  define MAX_LENGTH (400)
# endif
# include "../libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ENV_SIZE 4096
# ifndef MAX_SENT_SIZE
#  define MAX_SENT_SIZE (200)
# endif
# ifndef MAX_SENTENCES
#  define MAX_SENTENCES (50)
# endif

# define RED "\x1b[31m"
# define GREEN "\x1b[32m" // Used for variable expansion
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define BRIGHT_BLACK "\x1b[90m"
# define BRIGHT_RED "\x1b[91m"
# define BRIGHT_GREEN "\x1b[92m"
# define BRIGHT_YELLOW "\x1b[93m"
# define BRIGHT_BLUE "\x1b[94m"
# define BRIGHT_MAGENTA "\x1b[95m"
# define BRIGHT_CYAN "\x1b[96m"
# define BRIGHT_WHITE "\x1b[97m"
# define RESET "\x1b[0m"

// ghost variable marks removed quotes that only act as delimiter for $expansion
// DEBUG ILLEGAL SWITCH

const char		*token_to_string(t_token token);

// DEBUG

typedef struct s_sent
{
	char		*array[MAX_SENT_SIZE];
	bool		inpipe;
	bool		outpipe;
	char		*infile; //change to FD
	char		*outfile; //change to FD
	char		*heredocs; //Change to fixed size array
	bool		here_exists; //If we change to fixed size array we cant set it to NULL so we use a flag instead 

}				t_sent;

typedef struct s_data
{
	int			duh;
	char		**history;
	int			his_i;
	char		env[MAX_VARS + 1][MAX_LENGTH + 1];
	int			env_count;
	t_list		tokens;
	t_sent		*page[MAX_SENT_SIZE];
}				t_data;

typedef struct s_point
{
	t_node		*node;
	int			start;
	int			end;
}				t_point;

void			test(t_data data[]);
typedef void	(*node_func)(t_list *list, t_node *node);
void			ft_exit(t_data *data, char *message, int exit_code);
void			*ft_xcalloc(size_t nmemb, size_t size);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
size_t			ft_wrdlen(t_char *str, t_data *data);
const char		*find_env(t_char *source, t_data *data);
void			create_list(t_data *data, t_char *line);
void			iterate_list(t_list *list, node_func func);
t_data			*get_data(void);
void			debug_print(t_char *array, t_data *data);
void			print_node(t_list *list, t_node *node);
size_t			ft_tcharlen(t_char *line);
t_node			*destroy_node(t_list *list, t_node *node);
void	remove_quotes(t_char *dst, char *src);
int	copy_env_to_tchar(t_char *dst, int i, const char *env);
char	*cnvrt_to_char(t_char *line);
int	check_emp_arg(char *src, int i, t_char *dst, int *k, int in_d_quotes, int in_s_quotes);
t_char	*lexify(char *line, t_data *data);
#endif
