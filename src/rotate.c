#include "pushswap.h"

void	rotate(t_stack **stack)
{
	if(!stack || !*stack || !(*stack)->next)
		return;
	t_stack *first = *stack;
	t_stack *last = first;
	while(last->next)
		last = last->next;
	*stack = first->next;
	(*stack)->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
}

void	ra(t_stack **stack_a)
{
	rotate(stack_a);
}

void	rb(t_stack **stack_b)
{
	rotate(stack_b);
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	ra(stack_a);
	rb(stack_b);
}
