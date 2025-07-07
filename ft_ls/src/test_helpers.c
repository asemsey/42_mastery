# include "../include/ft_ls.h"

void		test_arg_init(t_ls *data);

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
