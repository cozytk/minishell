
int		main(void)
{
	t_all	*a;
	char	*line;

	a = malloc(sizeof(t_all) * 1);
    init(a);
	while (1)
	{
		init_index(a);
		get_next_line(0, &line);
		while (line[a->p.i])
		{
			parsing(a, line);
			show_com(a);
			show_arg(a);
			free_com_arg(a);
		}
		free(line);
		system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	}
}
