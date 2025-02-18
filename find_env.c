#include "minishell.h"
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len);


int ft_is_valid_env_var(const char *str)
{
	 size_t	i;

	if (!str || (!ft_isalpha(str[0]) || str[0] == '_')) 
	{
		return (0); 
	}
	i = 0;
	while (str[i] != '\0' && str[0] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1); // Valid environment variable name
}

//IF env variable is full AI claims it is basically undefined behavior
int find_env(const char *str, t_data *data)
{
	size_t	str_len;
	char	**envp;
	char	*start;
	size_t	i;

	if (!ft_is_valid_env_var(str))
	{
		return (-1);
	}
	str_len = ft_strlen(str);
	envp = data->env;
	i = 0;
	while (i < ENV_SIZE)
	{
		if (envp[i] != NULL)
		{
			start = ft_strnstr(envp[i], str, str_len);
			if (start == envp[i] && envp[i][str_len] == '=')
			{
				return i;
			}
		}
		i++;
	}
	return (-1);
}



