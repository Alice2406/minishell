/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triming_management_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniezgod <aniezgod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:22:01 by aniezgod          #+#    #+#             */
/*   Updated: 2023/12/11 09:22:02 by aniezgod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_wordcounting(const char *str, char *target, int c[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (str[c[0]] != '\0')
	{
		if (!ft_strchr(target, str[c[0]]))
		{
			c[1]++;
			while ((!ft_strchr(target, str[c[0]]) || q[0]) && str[c[0]] != '\0')
			{
				if (!q[1] && (str[c[0]] == '\"' \
				|| str[c[0]] == '\''))
					q[1] = str[c[0]];
				q[0] = (q[0] + (str[c[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				c[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			c[0]++;
	}
	return (c[1]);
}

static char	**put_in_tab(char **tab, char const *str, char *target, int i[3])
{
	int		len;
	int		quote[2];

	quote[0] = 0;
	quote[1] = 0;
	len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(target, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(target, str[i[0]]) \
		|| quote[0] || quote[1]) && str[i[0]])
		{
			quote[0] = (quote[0] + (!quote[1] && str[i[0]] == '\'')) % 2;
			quote[1] = (quote[1] + (!quote[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			tab[i[2]++] = "\0";
		else
			tab[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (tab);
}

char	**trim1(char const *str, char *target)
{
	char	**tab;
	int		word_counter;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!str)
		return (NULL);
	word_counter = ft_wordcounting(str, target, counts);
	if (word_counter == -1)
		return (NULL);
	tab = malloc((word_counter + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = put_in_tab(tab, str, target, i);
	tab[word_counter] = NULL;
	return (tab);
}
