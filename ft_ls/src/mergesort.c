#include "ft_ls.h"

t_list		*merge_sort(t_list *lst, t_list *(*comp)(t_list *, t_list *), int len);
// t_list	*merge_sort(t_list *lst, t_list *(*comp)(t_list *, t_list *));
t_list	*comp_alpha(t_list *l1, t_list *l2);

// ----------------------------------------------------------------------

t_list		*merge_sort(t_list *lst, t_list *(*comp)(t_list *, t_list *), int len) {
	// split in half using pointers
	t_list *f1 = lst;
	t_list *f2 = lst;
	t_list *c = NULL;
	t_list *result = NULL;
	int i = 1;

	ft_printf("DEBUG called merge_sort len=%d lst=%s\n", len, ((t_filedata *)(lst->content))->name);
	if (!lst || !lst->next || len < 1) {
		ft_printf("OOF len=%d\n", len);
		return lst;
	}
	while (i <= len/2) {
		if (!f2)
			break;
		f2 = f2->next;
		i++;
		ft_printf("DEBUG set f2=%s\n", ((t_filedata *)(f2->content))->name);
	}
	// while (i < len) {
	// 	lst = lst->next;
	// }
	// lst->next = NULL;//separate f1 from f2
	if (len > 1) {
		ft_printf("DEBUG call f1\n");
		f1 = merge_sort(f1, comp, len / 2 + len % 2);
		ft_printf("DEBUG call f2\n");
		f2 = merge_sort(f2, comp, len / 2);//SORT
	}
	while (f1 && f2 && f1->content && f2->content && (i < len/2 + len%2)) {
		c = comp(f1, f2);
		ft_printf("DEBUG big loop comp=%s\n", ((t_filedata *)(c->content))->name);
		if (!c) {
			ft_printf("ERROR null response from comparison\n");
			break;
		}
		ft_lstadd_back(&result, c);
		if (c == f1) {
			i++;
			f1 = f1->next;
		}
		else
			f2 = f2->next;
	}
	if (f1 && f1->content)
		ft_lstadd_back(&result, f1);
	else if (f2 && f2->content)
		ft_lstadd_back(&result, f2);
	ft_printf("ft_ls: merge_sort returns\n");
	return result;
}

t_list	*comp_alpha(t_list *l1, t_list *l2) {
	// NULL checks
	if (!l1 || !l1->content) {
		if (l2 && l2->content)
			return l2;
		return NULL;
	}
	if (!l2 || !l2->content)
		return l1;

	t_filedata *f1 = (t_filedata *)l1->content;
	t_filedata *f2 = (t_filedata *)l2->content;
	int len1 = ft_strlen(f1->name);
	int len2 = ft_strlen(f2->name);
	int c = ft_strncmp(f1->name, f2->name, (len1 <= len2 ? len1 : len2));
	if (c == 0) // return shorter one
		return (len1 <= len2 ? l1 : l2);
	return (c < 0 ? l1 : l2);
}

// DEBUG OUTPUT
// -rw-rw-r--  1 asemsey  asemsey  4396 Jul 30 16:25 directories.c
// -rw-rw-r--  1 asemsey  asemsey  3471 Jul 30 15:36 file_info.c
// -rw-rw-r--  1 asemsey  asemsey  1550 Jul 30 15:29 filedata.c
// -rw-rw-r--  1 asemsey  asemsey  3401 Jul 30 15:06 handle_args.c
// -rw-rw-r--  1 asemsey  asemsey  2258 Jul 30 14:46 test_helpers.c
// -rw-rw-r--  1 asemsey  asemsey  2108 Jul 30 16:23 mergesort.c
// -rw-rw-r--  1 asemsey  asemsey  3434 Jul 30 14:15 format.c
// -rw-rw-r--  1 asemsey  asemsey  2124 Jul 30 16:25 main.c

//  ./ft_ls -la src
// DEBUG called merge_sort len=10 lst=..
// DEBUG set f2=directories.c
// DEBUG set f2=file_info.c
// DEBUG set f2=filedata.c
// DEBUG set f2=handle_args.c
// DEBUG set f2=test_helpers.c
// DEBUG call f1
// DEBUG called merge_sort len=5 lst=..
// DEBUG set f2=directories.c
// DEBUG set f2=file_info.c
// DEBUG call f1
// DEBUG called merge_sort len=3 lst=..
// DEBUG set f2=directories.c
// DEBUG call f1
// DEBUG called merge_sort len=2 lst=..
// DEBUG set f2=directories.c
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=..
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=directories.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=directories.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=2 lst=file_info.c
// DEBUG set f2=filedata.c
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=file_info.c
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=filedata.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=5 lst=test_helpers.c
// DEBUG set f2=mergesort.c
// DEBUG set f2=format.c
// DEBUG call f1
// DEBUG called merge_sort len=3 lst=test_helpers.c
// DEBUG set f2=mergesort.c
// DEBUG call f1
// DEBUG called merge_sort len=2 lst=test_helpers.c
// DEBUG set f2=mergesort.c
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=test_helpers.c
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=mergesort.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=mergesort.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=2 lst=format.c
// DEBUG set f2=.
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=format.c
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=.
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// drwxrwxr-x  7 asemsey  asemsey  4096 Jul 30 16:33 ..
// -rw-rw-r--  1 asemsey  asemsey  6902 Jul 30 16:28 directories.c
// -rw-rw-r--  1 asemsey  asemsey  3471 Jul 30 15:36 file_info.c
// -rw-rw-r--  1 asemsey  asemsey  1550 Jul 30 15:29 filedata.c
// -rw-rw-r--  1 asemsey  asemsey  3401 Jul 30 15:06 handle_args.c
// -rw-rw-r--  1 asemsey  asemsey  2258 Jul 30 14:46 test_helpers.c
// -rw-rw-r--  1 asemsey  asemsey  2142 Jul 30 16:33 mergesort.c
// -rw-rw-r--  1 asemsey  asemsey  3434 Jul 30 14:15 format.c
// drwxrwxr-x  2 asemsey  asemsey  4096 Jul 30 12:23 .
// -rw-rw-r--  1 asemsey  asemsey  2121 Jul 30 16:25 main.c
