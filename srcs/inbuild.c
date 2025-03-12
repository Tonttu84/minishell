/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/12 10:47:49 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int run_builtin(int argc, char *argv[], char *env[])
{
	//Not sure if I can take input like this to function withot counting variables?
	if (argc == 0)
		return (1);
	if (ft_strncmp("cd", argv[0], 3 == 0 ))
			cd(argc, argv, env);
	else if (ft_strncmp("pwd", argv[0], 4 == 0 ))
		pwd(argc, argv, env);
	else if (ft_strncmp("echo", argv[0], 5 == 0 ))
		echo(argc, argv, env);
	else if (ft_strncmp("env", argv[0], 4 == 0 ))
		env(argc, argv, env);
	else if (ft_strncmp("export", argv[0], 7 == 0 ))
		export(argc, argv, env);
	else if (ft_strncmp("unset", argv[0], 6 == 0 ))
		unset(argc, argv, env);
	else if (ft_strncmp("exit", argv[0], 5 == 0 ))
		exit(argc, argv, env);
	else if
		return (0);
	return (1);
		
}




//ignore arguments
int	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
	return (0);
}

//Only takes 1 argument, throws error otherwise
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


//unset can take multiple arguments
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
//can take multiple arguments
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
