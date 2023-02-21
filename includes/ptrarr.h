#ifndef PTRARR_H
# define PTRARR_H

# define PTRARR_INITIAL_CAP 1

typedef struct s_ptrarr
{
	int		len;
	int		cap;
	void	**data;
}	t_ptrarr;

t_ptrarr	*ptrarr_create(void);
t_ptrarr	*ptrarr_destroy(t_ptrarr *ptrarr);
int			ptrarr_expand(t_ptrarr *ptrarr);
int			ptrarr_append(t_ptrarr *ptrarr, void *data);

#endif