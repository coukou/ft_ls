/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 12:11:12 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/27 12:22:49 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DICT_H
# define FT_DICT_H

typedef struct		s_dict
{
	char			*key;
	void 			*value;
	struct s_dict	*next;
}					t_dict;

void	*ft_dict_get(t_dict *dict, char *key);
void	ft_dict_del(t_dict **dict, char *key, void *value);
void	ft_dict_set(t_dict **dict, char *key, void *value);

#endif
