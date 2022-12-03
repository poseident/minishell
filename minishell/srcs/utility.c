#include "../include/minishell.h"

char *ft_strdup(char *tmp)
{
	int i;
	char *line;

	i = 0;
	line = malloc(sizeof(char) * ft_strlen(tmp) + 1);
	while (tmp[i])
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *ft_variable_name_without_dollar(char *s)
{
	char *tmp;
	int i;
	int j;

	j = 0;
	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(s)));
	i++;
	while (s[i])
	{
		tmp[j] = s[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int ft_variable_len(char *input)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (input[i] != '=')
	{
		count++;
		i++;
	}
	count++;
	i++;
	while (input[i])
	{
		if (input[i] == 34)
		{
			i++;
			while (input[i] != 34 && input[i])
			{
				i++;
				count++;
			}
			if (input[i] == 34)
				i++;
		}
		else if (input[i] == 39)
		{
			i++;
			while (input[i] != 39 && input[i])
			{
				i++;
				count++;
			}
			if (input[i] == 39)
				i++;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

int ft_strchr(char *input, char *s)
{
	int i;

	i = 0;
	while (input[i] && s[i])
	{
		if (input[i] != s[i])
			return (-1);
		i++;
	}
	if (input[i] == '\0' && s[i] == '\0')
		return (1);
	else
		return (0);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
