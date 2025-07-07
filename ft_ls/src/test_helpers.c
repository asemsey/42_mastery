# include "../include/ft_ls.h"

void		test_arg_init(t_ls *data);
void		test_modtime(t_ls *data);

// ----------------------------------------------------------------------

void test_arg_init(t_ls *data) {
	ft_printf("PWD = %s\n", data->pwd);
	if (data->files) {
		for (int i = 0; data->files[i] != NULL; i++) {
			printf("\t%d  |  %s\n", i, data->files[i]->path);
		}
	}
	int flags = data->cmd_flags;
	ft_printf("set flags: %d\n", flags);
	if (flags & LONG)
		ft_printf("LONG (-l)\n");
	if (flags & RECURSIVE)
		ft_printf("RECURSIVE (-R)\n");
	if (flags & HIDDEN)
		ft_printf("HIDDEN (-a)\n");
	if (flags & REVERSE)
		ft_printf("REVERSE (-r)\n");
	if (flags & TIMESORT)
		ft_printf("TIMESORT (-t)\n");
	if (flags & INVALID)
		ft_printf("INVALID (!!!)\n");
}

void test_modtime(t_ls *data) {
	int i = 0;
	if (!data->files) {
		ft_printf("no files\n");
		return ;
	}
	if (!(data->cmd_flags & LONG)) {
		while (data->files[i])
			ft_printf("%s\t\t", data->files[i++]->name);
		write(1, "\n", 1);
		return ;
	}
	// -l flag
	time_t now = time(NULL);
	while (data->files[i]) {
		if (data->files[i]->bytes > 0) {
			ft_printf("%c%s  %d [user]  [user?]  %d ", data->files[i]->f_type, data->files[i]->permissions, data->files[i]->links, data->files[i]->bytes);
			print_modified(data->files[i]->modified, now);
			ft_printf(" %s\n", data->files[i]->name);
		}
		i++;
	}
}
