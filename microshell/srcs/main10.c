/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:15:46 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:19:54 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**fill_bin2(char **bin)
{
	bin[20] = ft_strdup("mkdir");
	bin[21] = ft_strdup("mv");
	bin[22] = ft_strdup("pax");
	bin[23] = ft_strdup("ps");
	bin[24] = ft_strdup("pwd");
	bin[25] = ft_strdup("rm");
	bin[26] = ft_strdup("rmdir");
	bin[27] = ft_strdup("sh");
	bin[28] = ft_strdup("sleep");
	bin[29] = ft_strdup("stty");
	bin[30] = ft_strdup("sync");
	bin[31] = ft_strdup("syslog.py");
	bin[32] = ft_strdup("tcsh");
	bin[33] = ft_strdup("test");
	bin[34] = ft_strdup("unlink");
	bin[35] = ft_strdup("wait4path");
	bin[36] = ft_strdup("zsh");
	bin[37] = NULL;
	return (bin);
}

char	**fill_bin(void)
{
	char	**bin;

	bin = malloc(sizeof(char *) * 38);
	bin[0] = ft_strdup("[");
	bin[1] = ft_strdup("bash");
	bin[2] = ft_strdup("cat");
	bin[3] = ft_strdup("chmod");
	bin[4] = ft_strdup("cp");
	bin[5] = ft_strdup("csh");
	bin[6] = ft_strdup("dash");
	bin[7] = ft_strdup("date");
	bin[8] = ft_strdup("dd");
	bin[9] = ft_strdup("df");
	bin[10] = ft_strdup("echo");
	bin[11] = ft_strdup("ed");
	bin[12] = ft_strdup("expr");
	bin[13] = ft_strdup("hostname");
	bin[14] = ft_strdup("kill");
	bin[15] = ft_strdup("ksh");
	bin[16] = ft_strdup("launchctl");
	bin[17] = ft_strdup("link");
	bin[18] = ft_strdup("ln");
	bin[19] = ft_strdup("ls");
	bin = fill_bin2(bin);
	return (bin);
}

int	input_size(char *input)
{
	int	i;
	int	j;
	int	len;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (input[i] && input[i] <= 32)
		i++;
	while (input[j])
		j++;
	j--;
	while (input[j] <= 32)
	{
		count++;
		j--;
	}
	count += i;
	len = (ft_strlen(input) - count);
	return (len);
}

int	ft_last_caractere(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	i--;
	while (input[i] <= 32)
		i--;
	return (i);
}

char	*ft_lexer_simplify_count2(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 32)
			str[i] = ' ';
	}
	return (&str[0]);
}
