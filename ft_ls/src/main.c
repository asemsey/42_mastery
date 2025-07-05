#include "../include/ft_ls.h"

int	main(int argc, char **argv, char **env) {
	(void)argc;
	(void)argv;
	// (void)env;
	t_filedata pwd;

	pwd.f_type = F_DIR;
	pwd.name = ft_getenv("PWD", env);
	if (!pwd.name)
		return 1;
	ft_printf("Path: %s\n", pwd.name);
	return 0;
}
