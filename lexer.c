#include "minishell.h"

/*
jrimpila@c3r5p5:~/Git/minishell$ export GHOST=tadaa<<ta
> $GHOST
> 
*/





void remove_quotes(t_char *dst, char *src, t_data *data)
{
    int i;
    int in_s_quotes;
    int in_d_quotes;
	int k;
	int exp;

	(void)(data);
	exp = 0;
    in_s_quotes = 0;
    in_d_quotes = 0;
    i = 0;
	k = 0;
    while (src && src[i] != 0)
    {
        if (in_s_quotes && src[i] == '\'')
            in_s_quotes = 0;
        else if (in_d_quotes && src[i] == '\"')
            {
				in_d_quotes = 0;
				exp = 0;
				dst[k + 1].blok = 1;
			}
        else if (!in_d_quotes && !in_s_quotes && src[i] == '\"')
            in_d_quotes = 1;
        else if (!in_d_quotes && !in_s_quotes && src[i] == '\'')
            {
				in_s_quotes = 1;
				dst[k + 1].blok = 1;
			}
        else if (in_s_quotes)
        {
            dst[k].c = src[i];
            dst[k].esc = 1;
			k++;
        }
		else if (in_d_quotes)
        {
            dst[k].c = src[i];
			if (src[i] == '$')
            	exp = 1;
			else if (exp == 1)
			{
				if (ft_isalnum(src[i]) == 0 && src[i] != '_')
					{
						exp = 0;
						dst[k + 1].blok = 1;
					}
			}
			if (exp == 0)		
				dst[k].esc = 1;
			k++;
        }
        else
        {
			dst[k].c = src[i];
			k++;
		}
        i++;
    }
    dst[i].c = '\0'; 
}

// real << should not have a space on the right side, I will have to check what is the correct behavior
//It seems to require non whitespace character 

//Should get caught if it is surrounded by spaces but give error
void mark_commands(t_char *com_line, t_data *data)
{
    int i;
	
	(void)data;
	i = 0;
    while(com_line[i].c != 0)
    {
        if (i == 0 || com_line[i].esc || com_line[i - 1].esc || com_line[i + 1].c == 0 || com_line[i + 1].esc)
            ;
      //  else if (com_line[i - 1].c == '<' && !com_line[i - 2].esc && com_line[i - 2].c == ' ' && com_line[i].c == '<' && com_line[i + 1].c == ' ')
       //     com_line[i].com = 1;
        else if (com_line[i - 1].c == '>' && !com_line[i - 2].esc && com_line[i - 2].c == ' ' && com_line[i].c == '>' && com_line[i + 1].c == ' ')
            com_line[i].com = 1;
        else if (com_line[i - 1].c == ' ' && com_line[i].c == '>' && com_line[i + 1].c == '>' && !com_line[i + 2].esc && com_line[i + 2].c == ' ')
            com_line[i].com = 1;
   //     else if (com_line[i].c == '<' && com_line[i + 1].c == '<' && com_line[i + 2].c != 0 && (com_line[i + 2].esc == 0 && com_line[i + 2].c != ' '))
      //      com_line[i].com = 1;
        else if (com_line[i - 1].c != ' ' || com_line[i + 1].c != ' ')
            ;
        else if (com_line[i].c == '|' || com_line[i].c == '<' || com_line[i].c == '>')
            com_line[i].com = 1;
        i++;
    }
}

void mark_env_var(t_char *newline, int start, t_data *data)
{
	int end;

	(void)data;
	end = start;
	newline[end].var = 1;
	end++;
	if (newline[end].c == 0 || newline[end].esc ||
	(!ft_isalpha(newline[end].c) && newline[end].c != '_')) 
		return ; 
	else 
	{
		newline[end].var = 1;
		end++;
	}
	while(newline[end].c != 0 && !newline[end].esc && (ft_isalnum(newline[end].c) || newline[end].c == '_' ))
	{
		if (newline[end + 1].blok != 1)
			newline[end].var = 1;
		end++;
	}

}

void	mark_arguments(t_char *newline, t_data *data)
{
	int	i;

	(void)data;
	i = 0;
	while (newline[i].c != 0)
	{
		if (newline[i].esc)
			;
		else if (newline[i].c == '$')
			mark_env_var(newline, i, data);
		i++;
	}
}

int copy_env_to_tchar(t_char *dst, int i, const char *env)
{
	int	env_i;

	if (env == NULL)
		return (i);
	env_i = 0;
	while(env[env_i])
	{
		dst[i].c = env[env_i];
		dst[i].var = 1;
		dst[i].esc = 0;
		dst[i].com = 0;
		i++;
		env_i++;
	}
	return (i);
}

void expand_arguments(t_char *dst, t_char *src, t_data *data)
{
	int di;
	int si;
	const char *temp;

	di = 0;
	si = 0;

	while(src[si].c != 0)
	{
		if (src[si].c == '$' && src[si].esc == 0 && src[si].var)
		{
			temp = find_env(src + si, data);
				di = copy_env_to_tchar(dst, di, temp);
		}
		if (src[si].var == 0)
			{
				dst[di].c = src[si].c;
				dst[di].esc = src[si].esc;
				dst[di].var = src[si].var;
				dst[di].com = src[si].com;
				di++;
			}
		si++;
	}
	dst[di].c = 0;
}


t_char *lexify(char *line, t_data *data)
{
    t_char *newline;
    int i;
	static t_char expanded[1000];
	
	(void) data;
    newline = ft_xcalloc(ft_strlen(line) + 1, sizeof(t_char), data);
    remove_quotes(newline, line, data);
	mark_commands(newline, data);
	mark_arguments(newline, data);
	expand_arguments(expanded, newline, data);
    i = 0;
    while (newline[i].c)
    {
		if (newline[i].esc && newline[i].c == ' ')
			printf("%s_%s", RED, RESET);
        else if (newline[i].esc)
        {
            printf("%s%c%s", RED, newline[i].c, RESET);
        }
		else if (newline[i].com)
		{
            printf("%s%c%s", BLUE, newline[i].c, RESET);
        }
		else if (newline[i].c == '$' && newline[i].var)
			{
				printf("%s%s%s", YELLOW, find_env(newline + i, data), RESET);
				printf("%s%c%s", GREEN, newline[i].c, RESET);
			}
		else if (newline[i].var)
		{
            printf("%s%c%s", GREEN, newline[i].c, RESET);
        }
        else
            printf("%c", newline[i].c);
        i++;
    }
    printf("\n");

	i = 0;
	while (expanded[i].c)
{
    if (expanded[i].esc && expanded[i].c == ' ')
        printf("%s_%s", RED, RESET);
    else if (expanded[i].esc)
    {
        printf("%s%c%s", RED, expanded[i].c, RESET);
    }
    else if (expanded[i].com)
    {
        printf("%s%c%s", BLUE, expanded[i].c, RESET);
    }
    else if (expanded[i].c == '$' && expanded[i].var)
    {
        printf("%s%s%s", YELLOW, find_env(expanded + i, data), RESET);
        printf("%s%c%s", GREEN, expanded[i].c, RESET);
    }
    else if (expanded[i].var)
    {
        printf("%s%c%s", GREEN, expanded[i].c, RESET);
    }
    else
        printf("%c", expanded[i].c);
    i++;
}
	printf("\n");
	create_list(data, expanded);
	iterate_list(&data->tokens , print_node);
	return (newline);
   
}

void test(t_data data[1])
{
	t_char *result;
    // Example lines for testing your parsing function
char *test_lines[] =
{
    "cat \"$HOME/input.txt\" | grep \"search_pattern\" > \"$HOME/output.txt\" > \"$HOME/error.log\" | sort | uniq | while read line; |   echo \"Found line: \\\"$line\\\"\"; done; echo \"Current user: $USER\" | echo \"Non-existent variable: $NONEXISTENTVAR\"",
};

    
    for (unsigned int i = 0; i < sizeof(test_lines) / sizeof(test_lines[0]); i++)
	{
        printf("Test line %d: %s\n", i + 1, test_lines[i]);
        result = lexify(test_lines[i], data);
        printf("\n");
		//create_list(data, result);
		free(result);
		result = NULL;
		//printf("Printing nodes:  ");
		//iterate_list(&data->tokens, print_node);
		//printf("Stopped printing nodes\n");
    }
   /*
	int i = 0;
	while (i < MAX_VARS)
	{
		if (data->env[i][0])
			printf("%s\n", data->env[i]);
		i++;
	}
*/

}
