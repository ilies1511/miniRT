#include <ft_matrix.h>
#include <libft.h>
#include <ft_floats.h>

void	mtx_print(t_fd fd, t_matrix m)
{
	int	row;
	int	col;

	ft_fprintf(fd, "%dx%dMatrix:\n", (int)m.type, (int)m.type);
	row = 0;
	while (row < (int)m.type)
	{
		col = 0;
		ft_fprintf(fd, "|");
		while (col < (int)m.type)
		{
			ft_fprintf(fd, "%f|", m.m[row][col]);
			col++;
		}
		ft_fprintf(fd, "\n");
		row++;
	}
}

bool	mtx_eq(t_matrix ma, t_matrix mb)
{
	uint8_t	row;
	uint8_t	col;


	if (ma.type != mb.type)
		return (false);
	row = 0;
	while (row < ma.type)
	{
		col = 0;
		while (col < ma.type)
		{
			if (!eq_f(ma.m[row][col], mb.m[row][col]))
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}