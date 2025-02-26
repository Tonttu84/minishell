/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:23:16 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/26 12:59:45 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test(t_data data[1])
{
	t_char	*result;
	int		i;

	// Example lines for testing your parsing function
	char *test_lines[] = {
		"cat \"$HOME/i\"\"nput.txt\">>outfile.txt \'\' \'\'\"\" | echo $US\"\"ER \'\'grep $invalid \"search_pattern\" < \"$HOME/input.txt\" > \"$HOME/error.log\" | sort | uniq |   echo > test.txt \"Found line: \"$line\"\" echo \"Current user: $USER\" | echo \"Non-existent variable: $NONEXISTENTVAR\"",
	};
	for (i = 0; (unsigned int)i < sizeof(test_lines)
		/ sizeof(test_lines[0]); i++)
	{
		printf("Test line %d: %s\n", i + 1, test_lines[i]);
		result = lexify(test_lines[i], data);
		printf("\n");
		// create_list(data, result);
		free(result);
		result = NULL;
		create_page(&data->tokens);
	}
	/*
		i = 0;
		while (i < MAX_VARS)
		{
			if (data->env[i][0])
				printf("%s\n", data->env[i]);
			i++;
		}
 */
}