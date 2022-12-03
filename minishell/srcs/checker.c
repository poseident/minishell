#include "../include/minishell.h"

int	ft_checker(char *input)
{
	int i;

	i = 0;
	if (!input)
		return (-1);
	else if (nothing_check(input) == -1)
		return (-1);
	else if (quote_check(input) == -1)
	{
		printf("quote>\n");
		return (-1);
	}
	else
		return (0);
}

int quote_check(char *input)
{
	int i;
	int quote;

	i = 0;
	while (input[i])
	{
		quote = 0;
		if (input[i] == 59 && quote == 0)
			return (-1);
		else if (input[i] == 92 && quote == 0)
			return (-1);
		else if (input[i] == 34)
		{
			quote = 1;
			while (quote != 2 && input[i])
			{
				i++;
				if (input[i] == 34)
					quote = 2;
			}
			if (quote == 1)
				return (-1);
		}
		else if (input[i] == 39)
		{
			quote = 1;
			while (quote != 2 && input[i])
			{
				i++;
				if (input[i] == 39)
					quote = 2;
			}
			if (quote == 1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int nothing_check(char *input)
{
	int i;

	i = 0;
	while (input[i] && input[i] <= 32)
		i++;
	if (input[i] == '\0')
		return (-1);
	else
		return (0);
}