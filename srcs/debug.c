/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:06:42 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/21 19:16:20 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char* token_to_string(t_token token) 
{
    switch(token)
	{
        case DELIMIT: return "";
        case ARG: return "ARG";
        case CMD: return "CMD";
        case OUT_FILE: return "OUT_FILE";
		case IN_FILE: return "IN_FILE";
        case CTRL: return "CTRL";
		case PIPE: return "PIPE";
        default: return "UNKNOWN";
    }
}

const char* token_to_color(t_token token)

{
    switch (token)
	{
		case IN_FILE: return BRIGHT_BLUE;
        case DELIMIT:     return YELLOW;
        case ARG:         return CYAN;
        case CMD:         return MAGENTA;
        case OUT_FILE:  return WHITE;
        case CTRL:        return BLUE;
		case PIPE:			return BRIGHT_YELLOW;			
        default:          return RESET;
    }
}

void print_node(t_list *list, t_node *node)
{
    int i;

    (void) list;

    // Get the color for the node's type
    const char* color = token_to_color(node->type);

    // Print the node's type in its corresponding color
    printf("{%s%s%s", color, token_to_string(node->type), RESET);

    if (node->type != DELIMIT)
        printf(" ");

    i = 0;
    while (node->str && node->str[i].c)
    {
        while (node->str[i].c)
        {
            if (node->str[i].esc && node->str[i].c == ' ')
                printf("%s_%s", RED, RESET);
            else if (node->str[i].esc)
            {
                printf("%s%c%s", RED, node->str[i].c, RESET);
            }
            else if (node->str[i].com)
            {
                printf("%s%c%s", BLUE, node->str[i].c, RESET);
            }
            else if (node->str[i].var)
            {
                printf("%s%c%s", GREEN, node->str[i].c, RESET);
            }
            else
                printf("%c", node->str[i].c);
            i++;
        }
    }
    printf("}");
}
void debug_print(t_char *array, t_data *data) {
    int i = 0;
    while (array[i].c) {
        if (array[i].esc && array[i].c == ' ') {
            printf("%s_%s", RED, RESET);
        } else if (array[i].esc) {
            printf("%s%c%s", RED, array[i].c, RESET);
        } else if (array[i].com) {
            printf("%s%c%s", BLUE, array[i].c, RESET);
        } else if (array[i].c == '$' && array[i].var) {
            printf("%s%s%s", YELLOW, find_env(array + i, data), RESET);
            printf("%s%c%s", GREEN, array[i].c, RESET);
        } else if (array[i].var) {
            printf("%s%c%s", GREEN, array[i].c, RESET);
        } else if (array[i].c == ' ' && array[i].ghost) {
            printf("[G]");
        } else {
            printf("%c", array[i].c);
        }
        i++;
    }
    printf("\n");
}


