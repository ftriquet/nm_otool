#include <libft.h>
#include <nm_otool.h>

int		alpha_cmp(void *sym1, void *sym2, char *stringtable)
{
	return (ft_strcmp(stringtable + (((struct nlist *)sym1)->n_un.n_strx),
				stringtable + (((struct nlist *)sym2)->n_un.n_strx)));
}

int		no_cmp(void *sym1, void *sym2)
{
	(void)sym1;
	(void)sym2;
	return (1);
}
