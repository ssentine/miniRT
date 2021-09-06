/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:04:23 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 16:04:24 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*str;

	i = 0;
	str = s;
	if (n == 0)
		return ;
	while (i < n)
		str[i++] = 0;
}

static size_t	count_words(char const *s)
{
	int			count;
	int			is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == ',')
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	w_s(char const *s, int pos)
{
	size_t	len;

	len = 0;
	while (s[pos])
	{
		if (s[pos] == ' ' || s[pos] == '\t' || s[pos] == ',')
			return (len);
		len++;
		pos++;
	}
	return (len);
}

char			**ft_split(char const *s)
{
	t_split sp;

	sp.i = -1;
	sp.j = 0;
	sp.k = 0;
	sp.words = count_words(s);
	if (!(sp.t = malloc(sizeof(char*) * (sp.words + 1))))
		return (NULL);
	while (s[++sp.i])
	{
		if (s[sp.i] != ' ' && s[sp.i] != '\t' && s[sp.i] != ',')
		{
			if (sp.k == 0)
				if (!(sp.t[sp.j] = (char*)malloc(w_s(s, sp.i) + 1)))
					return (NULL);
			sp.t[sp.j][sp.k] = s[sp.i];
			sp.t[sp.j][++sp.k] = '\0';
		}
		if (((s[sp.i] == ' ' || s[sp.i] == '\t' || s[sp.i] == ',') &&
(s[sp.i + 1] != ' ' && s[sp.i + 1] != '\t' && s[sp.i + 1] != ',') &&
sp.k > 0) && (sp.k = 0) == 0)
			sp.j++;
	}
	sp.t[sp.words] = 0;
	return (sp.t);
}

int				ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] & s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
