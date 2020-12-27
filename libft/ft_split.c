/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarry <skarry@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 21:37:52 by skarry            #+#    #+#             */
/*   Updated: 2020/05/22 20:21:14 by skarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*free_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int		count_sym(char const *s, char c)
{
	int i;

	i = 0;
	while (*s != c && *(s++))
		i++;
	return (i);
}

static int		count_words(char const *s, char c)
{
	int		cut;

	cut = 0;
	if (*s && *s != c)
	{
		s++;
		cut++;
	}
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s != c && *s)
				cut++;
		}
		if (!(*s))
			return (cut);
		s++;
	}
	return (cut);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	if (!s || !(str = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!(str[j] = (char*)malloc(sizeof(char) * (count_sym(s, c) + 1))))
				return (free_str(str));
			while (*s != c && *s)
				str[j][i++] = *s++;
			str[j++][i] = '\0';
			i = 0;
		}
	}
	str[j] = NULL;
	return (str);
}
