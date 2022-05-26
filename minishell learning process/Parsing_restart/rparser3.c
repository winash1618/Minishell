#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termcap.h> 
#include <readline/readline.h>
#include <string.h>
#include <readline/history.h>


size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
	{
		count++;
	}
	s = s - count;
	return (count);
}

char *ft_readline(void)
{
	char *line= readline(">Enter a string: ");
	return (line);
}

void ft_clearscreen(void)
{
	char buf[1024];
	char *str;

	tgetent(buf, getenv("TERM"));
	str = tgetstr("cl", NULL);
	printf("%s", str);
	printf("");
}

// for saving local variable
typedef struct var 
{
	char *key;
	char *value;
	struct var *next;
	struct var *prev;
}	t_var;

// for saving commands
typedef struct list
{
	char	*token;
	int	flag;
	char *es; // expanded string.
	int d_flag; // indicate presence of dollar sign in the string.
	struct list	*next;
	struct list	*prev;
}	t_new;

// for saving required information
typedef struct info
{
	int flag;
	int w_flag; // if the string is double quoted then this flag exist.
	int e_flag; // if the string starts with an equal sign it's an error;
	int q_flag; // exist when count either of the quotes is odd
} t_info;

// to check for spaces
int ft_isspace(char c)
{
	if (c == '\n' || c == ' ' || c == '	')
		return (1);
	return (0);
}

// to check for quotes
int is_quote(char c)
{
	if (c == '"' || c == 39)
		return (0);
	return (1);
} 

void quote_counter(char *line, t_info *info)
{
	int c;

	c = 0;
	char *temp; 
	temp = line;
	while (*line)
	{
		if (*line == '"')
			c++;
		line++;
	}
	if (c % 2)
		info->q_flag = 1;
	c = 0;
	while (*temp)
	{
		if (*temp == '"')
			c++;
		temp++;
	}
	if (c % 2)
		info->q_flag = 1;
}

// find the word length.
int get_word_len(char *line)
{
	int len;

	len = 0;
	while (ft_isspace(*line) && *line)
		line++;
	if (!*line)
		return (-1);
	while (!ft_isspace(*line) && *line && is_quote(*line))
	{
		line++;
		len++;
	}
	return (len);
}

int ft_strlen_ch(char *line, char c)
{
	int len = 0;
	while(*line != c && *line)
	{
		len++;
		line++;
	}
	return (len);
}

// get the quoted word
char *quoted_word(char *line, char ch)
{
	int i;

	i = 0;
	int len = ft_strlen_ch(line, ch);
	if (len > 0)
	{
		char *s = malloc(sizeof(char) * (len + 1));
		while(line[i] && line[i]!=ch)
		{
			s[i] = line[i];
			i++;
		}
		s[i] = '\0';
		return (s);
	}
	return (NULL);
}

// move the pointer after the quote
char *go_past_quotes(char *s, char ch)
{
	// printf("%s \n", s);
	while (*s != ch && *s)
		s++;
	if(*s == ch)
		s++;
	return (s);
}

int check_word_for_parsing(char *line)
{
	if (*(line) == '"')
		return (1);
	else if (*(line) == 39)
		return (2);
	else
		return (3);
}

// get normal word
char *normal_word(char *line)
{
	char *word;
	int len = get_word_len(line);
	word = malloc(sizeof(char) * (len + 1));
	int i = 0;
	while (line[i] && is_quote(line[i]))
	{
		if (ft_isspace(line[i]))
			break;
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

// getting a word either quoted or normal
char *get_word(t_info *info, char *line)
{
	char *word;
	info->flag = 1;

	if (info->e_flag)
		return (NULL);
	while (ft_isspace(*line) && *line)
		line++;
	info->w_flag = check_word_for_parsing(line);
	if (info->w_flag == 3)
		word = normal_word(line);
	else if (info->w_flag == 1)
		word = quoted_word(++line, '"');
	else if (info->w_flag == 2)
		word = quoted_word(++line, 39);
	return (word);
}

// this is for getting words
void lst_add_new(t_new **pars, char *str, t_info *info)
{
	(*pars)->token = str;
	(*pars)->next = NULL;
	(*pars)->prev = NULL;
	if (info->w_flag == 1)
		(*pars)->flag = 1;
	else if (info->w_flag == 3)
		(*pars)->flag = 3;
}
void lst_add_back(t_new **pars, char *str, t_info *info)
{
	t_new *par;
	par = *pars;
	t_new *temp;
	while ((*pars)->next)
	{
		(*pars) = (*pars)->next;
	}
	temp = malloc(sizeof(t_new));
	temp->token = str;
	if (info->w_flag == 1)
		temp->flag = 1;
	else if (info->w_flag == 3)
		(temp)->flag = 3;
	(*pars)->next = temp;
	temp->next = NULL;
	temp->prev = (*pars);
	(*pars) = par;
}

// for printing purposes
void lst_print_vars(t_var *vars)
{
	while(vars != NULL)
	{
		printf("<key: %s> <value: %s> \n", vars->key, vars->value);
		vars= vars->next;
	}
}
void lst_print(t_new *pars)
{
	while(pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d", pars->token, pars->flag, pars->d_flag);
		pars= pars->next;
	}
}

// for normal word getter
void normal_lexer (t_new **pars, t_info *info, char *str)
{
	int wc;
	wc = 0;
	char *temp;
	char *temp1;
	temp = NULL;
	int flag;
	flag = 1;
	while(*str)
	{
		info->w_flag = 0;
		while(*str && ft_isspace(*str))
			str++;
		temp1 = get_word(info, str);
		if (!wc && *str && temp1)
		{
			(*pars) = malloc(sizeof(t_new));
			lst_add_new(pars, temp1, info);
			wc++;
		}
		else if (*str && temp1)
		{
			lst_add_back(pars, temp1, info);
			wc++;
		}
		if (*str == '"')
		{
			temp = go_past_quotes(++str, '"');
			flag = 0;
		}
		else if (*str == 39)
		{
			flag = 0;
			temp = go_past_quotes(++str, 39);
		}
		while(*str && !ft_isspace(*str) && flag && is_quote(*str))
			str++;
		if (!flag)
		{
			str = temp;
			flag = 1;
		}
	}
	// free(*pars);
	
}

// Functions below is used for variable assignment.
int check_var(char *line, t_info *info)
{
	int c = 0;
	while(*line && ft_isspace(*line))
		line++;
	if (*line == '=')
	{
		info->e_flag = 1;
		return (0);
	}
	else
	{
		if (!is_quote(*line))
			return (0);
		while (*line)
		{
			if (*line == '=')
				c++;
			line++;
		}
		if (c)
			return (1);
	}
	return (0);
}

int get_vars(char *line)
{
	int len = 0;
	while (*line != '=')
	{
		len++;
		line++;
	}
	return (len);
}

int get_len(char *line)
{
	int len = 0;
	while (*line)
	{
		len++;
		line++;
	}
	return (len);
}
char *get_key(char *line)
{
	int len;

	char *temp;
	len = 0;
	
	len = get_vars(line);
	if(len)
		temp = malloc(sizeof(char) * (len + 1));
	int i = 0;
	while (line[i] != '=' && line[i])
	{
		temp[i] = line[i];
		i++;
	}
	temp[i]='\0';
	return (temp);
}

char *get_value(char *line)
{
	int len;
	
	char *temp;
	len = 0;
	len = get_len(line);
	if(len)
		temp = malloc(sizeof(char) * (len + 1));
	int i = 0;
	while (line[i])
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void lst_add_newvar(t_var **var, char *line)
{
	(*var) = malloc(sizeof(t_var));
		(*var)->key = get_key(line);
		while (*line != '=' && *line)
			line++;
		line++;
		(*var)->value = get_value(line);
		(*var)->prev = NULL;
		(*var)->next = NULL;

}

void lst_add_backvar(t_var **var, char *line)
{
		t_var *tem;
		t_var *t;
		tem = *var;
		t = malloc(sizeof(t_var));
		while ((*var)->next)
			*var = (*var)->next;
		t->key = get_key(line);
		printf("%s\n", t->key);
		while (*line != '=' && *line)
			line++;
		line++;
		t->value = get_value(line);
		(*var)->next = t;
		t->prev = *var;
		*var = tem;
}

void var_lexer (t_var **var, char *line)
{
	
	static int wc;

	while (*line && ft_isspace(*line))
		line++;
	if (!wc)
	{
		lst_add_newvar(var, line);
		wc++;
	}
	else
	{
		lst_add_backvar(var, line);
		wc++;
	}
}

void find_dollar_presence(t_new *cmd)
{
	while(cmd != NULL)
	{
		cmd->d_flag = 0;
		int i = 0;
		while(cmd->token[i])
		{
			if (cmd->token[i] == '$')
				cmd->d_flag = 1;
			i++;
		}
		cmd = cmd->next;
	}
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
		{
			return ((char *) s);
		}
		s++;
	}
	if (!c)
	{
		return ((char *) s);
	}
	return (NULL);
}

int is_meta(char c)
{
	if (ft_strchr("	 \n|&;()<>$", c))
	{
		return (1);
	}
	return (0);
}
char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *str;
	int i;

	i = 0;
	str = (char *) ft_calloc((len + 1), sizeof(char));
	if (!str || !s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (str);
	while (s[start] && len)
	{
		str[i++] = s[start];
		start++;
		len--;
	}
	return (str);
}


void dollar_expansion(t_new *cmd, char **env)
{
	int i = 0;
	int c = 0;

	while (env[i])
	{
		if ()
		ft_strlen(ft_substr(env[i], 0, ft_strlen_sub(env[i])))
	}
}

int main(int ac, char **av, char **env)
{
	char *buf = (char *)malloc(sizeof(char) * (ft_strlen(getenv("TERM")) + 1));
	t_info *info;
	info = malloc(sizeof(t_info));
	t_new *cmd;
	info->flag = 1;
	info->e_flag = 0;
	t_var *var;
	char *str;
	tgetent(buf, getenv("TERM"));
	str = tgetstr("cl", NULL);
	free(buf);
	// printf("%s", str);
	// printf("");
	char *line;
	while (1)
	{
		info->e_flag = 0;
		info->q_flag = 0;

		line = ft_readline();
		quote_counter(line, info);
		if (!line || !strcmp(line, "exit"))
			return (0);
		else if (!(strcmp(line, "")))
			;
		else if (!strcmp(line, "clear"))
			ft_clearscreen();
		else if (!info->q_flag)
		{
			if(*line && check_var(line, info))
			{
				var_lexer(&var, line);
				lst_print_vars(var);
			}
			else
			{
				normal_lexer(&cmd, info, line);
				find_dollar_presence(cmd);
				dollar_expansion(cmd, env);
				lst_print(cmd);
			}
		}
		free (line);
	}
	return(0);
}
