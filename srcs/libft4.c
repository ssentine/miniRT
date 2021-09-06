/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:40:29 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 16:40:32 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *str1;
	unsigned char *str2;

	if (!n || dest == src)
		return (dest);
	str1 = (unsigned char*)src;
	str2 = (unsigned char*)dest;
	while (n--)
		*str2++ = *str1++;
	return (dest);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(const char *s1)
{
	int		len;
	char	*ptr;

	len = ft_strlen(s1) + 1;
	ptr = (char*)malloc(len * sizeof(char));
	if (ptr)
		ft_memcpy(ptr, s1, len);
	return (ptr);
}

void		*ft_calloc(size_t count, size_t size)
{
	unsigned	n;
	void		*ptr;

	n = count * size;
	ptr = malloc(n);
	if (ptr)
		ft_bzero(ptr, n);
	return (ptr);
}
