/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniezgod <aniezgod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:20:53 by aniezgod          #+#    #+#             */
/*   Updated: 2023/12/11 09:20:54 by aniezgod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status_code;

char	*ft_here_doc_str(char *str[2], size_t len, char *limit, char *trigger)
{
	char	*temp;

	while (g_status_code != 130 && (!str[0] || ft_strncmp(str[0], \
	limit, len) || ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", trigger, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	ft_here_doc(char *str[2], char *aux[2])
{
	int		fd[2];

	g_status_code = 0;
	if (pipe(fd) == -1)
	{
		error_function(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = ft_here_doc_str(str, 0, aux[0], aux[1]);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_status_code == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
