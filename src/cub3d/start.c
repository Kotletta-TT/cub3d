#include "render.h"

/*
gcc -O3 -Wall -Wextra -Werror start.c init.c utils.c cast.c draw.c events.c -Ilibft -lft -Llibft -Imlx -lmlx -Lmlx -framework OpenGL -framework AppKit -o cub3d && ./cub3d
*/

void start(t_map *map)
{
	// char	*map[] = {
	// 	"000000001111111111111111111111111",
	// 	"000000001N00000000110000000000001",
	// 	"000000001011000001110000000000001",
	// 	"000000001001000000000000000000001",
	// 	"111111111011000001110000000000001",
	// 	"100000000011000001110111111111111",
	// 	"111101111111110111000000100010000",
	// 	"111101111111110111010100100010000",
	// 	"110000001101010111000000100010000",
	// 	"100000000000000011000000100010000",
	// 	"100000000000000011010100100010000",
	// 	"110000011101010111110111100011100",
	// 	"11110111 1110101 1011110100010000",
	// 	"11111111 1111111 1111111111110000",
	// 	0
	// };
	t_cub	cub;

	// printf("floor: %i, ceiling: %i\n", map->resources.floor, map->resources.ceiling);
	init_cub(&cub, map);
	cast_rays(&cub);
	draw(&cub);
	mlx_hook(cub.window, 02, (1L<<0), key_pressed, &cub);
	mlx_hook(cub.window, 03, (1L<<1), key_released, &cub);
	mlx_hook(cub.window, 17, (1L<<17), destroy, &cub);
	mlx_loop_hook(cub.mlx, loop_hook, &cub);
	// mlx_mouse_hide(); //TODO: uncomment!
	mlx_loop(cub.mlx);
}
