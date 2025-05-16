#include "pushswap.h"

void	sort_three(t_stack **stack)
{
	if(ft_is_sorted(*stack))
		return;
	if(ft_is_reversed(*stack))
	{
		ra(stack);
		sa(stack);
		ft_printf("ra\nsa\n");
	}
	else if(ft_is_hogback(*stack))
	{
		rra(stack);
		sa(stack);
		ft_printf("rra\nsa\n");		
	}
	else
	{
		single_case(stack);	
	}
}

//Each remaining case needs only one op and each of the remaining cases has the max in a different position
//Thus the appropriate operation can be determined from the position of the max alone
void	single_case(t_stack **stack)
{
	int	first = (*stack)->num;
	int	second = (*stack)->next->num;
	int	third = (*stack)->next->next->num;

	if(second > first && second > third)
	{
		rra(stack);
		ft_printf("rra\n");
	}
	else if(third > second && third > first)
	{
		sa(stack);
		ft_printf("sa\n");
	}
	else
	{
		ra(stack);
		ft_printf("ra\n");
	}


}
