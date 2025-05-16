#include "pushswap.h"

t_stack	*ft_pop(t_stack **stack)
{
	if(stack == NULL || *stack == NULL)
		return NULL;
	t_stack *temp = *stack;
	*stack = temp->next;
	if(*stack)
		(*stack)->prev = NULL;
	temp->next=NULL;
	temp->prev = NULL;
	return (temp);
}

void	ft_stack_clear(t_stack **stack)
{
	t_stack	*current;
	t_stack	*next;

	if(!stack || !*stack)
		return;
	current = *stack;
	while(current){
		next = current->next;
		free(current);
		current=next;
	}
	*stack = NULL;
}
