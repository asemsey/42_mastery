#include "ft_ls.h"

int			size_columns(t_list *files, int sizes[4], int flags);
void		display_modified(time_t seconds, time_t now);
void		print_space(int n);

// ----------------------------------------------------------------------

// set the max columns sizes in sizes[4], also return total blocks
int	size_columns(t_list *files, int sizes[4], int flags) {
	char	*user = NULL;
	int		blocks = 0;
	while (files) {
		// 0-links  1-user  2-group  3-bytes
		t_filedata *data = (t_filedata *)files->content;
		if ((!(flags & HIDDEN) && data->name[0] == '.') || data->bytes < 0) {
			files = files->next;
			continue;
		}
		blocks += data->blocks;
		sizes[0] = ft_max(sizes[0], ft_digits_lu(data->links, 10));
		user = getpwuid(data->own_user)->pw_name;
		if (user)
			sizes[1] = ft_max(sizes[1], ft_strlen(user));
		else
			sizes[1] = ft_max(sizes[1], ft_digits_u(data->own_user, 10));
		user = getgrgid(data->own_group)->gr_name;
		if (user)
			sizes[2] = ft_max(sizes[2], ft_strlen(user));
		else
			sizes[2] = ft_max(sizes[2], ft_digits_u(data->own_group, 10));
		sizes[3] = ft_max(sizes[3], ft_digits_lu(data->bytes, 10));
		files = files->next;
	}
	return blocks/2;//block size is 1k, filestat gives 512
}

// print the date string in the ls -l format, no '\n'
void	display_modified(time_t seconds, time_t now) {
	char *str = ctime(&seconds);
	char *year = str + 20;
	char *date = str + 4;
	time_t diff;

	if (ft_strlen(str) < 25)// format different?
		return;
	*(year + 4) = '\0';

	diff = now - seconds;// if past > 0, future < 0
	if (diff < 0)
		diff = -diff;
	if (diff > 15552000) {//six months
		*(date + 6) = '\0';
		ft_printf("%s %s  ", date, year);
	} else {
		*(date + 12) = '\0';
		ft_printf("%s ", date);
	}
	// Www Mmm dd hh:mm:ss yyyy\n
	// Mmm dd hh:mm -> Jul  7 10:55
	// Mmm dd yyyy  -> Jul  7 2025
}

void	print_space(int n) {
	int i = 0;
	while (i < n) {
		write(1, " ", 1);
		i++;
	}
}
