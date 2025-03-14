/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/14 10:14:24 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	bi_exit(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	return (0);
}

int run_builtin(int argc, char *argv[])
{

	//Not sure if I can take input like this to function withot counting variables?
	if (argc == 0)
		return (1);
	if (ft_strncmp("cd", argv[0], 3) == 0 )
		{
			bi_cd(argc, argv);
		}
	else if (ft_strncmp("pwd", argv[0], 4) == 0)
		bi_pwd();
	else if (ft_strncmp("echo", argv[0], 5) == 0 )
		bi_echo(argc, argv);
	else if (ft_strncmp("env", argv[0], 4) == 0 )
		bi_env(get_data());
	else if (ft_strncmp("export", argv[0], 7) == 0 )
		bi_export(argc, argv);
	else if (ft_strncmp("unset", argv[0], 6) == 0 )
		bi_unset(argc, argv);
	else if (ft_strncmp("exit", argv[0], 5) == 0 )
		bi_exit(argc, argv);
	else if (1)
		return (0);
	return (1);
		
}


int is_builtin(char *cmd)
{
    if (cmd == NULL)
        return 0;
    if (ft_strncmp("cd", cmd, 3) == 0)
        return (1);
    else if (ft_strncmp("pwd", cmd, 4) == 0)
        return (2);
    else if (ft_strncmp("echo", cmd, 5) == 0)
        return (3);
    else if (ft_strncmp("env", cmd, 4) == 0)
        return (4);
    else if (ft_strncmp("export", cmd, 7) == 0)
        return (5);
    else if (ft_strncmp("unset", cmd, 6) == 0)
        return (6); 
    else if (ft_strncmp("exit", cmd, 5) == 0)
        return (7); 
	
    return (0); 
}





//ignore arguments
int	bi_pwd(void)
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

int is_valid_cd(char *dir)
{
	(void) dir;
	return (0);
}

int	bi_cd(int argc, char *argv[])
{
	char	*cur;
	char	cwd[PATH_MAX];
	
	if (argc > 2)
	{
		(void) argv;
		printf("cd: too many arguments\n");
		return (1);
	}
	cur = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	if (is_valid_cd(argv[1]) == 0)
		add_envvar(get_data()->env, "OLDPWD", getcwd(cwd, PATH_MAX));
	if (argv[1] == NULL || argv[1] == 0)
		{
			
			chdir(find_env_value("$HOME", get_data()));
		}
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		chdir(find_env_value("$OLDPWD", get_data()));
	else
		chdir(argv[1]);
	add_envvar(get_data()->env, "PWD", getcwd(cwd, PATH_MAX));
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
int	bi_echo(int argc, char *argv[])
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
	return (0);
}
