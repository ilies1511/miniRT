#include <main.h>

void	main_cleanup(t_main *m_data, uint8_t exit_stat)
{
	mlx_delete_image(m_data->mlx, m_data->img);
	mlx_close_window(m_data->mlx);
	exit(exit_stat);
}

void	ft_error(t_main *m_data, char *msg, char *file, int line, uint8_t exit_stat)
{
	ft_fprintf(2, "error in %s in line %d: %s\n", file, line, msg);
	main_cleanup(m_data, exit_stat);
}

