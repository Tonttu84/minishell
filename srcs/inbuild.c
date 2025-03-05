/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/05 12:32:10 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	test_inbuilds(t_node *cmd)
{
	if (cmd->str[0].c == 'c' && cmd->str[1].c == 'd' && cmd->str[2].c == 0
		&& cmd->str[2].esc == 0)
		return (1);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'c'
		&& cmd->str[2].c == 'h' && cmd->str[1].c == 'o' && cmd->str[2].c == 0
		&& cmd->str[2].esc == 0)
		return (2);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'n'
		&& cmd->str[2].c == 'v' && cmd->str[3].c == 0 && cmd->str[3].esc == 0)
		return (3);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'x'
		&& cmd->str[2].c == 'o' && cmd->str[3].c == 'r' && cmd->str[5].c == 't'
		&& cmd->str[6].c == 0 && cmd->str[6].esc == 0)
		return (4);
	else if (cmd->str[0].c == 'p' && cmd->str[1].c == 'w'
		&& cmd->str[2].c == 'd' && cmd->str[3].c == 0 && cmd->str[3].esc == 0)
		return (5);
	else if (cmd->str[0].c == 'u' && cmd->str[1].c == 'n'
		&& cmd->str[2].c == 's' && cmd->str[3].c == 'e' && cmd->str[4].c == 't'
		&& cmd->str[5].c == 0 && cmd->str[5].esc == 0)
		return (6);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'x'
		&& cmd->str[2].c == 'i' && cmd->str[3].c == 't' && cmd->str[4].c == 0
		&& cmd->str[4].esc == 0)
		return (7);
	else
		return (0);
}

int	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
	return (0);
}

// TODO handle -1 Has some issues, needs debugging
int	cd(int argc, char *argv[])
{
	char	*cur;
	char	cwd[PATH_MAX];

	if (argv[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	cur = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	if (is_valid_cd(argv[1]) == 0)
		set_variable(get_data(), "OLDPWD", getcwd(cwd, PATH_MAX));
	if (argv[1] == NULL || argv[1] == 0)
		chdir(get_own_env(get_data(), "HOME"));
	else if (ft_strncmp(argv[1], "-", 2))
		chdir(get_own_env(get_data(), "HOME"));
	else
		chdir(argv[1]);
	set_variable(get_data(), "PWD", getcwd(cwd, PATH_MAX));
	return (0);
}

int	unset_env(const char *var, t_data *data)
{
	int	tar_i;
	int	i;

	i = 0;
	tar_i = find_env(var, data);
	if (tar_i == -1)
		return (-1);
	else
	{
		while (i < MAX_LENGTH)
		{
			data->env[tar_i][i] = 0;
			i++;
		}
	}
	return (0);
}

int	echo_check_opt(char *str)
{
	int	i;
	int	isvalid;

	i = 0;
	isvalid = 0;
	if (str[i] != '-')
		return (isvalid);
	i++;
	while (str[i])
	{
		if (str[i] == 'n')
		{
			isvalid = 1;
			i++;
		}
		else
		{
			isvalid = 0;
			return (isvalid);
		}
	}
	return (isvalid);
}

// Argument expansion should already be done here so we can print everything as it is?
int	echo(int argc, char *argv[])
{
	int	i;
	int	opt;

	opt = 0;
	if (argc > 1)
		opt = echo_check_opt(argv[1]);
	i = 2;
	while (opt && echo_check_opt(argv[i]) && i < argc)
		i++;
	while (i < argc)
	{
		printf("%s", argv[i]);
		i++;
	}
	if (opt)
		printf("\n");
}
