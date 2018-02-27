/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:18:10 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:32:05 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	words;
	int		count_next;

	words = 0;
	count_next = 1;
	while (*s)
	{
		if (count_next && *s != c)
		{
			words++;
			count_next = 0;
		}
		if (*s == c)
			count_next = 1;
		s++;
	}
	return (words);
}

char			**ft_strsplit(const char *s, char c)
{
	size_t	words;
	size_t	len;
	int		i;
	char	**ret;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	ret = (char**)ft_memalloc(sizeof(*ret) * words + 1);
	if (ret == NULL)
		return (NULL);
	ret[words] = 0;
	i = -1;
	while ((size_t)++i < words)
	{
		while (*s == c)
			s++;
		len = ft_strlenc(s, c);
		ret[i] = ft_strndup(s, len);
		s += len;
	}
	return (ret);
}
