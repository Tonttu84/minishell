/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:02:52 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/16 17:57:51 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_delimiter(const char *str)
{
	if (str == NULL)
		printf("DEBUG : find_next_delimiter NULL pointer as input\n");
    int i;
    int in_s_quote;
    int in_d_quote;

    i = 0;
    in_s_quote = 0;
    in_d_quote = 0;
    while (str && str[i])
	{
		if (in_s_quote && str[i] == '\'')
            in_s_quote = 0;
        else if (in_s_quote == 0 && in_d_quote == 0 && str[i] == '\'')
            in_s_quote = 1;
        else if (in_d_quote && str[i] == '\"')
            in_d_quote = 0;
        else if (in_s_quote == 0 && in_d_quote == 0 && str[i] == '\"')
            in_d_quote = 1;
        else if (!in_d_quote && !in_s_quote && str[i] == ' ')
            return (i);
        i++;
    }
	if (in_s_quote || in_d_quote)
		{
			errno = EINVAL;
			perror("Quotes not closed ");
			return (-1);
		}
    return (i);
}

const char *find_next_start(const char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str && *str == ' ')
	{
		str++;
	}
	if (*str == 0)
		return (NULL);
	else 
		return (str);
}
void free_arguments(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
		{
			free(args[i]);
			i++;
		}
	free(args);
}

char **create_args(const char *line, t_data *data)
{
	char **args;
	int i;
	int size;
	const char *start;

	args = ft_calloc(ft_strlen(line) + 1, sizeof (char *), data);
	i = 0;
	start = find_next_start(line);
	while (i < (int)ft_strlen(line))
	{
		start = find_next_start(start);
		if (start == NULL)
			break ;
		size = find_next_delimiter(start);
		if (size < 1)
			{
				free_arguments(args);
				return (NULL);
			}
		args[i] = ft_calloc(size + 1, sizeof(char), data); 
		ft_strlcpy(args[i], start, size +1);
		start = start + size;
		i++;
	}
	return (args);
}

void create_list(char **elements, t_data *data)
{
	int	i;
	t_node	*new;

	
	i = 0;
	while (elements && elements[i])
	{
		new = create_node(elements[i], RAW, data);
		ft_lstadd_back(&data->tokens, new);
		new = create_node(NULL, DELIMIT, data);
		ft_lstadd_back(&data->tokens, new);
		i++;
	}
}

int find_arg_start(char *str)
{
	int	start;
	int in_s_quote;
	int in_d_quote;

	in_d_quote = 0;
	in_s_quote = 0;
	start = 0;
	if (str == NULL)
		return (0);
	while(str[start])
	{
		if (in_s_quote && str[start] == '\'')
			in_s_quote = 0;
		else if (in_s_quote)
			;
		else if (str[start] == '$' && !in_s_quote)
			return (start);
		else if (in_d_quote && str[start] == '\"')
			in_d_quote = 0;
		else if (in_d_quote)
			;
		else if (str[start] == '\'')
			in_s_quote = 1;
		else if (str[start] == '\"')
			in_d_quote = 1;
		start ++;
	}
	return (-1);
}
//while legal character 
int find_arg_end(t_node *cur, int start)
{
    int end;
    int bracketed;

    bracketed = 0;
    end = start + 1;
    if (cur->str[end] == '{')
    {
        bracketed = 1;
        end++;
    }
    else if (!ft_isalpha(cur->str[end]) && cur->str[end] != '_')
    {
        perror("Tried to expand illegal argument or argument type out of scope\n");
        return -1;
    }
    while (ft_isalnum(cur->str[end]) || cur->str[end] == '_')
        end++;
    if (bracketed == 1)
    {
        if (cur->str[end] != '}')
        {
            perror("unexpected end of file\n");
            return -1;
        }
        end++;
    }
    return end;
}

void replace_node(t_stack *stack, t_node *target, t_node *replacement)
{
	if (!stack || !target || !replacement)
	{
		perror("DEBUG, NULL input to replace_node");
		exit (-1);
	}
	replacement -> next = target ->next;
	replacement -> prev = target ->prev;
	target -> prev -> next = replacement;
	target -> next -> prev = replacement;
	if (stack -> first == target)
		stack->first = replacement;
	if (stack -> last == target)
		stack->first = replacement; 
	
}

//Last sould always be a delimiter so it doesnt need to be checked
t_point *find_expansion(t_stack *list)
{
	t_node *cur;
	int start;
	t_point *retval;

	start = 0;
	if (list->first == NULL)
		return (NULL);
	cur = list->first;
	while (cur != list-> last)
	{
		start = find_arg_start(cur->str);
		if (start >= 0)
		{
			retval->end = find_arg_end(cur, start);
			if (retval->end < 0)
			{
				return NULL;
			}
			retval->node = cur;
			retval->start = start; 
			return (retval);
		}
			
		cur = cur -> next;
	}
	return (NULL);
}
//Option to just destroy the token if the argument is zero
void add_env_node(t_node *target, size_t start, size_t end, t_data *data)
{
	char *variable;
	char *env;
	t_node *new;

	variable = ft_strndup(target->str, start, end);
	env = get_own_env(data, variable);
	target->original = variable;
	new = create_node(env, ARGUMENT, data);
	//if (new->str && ft_strlen(new->str > 0))
		add_behind(target, new, data);
	//else
	//	remove_node(new, data);
}

void remove_node(t_node *target, t_data *data)
{
	if (!target || !data)
	{
		perror("DEBUG Invalid input to remove_node");
		return ;
	} 
	if (target->next == target)
	{
		data->tokens.first = NULL;
		data->tokens.last = NULL;
		free(target->str);
		free(target);
		return ;
	}
	if (data->tokens.first == target)
		data->tokens.first = target->next;
	if (data->tokens.last == target)
		data->tokens.last = target->prev;
	target->next->prev = target -> prev;
	target->prev->next = target -> next;
	free(target->str);
	if (target->type == ARGUMENT)
		free(target->original);
	free(target);
	
}

//Just add them after target and finally delete the target
void	expand(t_node *target, int start, int end, t_data *data)
{
	char *str;
	t_node *new;
	t_token type;
	
	type = target->type;
	if (target == NULL)
	{
		perror("DEBUG iffy input to exppand\n");
		return ;
	}
	str = ft_strdup(target->str);
	if (str == NULL)
	{
		perror("Memory allocation failed\n");
		return ;
	}
	if (end != (int)ft_strlen(target->str))
	{
		create_node(ft_strndup(str, end, ft_strlen(str)), type, data);
		add_behind(target, new, data);
	}
	{
		add_env_node(target, (size_t)start, (size_t)end, data);
		
	}
	if (start > 0)
	{
		new = create_node(ft_strndup(str, 0, start), type, data);
		add_behind(target, new, data);
	}
	remove_node(target, data);
	free (str);
}

void expand_arguments(t_data *data)
{
	t_point *target;
	
	target = NULL;
	target = find_expansion(&data->tokens);
	while (target)
	{
		expand(target->node, target->start, target->end, data);
		target = find_expansion(&data->tokens);
	}
}

void join_lists(t_data *data, t_node *target)
{
	char *joined;
	t_node *cur;

	cur = target;
	while(cur != data->tokens.last)
	{
		if (cur && cur->next && cur->next->str && cur -> str)
		{
		joined = ft_strjoin(cur->str, cur->next->str);
		free(cur->str);
		cur->str = NULL;
		cur->str = joined; 
		remove_node(cur->next, data);
		}
		else 
			cur = cur->next;
	}
}
/*
Now the situation is that I can have delimit $invalid delimit

And after expansion delimit "" DELIMIT

bash treats cd $INVALD which expands to ""
different than cd ""			



*/
//Last should always be a delimiter
//Now the problem is that we are clearing quotes from inside quotes 
char    *clean_string(char *str, t_data *data)
{
    char *retstr;
    int i;
    
    // Check for NULL and add a debug print
    if (str == NULL)
    {
        printf("Debug: Input string is NULL\n");
        return NULL;
    }
    
    retstr = ft_calloc(ft_strlen(str) + 2, sizeof(char), data);
    retstr[0] = '\'';
    i = 1;
    while (*str != 0)
    {
        if (*str != '\"' &&  *str != '\'')
        {
                retstr[i] = *str;
            i++;
        }
        str++;
    }
    retstr[i] = '\'';
    retstr[i + 1] = 0;
    //ree(str);
    return (retstr);
}



void remove_quotes(t_node *target, t_data *data)
{
	t_node *cur;
	
	if (!target || !data)
	{
		perror("DEBUG strange input to remove_quotes\n");
		return ;
	}
	cur = target;
	while (cur != data->tokens.last)
	{
		cur->str = clean_string(cur->str, data);
		cur = cur ->next;
	}
}

//valgrind kertoo bash komennon 

/*
int create_tokens(char *line, t_data *data)
{
	char			**result;
	int				i;
	
	i = 0;

	
	result = create_args(line, data);
	if (result == NULL)
		return (-1);c"d
	create_list(result, data);

	join_lists(data, data->tokens.first);

	remove_quotes(data->tokens.first, data);

	return 0;
}

*/

//Create custom struct for chars

int main(int argc, char *argv[])
{
	char			**result;
	static t_data	data[1];
	int				i;
	t_node 			*cur;
	
	i = 0;
	if (argc != 2)
		return (-1);
	//init
	
	result = create_args(argv[1], data);
	if (result == NULL)
		return (-1);
	create_list(result, data);
	cur = data->tokens.first;
	
	while (cur != data->tokens.last)
	{
		printf("%s ", cur->str);
		cur = cur -> next;
		printf("\n");
	}
	join_lists(data, data->tokens.first);
	cur = data->tokens.first;
	
	while (cur != data->tokens.last)
	{
		printf("%s ", cur->str);
		cur = cur -> next;
		printf("\n");
	}
	remove_quotes(data->tokens.first, data);
	
	
	cur = data->tokens.first;
	
	while (cur != data->tokens.last)
	{
		printf("%s ", cur->str);
		cur = cur -> next;
		printf("\n");
	}
	printf("%s ", cur->str);
	return 0;
}

