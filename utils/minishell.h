/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:58:36 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/20 17:27:46 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

typedef struct  s_collect
{
    struct s_collect    *next;
    void                *data;
}   t_collect;

t_collect	*create_item(void *data);
t_collect	*last_item(t_collect *begin_list);
t_collect	*init_collect(void);
void		close_collect(t_collect *init);
void		*put_item(t_collect **begin_list, void *data);

#endif
