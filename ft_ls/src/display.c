#include "ft_ls.h"

void		display_entries(t_list *files, int flags);
void		display_long(t_list *files, int flags);
void		display_users(t_filedata *data, int sizes[4]);
void		display_number(unsigned long number, int size);
void		display_short(t_list *files, int flags);

// ----------------------------------------------------------------------

void display_entries(t_list *files, int flags) {
	if (!files)
		return ;
	if (flags & LONG) {// case -l
		display_long(files, flags);
	} else {// default
		display_short(files, flags);
	}
	write(1, "\n", 1);//HERE this results in extra newline at the end of output
}

void display_long(t_list *files, int flags) {
	time_t now = time(NULL);
	int sizes[4];
	ft_bzero(sizes, 4 * sizeof(int));
	ft_printf("total %d\n", size_columns(files, sizes, flags));
	while (files) {
		t_filedata *data = (t_filedata *)files->content;
		if (!(flags & HIDDEN) && data->name[0] == '.') {
			files = files->next;
			continue;
		}
		if (data->bytes >= 0) {
			ft_printf("%c%s ", data->f_type, data->permissions);
			display_number(data->links, sizes[0]);
			display_users(data, sizes);
			display_number(data->bytes, sizes[3]);
			display_modified(data->modified, now);
			ft_printf("%s\n", data->name);
		}
		files = files->next;
	}
}

// printf the user and group columns with correct padding after
void display_users(t_filedata *data, int sizes[4]) {
	if (!data || data->bytes < 0)
		return;
	char *user = getpwuid(data->own_user)->pw_name;
	if (user) {
		ft_printf("%s", user);
		print_space(sizes[1]-ft_strlen(user)+1);
	} else {
		ft_printf("%u", data->own_user);
		print_space(sizes[1]-ft_digits_u(data->own_user, 10)+1);
	}
	user = getgrgid(data->own_group)->gr_name;
	if (user) {
		ft_printf("%s", user);
		print_space(sizes[2]-ft_strlen(user)+1);
	} else {
		ft_printf("%u", data->own_group);
		print_space(sizes[2]-ft_digits_u(data->own_group, 10)+1);
	}
}

void	display_number(unsigned long number, int size) {
	print_space(size-ft_digits_lu(number, 10));
	ft_printf("%u ", number);
}

void	display_short(t_list *files, int flags) {
	while (files) {
		t_filedata *data = (t_filedata *)files->content;
		if (!(flags & HIDDEN) && data->name[0] == '.') {
			files = files->next;
			continue;
		}
		if (data->bytes >= 0)
			ft_printf("%s\t\t", data->name);
		files = files->next;
	}
}


