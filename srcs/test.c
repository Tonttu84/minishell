/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:23:16 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/03 15:15:52 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test(void)
{
	t_char *result;
	int i;
	t_data *data;

	data = get_data();
	// Example lines for testing your parsing function
	char *test_lines[] =
	{
		
		//"ls -la | cat > out.txt <test.c | echo $blaa?"
		"cat ",
		"/usr/bin/cat ",
		"which cat ",
		"/usr/bin/which cat ",
		"cat \"$HOME/i\"\"nput.txt\">>outfile.txt \'\' \'\'\"\" | echo $US\"\"ER \'\'grep $invalid \"search_pattern\" < \"$HOME/input.txt\" <<EOF > \"$HOME/error.log\" | sort | uniq |   echo > test.txt \"Found line: \"$line\"\" | echo \"Current user: $USER\" | echo \"Non-existent variable: $NONEXISTENTVAR\" ",
	};
	for (i = 0; (unsigned int)i < sizeof(test_lines)
		/ sizeof(test_lines[0]); i++)
	{
		printf("Test line %d: %s\n", i + 1, test_lines[i]);
		result = lexify(test_lines[i], data);
		printf("\n");
		free(result);
		result = NULL;
		iterate_list(&data->tokens, print_node);
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
