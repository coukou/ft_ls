/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:48:10 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/09 21:33:47 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include <stdlib.h>

char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char*));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmap(const char *s, char (*f)(char));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strequ(const char *s1, const char *s2);
int		ft_strnequ(const char *s1, const char *s2, size_t n);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strjoin_free(const char *s1, const char *s2);
char	*ft_strtrim(const char *s);
char	**ft_strsplit(const char *s, char c);
char	*ft_strrev(char *s);
size_t	ft_strlen(const char *str);
size_t	ft_strlenc(const char *str, int c);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t len);
char	*ft_strdupc(const char *str, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t len);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strncat(char *s1, char *s2, size_t n);
size_t	ft_strlcat(char *s1, char *s2, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *src, const char *find);
char	*ft_strnstr(const char *src, const char *find, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strfind(const char *str, int c);
char	*ft_strtolower(char *str);
char	*ft_strtoupper(char *str);

#endif
