#include "minishell.h"

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"



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
        else if (com_line[i - 1].c == '<' && !com_line[i - 2].esc && com_line[i - 2].c == ' ' && com_line[i].c == '<' && com_line[i + 1].c == ' ')
            com_line[i].com = 1;
        else if (com_line[i - 1].c == '>' && !com_line[i - 2].esc && com_line[i - 2].c == ' ' && com_line[i].c == '>' && com_line[i + 1].c == ' ')
            com_line[i].com = 1;
        else if (com_line[i - 1].c == ' ' && com_line[i].c == '>' && com_line[i + 1].c == '>' && !com_line[i + 2].esc && com_line[i + 2].c == ' ')
            com_line[i].com = 1;
        else if (com_line[i].c == '<' && com_line[i + 1].c == '<' && com_line[i + 2].c != 0 && (com_line[i + 2].esc == 0 && com_line[i + 2].c != ' '))
            com_line[i].com = 1;
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


void lexify(char *line, t_data *data)
{
    t_char *newline;
    int i;
	
	(void) data;
    newline = ft_xcalloc(ft_strlen(line) + 1, sizeof(t_char), data);
    remove_quotes(newline, line, data);
	mark_commands(newline, data);
	mark_arguments(newline, data);
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
		else if (newline[i].var)
		{
            printf("%s%c%s", GREEN, newline[i].c, RESET);
        }
        else
            printf("%c", newline[i].c);
        i++;
    }
    printf("\n");
   
}

void test(t_data data[1])
{
    // Example lines for testing your parsing function
char *test_lines[] =
{
    "echo $HOME > home_dir.txt",
    "cp $PATH/path/to/file $HOME/backup/",
    "ls -la $USER > user_list.txt",
    "find $HOME -type f -name '*.log' | xargs grep 'er\"r\"$or' > error_logs.txt",
    "ps -ef | grep $SHELL > shell_processes.txt",
    "cd $TEMP && ls -l > temp_dir_list.txt",
    "tar -czvf $BACKUP/archive.tar.gz $HOME/documents",
    "echo tadaa \"$HOSTNAM'E'\" << hostname.txt",
    "awk '{print $2}' $DATA_FILE > second_column.txt",
    "df -h $HOME > disk_usage_home.txt",
	"echo '$HOME'",
	"./pipex infile \"ls -a\" \"cat -e\" outfile | \"cat -e\" outfile"
};

    
    for (unsigned int i = 0; i < sizeof(test_lines) / sizeof(test_lines[0]); i++)
	{
        printf("Test line %d: %s\n", i + 1, test_lines[i]);
        lexify(test_lines[i], data);
        printf("\n");
    }
   
	int i = 0;
	while (i < MAX_VARS)
	{
		printf("%s\n", data->env[i]);
		i++;

	}

}
