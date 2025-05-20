#include "../libft/libft.h"
#include "pushswap.h"

char	*ft_join_args(int argc, char **argv)
{
	char	*joined;
	int	i;

	joined = ft_strdup("");
	i = 1;
	while(i < argc)
	{
		char	*temp = ft_strjoin(joined,argv[i]);
		free(joined);
		joined = ft_strjoin(temp, " ");
		free(temp);
		i++;
	}
	return joined;

}

int	main(int argc, char **argv)
{

	t_stack	*stack_a = NULL;
	t_stack *stack_b = NULL;
	

	
	if(argc == 2)
		stack_a = ft_fill_stack(argv[1]);
	else if(argc > 2)
	{
		char	*joined = ft_join_args(argc,argv);
		stack_a = ft_fill_stack(joined);
		free(joined);
	}
	
	if(ft_stack_size(stack_a) > 3)
			mechanical_turk(&stack_a, &stack_b);
	else
		sort_three(&stack_a);
	


	return(0);
}
