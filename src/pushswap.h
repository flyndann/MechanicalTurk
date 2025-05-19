/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:22:51 by daflynn           #+#    #+#             */
/*   Updated: 2025/03/26 13:22:39 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include "../libft/libft.h"
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

//Mechanical Turk style doubly linked list
typedef	struct s_stack{

	int	num;
	int	index;
	int	push_cost;
	int	target_pos;
	bool	above_median;
	bool	cheapest;
	struct s_stack	*next;
	struct s_stack	*prev;
	struct s_stack	*target_node;
	struct s_stack	*head;
	struct s_stack	*tail;
	
}	t_stack;


t_stack	*ft_create_node(int num);
void    ft_append_node(t_stack **stack, t_stack *new_node);
t_stack *ft_fill_stack(char *arg);
void    ft_print_stack(t_stack *stack);
t_stack *ft_pop(t_stack **stack);
void    ft_push(t_stack **stack, t_stack *new_node);
int     ft_stack_size(t_stack *stack);
int     ft_is_sorted(t_stack *stack);
void 	pb(t_stack **stack_a, t_stack **stack_b);
void	pa(t_stack **stack_a, t_stack **stack_b);
void    swap(t_stack **stack);
void    sa(t_stack **stack_a);
void    sb(t_stack **stack_b);
void    rr(t_stack **stack_a, t_stack **stack_b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void    rotate(t_stack **stack);
void    reverse(t_stack **stack);
void    rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **stack_a, t_stack **stack_b);
int     ft_is_hogback(t_stack *stack);
void    sort_three(t_stack **stack);
void	single_case(t_stack **);
int     ft_is_reversed(t_stack *stack);
char    *ft_join_args(int argc, char **argv);
#endif
