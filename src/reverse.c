#include "pushswap.h"

void	reverse(t_stack **stack)
{
	if(!stack || !*stack || !(*stack)->next)
		return;
	t_stack	*last = *stack;
	while(last->next)
		last = last->next;
	t_stack	*second_last = last->prev;
	second_last->next = NULL;
	last->prev = NULL;
	last->next = *stack;
	(*stack)->prev = last;
	*stack = last;
}

void	rra(t_stack **stack_a)
{
	reverse(stack_a);
}

void	rrb(t_stack **stack_b)
{
	reverse(stack_b);
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	reverse(stack_a);
	reverse(stack_b);
}

