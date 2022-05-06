#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termcap.h>
#include <readline/readline.h>
#include <string.h>
#include <readline/history.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int ft_strlen(const char *str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*k;
	size_t			count;

	k = s;
	count = 0;
	while (n)
	{
		*k++ = 0;
		n--;
		count++;
	}
	k = k - count - 1;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * count);
	return (ptr);
}


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*k;
	unsigned const char	*m;
	size_t				count;

	count = 0;
	k = dst;
	m = src;
	if (dst == NULL && src == NULL)
		return (dst);
	while (n)
	{
		*k++ = *m++;
		count++;
		n--;
	}
	m = m - count;
	return (k - count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		count1;
	int		count2;

	if (!s1 || !s2)
		return (NULL);
	count1 = ft_strlen(s1);
	count2 = ft_strlen(s2);
	str = (char *) ft_calloc((count1 + count2 + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, count1);
	ft_memcpy(str + count1, s2, count2);
	return (str);
}

static int	count(char const *s, char c)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			l++;
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			l++;
		i++;
	}
	return (l);
}

static char	**splitter(char const *s, char c, char **str, int *i)
{
	while (i[0] < i[4])
	{
		i[1] = 0;
		while (s[i[2]] == c && s[i[2]])
			i[2]++;
		while (s[i[2]] != c && s[i[2]])
		{
			i[1]++;
			i[2]++;
		}
		str[i[0]] = (char *)malloc(sizeof(char) * (i[1] + 1));
		i[2] -= i[1];
		i[3] = 0;
		while (s[i[2]] != c && s[i[2]])
		{
			str[i[0]][i[3]] = s[i[2]];
			i[3]++;
			i[2]++;
		}
		str[i[0]++][i[3]] = '\0';
	}
	str[i[0]] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i[5];
	int		j;

	j = 0;
	while (j < 5)
		i[j++] = 0;
	if (!s)
		return (NULL);
	i[4] = count(s, c);
	str = (char **) malloc(sizeof(*str) * (i[4] + 1));
	if (!str)
		return (NULL);
	return (splitter(s, c, str, i));
}

void ft_execve(const char *data, char **argv)
{
	char *envp[] = {0};

	execve(data, argv, envp);
}

int main ()
{
	char **str;
	char *data;
	int fd;
	int i;
	char *av[] = {"echo", "hello", 0};
	
	str = ft_split(getenv("PATH"), ':');
	i = -1;
	while (str[++i] != NULL)
	{
		printf("%s ", str[i]);
		data = ft_strjoin(str[i],"/echo");
		fd = access(data, F_OK);
		if (fd == -1)
			printf("Error Accessing \n");
		else
		{
			printf("OK \n");
			ft_execve(data, av);
			return (0);
		}
		free (data);
		free (str[i]);
	}
	return (0);
}