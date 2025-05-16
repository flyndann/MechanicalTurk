#include "pushswap.h"

void	smart_rotate(t_stack **stack, int pos, char stack_name)
{
	int size = ft_stack_size(*stack);
	if(pos<=size/2)
	{
		while(pos-- > 0)
		{
			if(stack_name == 'a')
			{
				ra(stack);
				ft_printf("ra\n");
			}
			else
			{
				rb(stack);
				ft_printf("rb\n");
			}
		}
	}
	else
	{
		pos = size - pos;
		while(pos --> 0)
		{
			if(stack_name == 'a')
			{
				rra(stack);
				ft_printf("rra\n");
			}else
			{
				rrb(stack);
				ft_printf("rrb\n");
			}
		}
	}
}

void	assign_target(t_stack *a, t_stack *b)
{
	t_stack	*current_b = b;
	t_stack *target_a;
	int a_size = ft_stack_size(a);
	while(current_b)
	{
		target_a = find_closest_smaller(a, current_b->num);
		if(!target_a)
			target_a = find_max_node(a);
		
		current_b->target_pos = get_node_position(a, target_a);
		current_b->target_node = target_a;
		
		current_b->target_above_median = (current_b->target_pos > (a_size/2));
		current_b = current_b->next;
	}
}

int	calculate_cost(t_stack *a, t_stack *b_node)
{
	int	cost_a = get_rotation_cost(a, b_node->target_pos);
	int	cost_b = get_rotation_cost(b, get_node_position(b, b_node);
			return (cost_a + cost_b);
}

void	mechanical_turk(t_stack **stack_a, t_stack **stack_b)
{
	//blind push
	
	if(ft_stack_size(*stack_a)>=2)
	{
		pb(stack_a, stack_b);
		ft_printf("pb\n");
		if(ft_stack_size(*stack_a)>=1){
			pb(stack_a, stack_b);
			ft_printf("pb\n");
			}
	}

	//push until A has only three remaining elements
	while(ft_stack_size(*stack_a)>3)
	{
		assign_target(*stack_a, *stack_b);
		pb(stack_a, stack_b);
		ft_printf("pb\n");
		ft_print_stack(stack_a);
		if((ft_stack_size(*stack_b)>=2)&&((*stack_b)->num < (*stack_b)->next->num))
		{
			sb(stack_b);
			ft_printf("sb\n");
		}
	}

	//sort remaining three in A
	if(!ft_is_sorted(*stack_a))
		sort_three(stack_a);

	//reinsertion
	while(*stack_b)
	{
		update_target_positions(*stack_a,*stack_b);
		t_stack *cheapest = find_cheapest_node(*stack_a, *stack_b);
		smart_rotate(a, cheapest->target_pos, 'a');
		smart_rotate(b, get_node_position(*stack_b,cheapest),'b');
		pa(stack_a,stack_b);
	}

	//final rotation
	smart_rotate(a, find_min_posiiton(*a),'a');
}
