#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termcap.h> 
#include <readline/readline.h>
#include <string.h>
#include <readline/history.h>

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

// for saving environmet variable list
typedef struct env
{
	char *key;
	char *value;
	struct env *next;
	struct env *prev;
}	t_env;

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
	struct list	*next;
	struct list	*prev;
}	t_new;

typedef struct parse
{
	t_new *cmd_lst;
	t_var *var_lst;
}	t_parse;

int ft_isspace(char c)
{
	if (c == '\n' || c == ' ' || c == '	')
		return (1);
	return (0);
}

int get_word_len(char *line)
{
	int len;

	len = 0;
	while (ft_isspace(*line) && *line)
		line++;
	if (!*line)
		return (-1);
	while (!ft_isspace(*line) && *line)
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

char *quoted_word(char *line, char ch)
{
	
	int len = ft_strlen_ch(line, ch);
	char *s = malloc(sizeof(char) * (len + 1));
	int i = 0;
	while(line[i] && line[i]!=ch)
	{
		s[i] = line[i];
		i++;
	}
	s[i] = '\0';
	if (!line[i])
		return (NULL);
	printf("%s \n", s);
	return (s);
}
char *go_past_quotes(char *s, char ch)
{
	// printf("%s \n", s);
	while (*s != ch && *s)
		s++;
	if(*s == ch)
		s++;
	return (s);
}

char *get_word(char *line)
{
	char *word;

	int len = get_word_len(line);
	if (len <= 0)
		return (NULL);
	
	while (ft_isspace(*line) && *line)
		line++;
	int i = 0;
	if(*line == '"')
		return(quoted_word(++line, '"'));
	if(*line == 39)
		return(quoted_word(++line, 39));
	word = malloc(sizeof(char) * (len + 1));
	while (line[i])
	{
		if (ft_isspace(line[i]))
			break;
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';

	return (word);
}

void lst_add_new(t_new **pars, char *str)
{
	(*pars)->token = str;
	(*pars)->next = NULL;
	(*pars)->prev = NULL;
}
void lst_add_back(t_new **pars, char *str)
{
	t_new *par;
	par = *pars;
	t_new *temp;
	// printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
	while ((*pars)->next)
	{
		// printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
		(*pars) = (*pars)->next;
	}
	// printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
	temp = malloc(sizeof(t_new));
	temp->token = str;
	(*pars)->next = temp;
	temp->next = NULL;
	temp->prev = (*pars);
	(*pars) = par;
	// printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
	// while ((*pars)->next)
	// {
	// 	printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
	// 	(*pars) = (*pars)->next;
	// }
	// printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
	// (*pars) = par;

}

void lst_print_vars(t_var *vars)
{
	while(vars != NULL)
	{
		printf("<key: %s> <value: %s>", vars->key, vars->value);
		vars= vars->next;
	}
}
void lst_print(t_new *pars)
{
	while(pars != NULL)
	{
		printf("<token: %s> ", pars->token);
		pars= pars->next;
	}
}

void norm_parser (t_new **pars, char *str)
{
	int wc;
	wc = 0;
	char *temp;
	temp = NULL;
	int flag;
	flag = 1;
	while(*str)
	{
		while(*str && ft_isspace(*str))
			str++;
		if (!wc && *str)
		{
			(*pars) = malloc(sizeof(t_new));
			lst_add_new(pars, get_word(str));
			wc++;
		}
		else if (*str)
		{
			lst_add_back(pars, get_word(str));
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
		while(*str && !ft_isspace(*str) && flag)
			str++;
		if (!flag)
		{
			str = temp;
			flag = 1;
		}
	}
	free(*pars);
	lst_print(*pars);
}

int check_var(char *line)
{
	int c = 0;
	while(*line && ft_isspace(*line))
		line++;
	if (*line == '=')
		return (0);
	else
	{
		while (*line)
		{
			if (*line == '=')
				c++;
			line++;
		}
		if (c > 1 || !c)
			return (0);
		else if (c == 1)
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

void var_parser (t_var **var, char *line)
{
	
	static int wc;

	while (*line && ft_isspace(*line))
		line++;
	if (!wc)
	{
		(*var) = malloc(sizeof(t_var));
		(*var)->key = get_key(line);
		while (*line != '=' && *line)
			line++;
		line++;
		(*var)->value = get_value(line);
		(*var)->prev = NULL;
		(*var)->next = NULL;

		wc++;
	}
	else
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
		wc++;
		*var = tem;
	}
}

int main()
{
	char buf[1024];
	t_parse *parse;
	parse = malloc(sizeof(t_parse));
	t_new *cmd;
	
	t_var *var;
	char *str;
	tgetent(buf, getenv("TERM"));
	// str = tgetstr("cl", NULL);
	// printf("%s", str);
	printf("");
	char *line;
	while (1)
	{
		line = ft_readline();
		if (!strcmp(line, "exit"))
			return (0);
		else if (!(strcmp(line, "")))
			;
		else if (!strcmp(line, "clear"))
			ft_clearscreen();
		else
		{
			if(*line && check_var(line))
			{
				var_parser(&var, line);
				lst_print_vars(var);
			}
			else
			{
				norm_parser(&cmd, line);
			}
		}
		free (line);
	}
	return(0);
}