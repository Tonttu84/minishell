#include "minishell.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>



void add_to_history(char *line, t_data *data)
{
	if (line && *line)
	{
		add_history(line);
	}
}


void init_env(char **env_orig, t_data *data)
{
	char **my_env;
	int i;

	my_env =(char **)ft_calloc(ENV_SIZE + 1, sizeof(char *), data);
	i = 0;
	data->env = my_env;
	while (env_orig[i]!= NULL)
	{
		if (env_orig[i][0] != '_' && env_orig[i][1] != '\0')//or should it be '='
			data->env[i] = ft_strdup(env_orig[i]);
		i++;
	}

}




void print_env(t_data *data)
{
	int	i; 

	i = 0;
	while (i < ENV_SIZE)
	{
		if (data->env[i] != NULL)
			printf("%s\n", data->env[i]);
		i++;
	}


}

//Do we want dynamic or fixed size for readline?

//arg[0] is export and 
//arg[1] is the variable name

int add_variable(t_data *data,const char *env_var, const char *value)
{
	int i;
	char *new;
	char *final;

	i = 0;
	while (i < ENV_SIZE && data->env[i])
	{
		i++;
	}
	if (i == ENV_SIZE)
		ft_exit(data, "Error: Environment variable limit exceeded\n", 1001);
	new = ft_strjoin(env_var, "=");
	//free(env_var);
	final = ft_strjoin(new, value);
	free(new);
	data->env[i] = final;

	return (0);
}
int set_variable(t_data *data, char *env_var, char *value)
{
	int old_i;
	
	old_i = find_env(env_var, data);
	free(data->env[old_i]);
	data->env[old_i] = NULL;
	add_variable(data, env_var, value);
	return (0);
}

void do_error(t_data *data)
{
	ft_exit(data, "Error happened", 22);
}

int errorcheck(char *line)
{
	(void) line;
	return (0);
}
static int is_valid_cd(char *arg)
{
	(void) arg;
	return 0;
}

//handle -1
int cd(t_data *data, char **tokens)
{
	char *cmd;
	char *cur;
	char cwd[PATH_MAX];

	if (tokens[2] != NULL)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	cur = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	if (is_valid_cd(tokens[1]) == 0)
		set_variable(data, "OLDPWD", getcwd(cwd, PATH_MAX));
	
	
	//problem if chdir fails
	if (tokens[1] == NULL || tokens[1] == 0)
		chdir(get_own_env(data, "HOME"));
	else if (ft_strncmp(tokens[1], "-", 2))
		chdir(get_own_env(data, "HOME"));
	else 
		chdir(tokens[1]);
	set_variable(data, "PWD", getcwd(cwd, PATH_MAX));

	//set the real cwd to be the new pwd
	return (0);
}

//bash export without arguments sorts the list alphabetically
void print_export(t_data *data)
{
	int	i; 

	i = 0;
	while (i < ENV_SIZE)
	{
		if (data->env[i] != NULL)
			printf("declare -x %s\n", data->env[i]);
		i++;
	}


}


//fix mallocs // debug
//EXPORT requiers non expanded arguments
int export(t_data *data)
{
	char *target;
	char **env_value_pair;
	int env_location;



	if (data->tokens.first->next->next == NULL) // or it is a pipe < > | << etc)
		return (print_export(data), 0);
	//need to make sure that this program is only receiving the correct tokens
	if (data->tokens.first->next->next->type != ARGUMENT)
		return (1);
	target = tokens[1];
	if (errorcheck(tokens[1]) == 1)
		do_error(data);
	else
	{
		env_value_pair = ft_split(target, '=');
		if (env_value_pair == 0 || env_value_pair[1] == 0)
			perror("Something has gone wrong");
		env_location = find_env(env_value_pair[0], data);
	}
	if (env_location == -1)
		add_variable(data, env_value_pair[0], env_value_pair[1]);
	else 
		set_variable(data, env_value_pair[0], env_value_pair[1]);
	free(env_value_pair);

	return (0);
}

//Bash manages to print pwd even if you unset pwd
int pwd(t_data *data)
{
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("getcwd() error");

	return (0);
	
}


//Can it get a zero sized string?
#include <string.h> // Include this for strcmp



//normaali case expansiossa on etta koska on jo splitattu spacella niin korvaa vaan sen variablen arvolla, tokenien maara pysyy samana.
//Hankalampi case on jos on ${tadaa}blaa
int echo(t_data *data, char **tokens)
{
	if (tokens == NULL || tokens[1] == NULL)
		do_error(data);
//	if (ft_strchr(tokens[1], (int)'$'))
	//	print_expanded(data, tokens);
//	else
	//	print_plain(data, tokens);


	return (0); 
}

//linked list makes adding in the middle easier. 
//step 1, remove quotes, find the first quote, match it continue.




int env(t_data *data)
{
	(void) data;
	print_env(data);
	return (0);
}

// currently env and exit dont accept arguments




int check_inbuilts(t_data *data)
{
    if (ft_strncmp(data->tokens.first, "env", 4) == 0)
        env(data);
    else if (ft_strncmp(data->tokens.first, "exit", 5) == 0)
        exit(0);
    else if (ft_strncmp(data->tokens.first, "export", 7) == 0)
        export(data);
    else if (ft_strncmp(data->tokens.first, "unset", 6) == 0)
        unset(data, tokens);
    else if (ft_strncmp(data->tokens.first, "cd", 3) == 0)
        cd(data, tokens);
    else if (ft_strncmp(data->tokens.first, "echo", 5) == 0)
        echo(data, tokens);
    else if (ft_strncmp(data->tokens.first, "pwd", 4) == 0)
        pwd(data);
	//free_tokens(tokens);
	return (0);
}




//It would be possible to have inbuilts as a first "virtual folder in the pipe, so if the inbuilt is found it doesnt try other folders
void prompt_input(t_data *data)
{
	char *line;
	char **tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break;
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
	//	tokens = tokenize(data, line);
		//check_inbuilts(data);
		
		add_to_history(line, data);
		free(line); // Free the allocated memory
	}
}

void test(t_data *data)
{
	char **split;
	split = ft_split("export tadaa tidii", ' ');
	printf("%s and %s and %s\n", split[0], split[1], split[2]);

}



// in bash _ stores the last argument. If there are multiple arguments it stores the last.
// It is only updated on a succesful command
int main(int ac, char **av, char **env)
{
	static t_data data[1];

	init_env(env, data);
	test(data);

	prompt_input(data);

	rl_clear_history(); // Clear the history when exiting
	

	return 0;
}

