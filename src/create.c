#include "../libft/libft.h"
#include "pushswap.h"

t_stack *ft_create_node(int num)
{
	t_stack	*new_node = malloc(sizeof(t_stack));
	if(!new_node)
		return NULL;
	new_node->num = num;
	new_node->index=-1;
	new_node->push_cost=0;
	new_node->above_median=false;
	new_node->cheapest=false;
	new_node->next=NULL;
	new_node->prev=NULL;
	new_node->target_node=NULL;
	new_node->head=NULL;
	new_node->tail=NULL;
	return new_node;
}

t_stack	*ft_fill_stack(char *arg)
{
	t_stack	*stack = NULL;
	char	**nums = ft_split(arg,' ');
	int 	i;

	i= 0;
	while(nums[i])
	{
		int	n;
		n = ft_atoi(nums[i]);
		ft_append_node(&stack, ft_create_node(n));
		i++;
	}	
	//free ft_split result
	i = 0;
	while(nums[i])
		free(nums[i++]);
	free(nums);

	return stack;
}
