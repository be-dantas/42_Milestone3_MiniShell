void	free_list(t_env **begin_list)
{
	while (*begin_list)
	{
		free((*begin_list->key));
		free((*begin_list->value));
		(*begin_list)=(*begin_list)->next;
	}
}
