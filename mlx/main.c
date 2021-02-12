#include "mlx.h"

int main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "Hello World!");
	mlx_loop(mlx);
	return (0);
}
