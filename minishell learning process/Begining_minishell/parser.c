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

typedef struct hist
{
	char	*log;
	struct hist *next;
	struct list *prev;
}	t_hist;

typedef struct parse
{
	t_new *cmd_lst;
	t_var *var_lst;
	t_env *env_lst;
	t_hist *hist_lst;
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

char *get_word(char *line)
{
	char *word;

	int len = get_word_len(line);
	if (len <= 0)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	while (ft_isspace(*line) && *line)
		line++;
	int i = 0;
	
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
	printf("hiffd\n");
	(*pars)->token = str;
	(*pars)->next = NULL;
	(*pars)->prev = NULL;
	// if (*str)
	// {
	// 	(*pars)->token = str;
	// 	(*pars)->next = NULL;
	// 	(*pars)->prev = NULL;
	// }
	// else if (*str && !*pars)
	// {
	// 	t_new *temp;
	// 	temp = malloc(sizeof(t_new));
	// 	temp->token = str;
	// 	(*pars)->next = temp;
	// 	temp->next = NULL;
	// 	temp->prev = (*pars);
	// }
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
	printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
	while ((*pars)->next)
	{
		printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
		(*pars) = (*pars)->next;
	}
	printf("%p %p %s %p \n", (*pars), (*pars)->prev, (*pars)->token, (*pars)->next);
	(*pars) = par;

}
void lst_print(t_new *pars)
{
	while(pars != NULL)
	{
		printf("%s \n", pars->token);
		pars= pars->next;
	}
}

void parser (t_new **pars, char *str)
{
	
	int wc;
	wc = 0;

	// printf("%s", str);
	// printf("%s", get_word(str));
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
		while(*str && !ft_isspace(*str))
			str++;
	}
	free(*pars);
	// lst_print(*pars);
}

int main()
{   
	char buf[1024];
    char *str;
	t_new *pars;
    tgetent(buf, getenv("TERM"));
    str = tgetstr("cl", NULL);
	printf("%s", str);
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
			parser(&pars, line);
		free (line);
	}
	return(0);
}