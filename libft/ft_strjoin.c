/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadye <asadye@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:31:47 by achopper          #+#    #+#             */
/*   Updated: 2021/07/21 14:26:54 by achopper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		s1_len;
	char	*tmp;

	s1_len = (int)ft_strlen(s1);
	if (NULL == s1 || NULL == s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2)) + 1);
	tmp = res;
	if (NULL == res)
		return (NULL);
	ft_memcpy(res, s1, s1_len);
	res += s1_len;
	ft_memcpy(res, s2, ft_strlen(s2));
	res += ft_strlen(s2);
	*res = '\0';
	free((void *)s1);
	return (tmp);
}
