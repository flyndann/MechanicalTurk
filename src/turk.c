#include "pushswap.h"

void double_smart_rotate(t_stack **a, t_stack **b, t_stack *b_node)
{
	int a_pos = b_node->target_pos;
	int b_pos = get_node_position(*b, b_node);
	int a_size = ft_stack_size(*a);
	int b_size = ft_stack_size(*b);

	// Both in first half: do rr
	while (a_pos > 0 && b_pos > 0 && a_pos <= a_size / 2 && b_pos <= b_size / 2)
	{
		rr(a, b);
		ft_printf("rr\n");
		a_pos--;
		b_pos--;
	}

	// Both in second half: do rrr
	while (a_pos > a_size / 2 && b_pos > b_size / 2)
	{
		rra(a);
		rrb(b);
		ft_printf("rrr\n");
		a_pos++;
		b_pos++;
		if (a_pos >= a_size) a_pos -= a_size;
		if (b_pos >= b_size) b_pos -= b_size;
	}

	// Finish rotating each stack independently
	smart_rotate(a, a_pos, 'a');
	smart_rotate(b, b_pos, 'b');
}


//from deepseek
int	get_node_position(t_stack *stack, t_stack *node)
{
	int	pos = 0;
	t_stack	*current = stack;
	while(current)
	{
		if(current == node)
			return pos;
		pos++;
		current = current->next;
	}
	return -1;

}

//from deepseek
t_stack	*find_max_node(t_stack *stack)
{
	t_stack	*current = stack;
	t_stack *max_node= stack;
	while(current)
	{
		if(current->num > max_node->num)
			max_node = current;
		current = current->next;
	}
	return max_node;
}

t_stack	*find_min_node(t_stack *stack)
{
	t_stack	*current = stack;
	t_stack	*min_node = stack;
	while(current)
	{
		if(current->num < min_node->num)
			min_node = current;
		current = current->next;
	}
	return min_node;
}

/**
 * Finds the node with the closest smaller value to the given number
 * @param stack the stack to searching
 * @param num The number to find closest smaller value to
 * @return Node with closest smaller value, or NULL if none exists
 */
t_stack	*find_closest_smaller(t_stack *stack, int num)
{
	if(!stack)
		return NULL;
	t_stack *current = stack;
	t_stack *closest = NULL;
	int max_smaller = INT_MIN;

	while(current)
	{
		if(current->num < num && current->num > max_smaller)
		{
			max_smaller = current->num;
			closest = current;
		}
		current = current->next;
	}
	return closest;
}

/**
 * Calculates rotation cost for a position in stack
 * @param stack The stack to rotate
 * param pos Position to rotate to
 * return Number of rotations needed
 */
int	get_rotation_cost(t_stack *stack, int pos)
{
	int	size;

	size = ft_stack_size(stack);
	if(pos<= size / 2)
		return pos;
	else
		return size - pos;
}

/**
 * Rotates stack to positon using most efficient rotation
 * @param stack Pointer to stack
 * @param pos position to rotate to
 * @param stack_name Name of stack ('a' or 'b' for output
 */
void	smart_rotate(t_stack **stack, int pos, char stack_name)
{
	if(!stack || !*stack)
		return;
	int size = ft_stack_size(*stack);
	if(pos <= size / 2)
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
		while(pos-- > 0)
		{
			if(stack_name == 'a')
			{
				rra(stack);
				ft_printf("rra\n");
			}
			else
			{
				rrb(stack);
				ft_printf("rrb\n");
			}
		}
	}
}

/**
 * Assigns target positions for elemnts in stack B
 * @param a stack A
 * parma b Stack B
 */
void	assign_target(t_stack *a, t_stack *b)
{
	if(!a || !b)
		return;
	t_stack *current_b = b;
	t_stack *target_a;
	int a_size = ft_stack_size(a);
	while(current_b)
	{
		target_a = find_closest_smaller(a, current_b->num);
		if(!target_a)
			target_a = find_min_node(a);
		current_b->target_pos = get_node_position(a, target_a);
		current_b->target_node = target_a;
		current_b->target_above_median = (current_b->target_pos > (a_size / 2));
		current_b = current_b->next;
	}
}

/**
 * Calculates the cost of moving a node from stack b to its target position in stack a;
 * @param a Stack A
 * param b Stack B
 * param b_node NOde in stack B
 * return Total cost of operation
 */
int	calculate_cost(t_stack *a, t_stack *b, t_stack *b_node)
{
	if(!a || !b || !b_node)
		return INT_MAX;
	int cost_a = get_rotation_cost(a, b_node->target_pos);
	int cost_b = get_rotation_cost(b,get_node_position(b, b_node));
	return(cost_a + cost_b);
}

/**
 * @param a Stack A
 * @param b Stack B
 * @return Node with lowest cost or NULL if stacks are empty
 */
t_stack	*find_cheapest_node(t_stack *a, t_stack *b)
{
	if(!a || !b)
		return NULL;
	t_stack *current = b;
	t_stack *cheapest = NULL;
	int	min_cost = INT_MAX;
	int current_cost;
	while(current)
	{
		current_cost = calculate_cost(a, b, current);
		if(current_cost < min_cost)
		{
			min_cost = current_cost;
			cheapest = current;
		}
		current = current->next;
	}
	return cheapest;
}

/**
 * Pushes two elements from stack A to stack B initially
 * @param stack_a Pointer to stack A
 * @param stack_b Pointer to stack B
 */
void	push_initial_elements(t_stack **stack_a, t_stack **stack_b)
{
	if(!stack_a || !stack_b || !*stack_a)
		return;
	if(ft_stack_size(*stack_a) >= 2)
	{
		pb(stack_a, stack_b);
		ft_printf("pb\n");
		if(ft_stack_size(*stack_a) >= 1)
		{
			pb(stack_a,stack_b);
			ft_printf("pb\n");
		
		//Optimizazion: sort the first two elements in B if needed
			if(ft_stack_size(*stack_b) >= 2 && (*stack_b)->num < (*stack_b)->next->num)
			{
				sb(stack_b);
				ft_printf("sb\n");
			}
		}
	}
}

/**
 * Pushes elements until stack A has only 3 elements left
 * @param stack_a Pointer to stack A
 * @param stack_b Pointer to stack B
 */
void	push_until_three_left(t_stack **stack_a, t_stack **stack_b)
{
	if(!stack_a || !stack_b || !*stack_a)
		return;
	while(ft_stack_size(*stack_a)>3)
	{
		assign_target(*stack_a, *stack_b);
		pb(stack_a, stack_b);
		ft_printf("pb\n");
		if(ft_stack_size(*stack_b)>=2&&(*stack_b)->num < (*stack_b)->next->num)
		{
			sb(stack_b);
			ft_printf("sb\n");
		}
	}
}

//there would be a sort three 
//here but alread have it

/**
 * Finds position of minimum value in stack
 * @param stack Stack to search
 * @return Position of minuimmvalue or -1 if stack empty
 */
int find_min_position(t_stack *stack)
{
	if(!stack)
		return -1;
	t_stack *current = stack;
	int min_val = stack->num;
	int position = 0;
	int min_pos = 0;
	while(current)
	{
		if(current->num < min_val)
		{
			min_val = current->num;
			min_pos = position;
		}
		current = current->next;
		position++;
	
	}
	return min_pos;
}

/**
 * reuinserts elements from stack B back to stack A
 * @param stack_a Pointer to stack A
 * @param stack_b Pointer to stack B
 */
void	reinsert_elements(t_stack **stack_a, t_stack **stack_b)
{
	while (*stack_b)
	{
		assign_target(*stack_a, *stack_b);
		t_stack *cheapest = find_cheapest_node(*stack_a, *stack_b);
		if (!cheapest)
			break;
		double_smart_rotate(stack_a, stack_b, cheapest);
		pa(stack_a, stack_b);
		ft_printf("pa\n");
	}
}

void mechanical_turk(t_stack **stack_a, t_stack **stack_b)
{
    if (!stack_a || !stack_b || !*stack_a)
        return;

    int size = ft_stack_size(*stack_a);

    if (size <= 1)
        return; // already sorted

    else if (size == 2)
    {
        if ((*stack_a)->num > (*stack_a)->next->num)
        {
            sa(stack_a);
            ft_printf("sa\n");
        }
        return;
    }
    else if (size == 3)
    {
        sort_three(stack_a);
        return;
    }

    // Main algorithm for larger stacks
    push_initial_elements(stack_a, stack_b);
    push_until_three_left(stack_a, stack_b);

    if (!ft_is_sorted(*stack_a))
        sort_three(stack_a);

    // Reinsert elements from stack B to stack A
    reinsert_elements(stack_a, stack_b);

    // Final rotate to position minimum element at the top
    smart_rotate(stack_a, find_min_position(*stack_a), 'a');
}

