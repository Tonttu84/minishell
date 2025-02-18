/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:45:33 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/15 16:21:06 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	tokenize(t_data *data, const char *startp, int length, t_token t_type)
{
	char *newstr;
	
	if (!data || !startp || length <= 0 || t_type > 2 || t_type < 0)
    {
        perror("DEBUG: Iffy input on tokenize\n");
        return -1; 
    }
	newstr = ft_calloc(length + 1, sizeof(char), data);
	ft_strlcpy(newstr, startp, (size_t)length + 1);
	//if (create_node(newstr, t_type) != NULL)
//		ft_lstadd_back(&data->tokens, newstr);
	
	return (length);
}

int grab_dou_quote(t_data *data, const char* line, int start, int escape)
{
	int end;

	if (!data | !line | start < 0 | line[start] != '\"')
	{
        perror("DEBUG: Iffy input on grab_duo_quote\n");
        return -1; 
    }
	end = start + 1;
	while (1)
	{
		//need to track if escape is active or not
		if (line[end] == '\"' && line[end - 1] != '\\')
			return (tokenize(data, line + start, end-start, DOUBLE_QUOTE));
		if (line[end] == '\0')
			{
				perror("DEBUG: Single quote does not match");
				//throw_err(data);
			}
		end++;
	}
	return (0);
}


int grab_sin_quote(t_data *data, const char* line, int start)
{
	int end;

	if (!data | !line | start < 0 | line[start] != '\'')
	{
        perror("DEBUG: Iffy input on grab_sin_quote\n");
        return -1; 
    }
	end = start + 1;
	while (1)
	{
		if (line[end] == '\'' && line[end - 1] != '\\')
			return (tokenize(data, line + start, end-start, SINGLE_QUOTE));
		if (line[end] == '\0')
			{
				perror("DEBUG: Single quote does not match");
			//	throw_err(data);
			}
		end++;
	}
	return (0);
}

//How do I treat special characters???
//OMG c"d" is proper syntax
int grab_normal(t_data *data, const char* line, int start)
{
	int end;

	if (!data | !line | start < 0)
	{
        perror("DEBUG: Iffy input on grab_nor\n");
        return -1; 
    }
	end = start + 1;
	while (1)
	{
		if (line[end] == '\0')
			return (tokenize(data, line + start, end-start, NORMAL ));
		//This might need to be checked with recursion due to the previous being cancellable too
		else if (line[end - 1] == '\\' && end - 2 >= 0 && line [end -2] != '\\')
			 continue;
		else if (line[end] == (' '))
			return (tokenize(data, line + start, end-start, NORMAL ));
	}
	return (0);
}

//line should never be empty because of previous errorchecking in readline
//first \ gets ignore  a following doesnt space seems to get ignored. tab cant be entered
/*void remove_quotes(t_data *data, const char *line)
{
	static int i;
	int start;
	char target;

	if (line == NULL)
		;//exit or error or just return?
	i = 0;
	//first space or \ gets alwaus ignored. Then I dont have to worry about peeking outside of the array. 

	if (line[i] == ' ')
		i++;
	else
	{
		if (line[i] == '\'')
			i = i + grab_sin_quote(data, line, i);
		else if (line[i] == '\"')
			i = i + grab_dou_quote(data, line, i);
		else 
			i = i + grab_normal(data, line, i);
			
	}
	//Ive hanled the first character as a specil case so I always know that anything in the while loop doesnt have to worry about - 1 being outside of the loop
	while (start < 0 && line[i - 1] != '\\' && (line[i] == ' ' || line [i] == '\\'))
		i++;
	start = i;
	if (line[i] == '\'')
			target = '\'';
	else if (line[i] == '\"')
			target = '\"';
	else 
			target = '\0';
}
*/
