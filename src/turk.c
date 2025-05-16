#include "pushswap.h"

void	mechanical_turk(t_stack **stack_a, t_stack **stack_b)
{
	//blind push
	
	if(ft_stack_size(*stack_a)>=2)
	{
		pb(stack_a, stack_b);
		if(ft_stack_size(*stack_a)>=1)
			pb(stack_a, stack_b);
	}

	//push until A has only three remaining elements
	while(ft_stack_size(*stack_a)>3)
	{
		assign_target(*stack_a, *stack_b);
		pb(stack_a, stack_b);
		if((ft_stack_size(*stack_b)>=2)&&((*stack_b)->num < (*stack_b)->next->num))
			sb(stack_b);
	}

	//sort remaining three in A
	if(!ft_is_sorted(*stack_a))
		sort_three(stack_a);

	//reinsertion
	while(*stack_b)
	{
		t_stack *cheapest = find_cheapest_node(*stack_a, *stack_b);
		rotate_to_target(stack_a, cheapest->target_pos);
		pa(stack_a,stack_b);
	}

	//final rotation
	int min_pos = find_min_position(*stack_a);
	rotate_to_target(stack_a, min_pos);
}
