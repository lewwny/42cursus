/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:24:23 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/18 18:57:06 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <pthread.h>
# include <errno.h>
# include <ifaddrs.h>
# include <signal.h>

# define WIDTH 1280
# define HEIGHT 720

# define TEX_HEIGHT 64
# define TEX_WIDTH 64

# define MAX_DIST 17.5

# define COL_BUF 0.1

# define WALL_HEIGHT_THRESHOLD 0.95
# define DISTANCE_LOD_THRESHOLD 25.0
# define PIXEL_SKIP_THRESHOLD 0.5

# define NO_SO 0
# define WE_EA 1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define FLOOR 4
# define CEILING 5

# define PLAYER_HITBOX_WIDTH 0.05
# define PLAYER_HITBOX_HEIGHT 0.05
# define DEBUG_HITBOX 1

# define ROT_SPEED 0.001
# define PORT 8080
# define BUFFER_SIZE 20000
# define SPRITE_MIN_DIST 0.2
# define SPRITE_MAX_DIST 20.0
# define SPRITE_MIN_RADIUS 2
# define SPRITE_MAX_RADIUS 12
# define SPRITE_BASE_RADIUS 15.0
# define SPRITE_RADIUS_SCALE 3.0

# define MINIMAP_SIZE 200
# define MINIMAP_CELL_SIZE 28
# define MINIMAP_RADIUS 3

# ifdef __APPLE__

#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define LINUX 0
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_SHIFT 257
#  include "../mlx_mac/mlx.h"

# elif __linux__

#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define LINUX 1
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_SHIFT 65505
#  include "../mlx_linux/mlx.h"

# endif

typedef struct s_server
{
	int					server_fd;
	int					client_fd;
	struct sockaddr_in	server_addr;
	struct sockaddr_in	client_addr;
	socklen_t			addr_len;
	pthread_mutex_t		mutex;
}	t_server;

typedef enum e_anim_type
{
	ANIM_NONE,
	ANIM_MOVE,
	ANIM_TURN
}	t_anim_type;

typedef struct s_move_anim
{
	t_anim_type	type;
	double		start_x;
	double		start_y;
	double		end_x;
	double		end_y;
	int			frame;
	int			total_frames;
	double		(*ease_fn)(double);
}	t_move_anim;

typedef struct s_rot_anim
{
	t_anim_type	type;
	double		start_angle;
	double		end_angle;
	int			frame;
	int			total_frames;
	double		(*ease_fn)(double);
}	t_rot_anim;

typedef struct s_rotate
{
	int		rotate;
	double	frac_x;
	double	frac_y;
}	t_rotate;

typedef struct s_parse
{
	int		no;
	char	*no_path;
	int		so;
	char	*so_path;
	int		we;
	char	*we_path;
	int		ea;
	char	*ea_path;
	int		f;
	char	*f_color;
	int		c;
	char	*c_color;
}	t_parse;

typedef struct s_ceiling
{
	int	r;
	int	g;
	int	b;
}	t_ceiling;

typedef struct s_floor
{
	int		r;
	int		g;
	int		b;
	int		x;
	int		y;
	double	row_dist;
	double	step_x;
	double	step_y;
	double	floor_x;
	double	floor_y;
}	t_floor;

typedef struct s_color
{
	t_ceiling	ceiling;
	t_floor		floor;
}	t_color;

typedef struct s_wall
{
	int				height;
	int				start;
	int				end;
	int				side;
	int				color;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
	unsigned int	*data;
}	t_wall;

typedef struct s_ray
{
	double	camera_x;
	double	ray_x;
	double	ray_y;
	double	stepsize;
	double	step_size_x;
	double	step_size_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	distance;
	double	wall_x;
	int		mapx;
	int		mapy;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	bool	hit;
	t_wall	wall;
	t_floor	floor;
}	t_ray;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	fov;
	double	target_fov;
	double	move_speed;
	int		pitch;
	t_ray	ray;
}	t_player;

typedef struct s_tex_data
{
	int				width;
	int				height;
	int				endian;
	int				bpp;
	int				size_line;
	unsigned int	*data;
}	t_tex_data;

typedef struct s_texture
{
	void			*no;
	void			*so;
	void			*we;
	void			*ea;
	void			*floor;
	void			*ceiling;
	unsigned int	*no_data;
	unsigned int	*so_data;
	unsigned int	*we_data;
	unsigned int	*ea_data;
	unsigned int	*floor_data;
	unsigned int	*ceiling_data;
	t_tex_data		tex_ptr[6];
}	t_texture;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	int		up;
	int		down;
	int		esc;
	int		shift;
}	t_keys;

typedef struct s_menu
{
	void		*resume2;
	void		*quit2;
}	t_menu;

typedef struct s_other
{
	double		otherposx;
	double		otherposy;
	double		posx;
	double		posy;
	int			end;
	int			connected;
	int			lifebar_state;
	int			end2;
	bool		client_connected;
	pthread_t	join_reade;
	pthread_t	join_writee;
	pthread_t	server;
	pthread_t	read_thread;
}	t_other;

typedef struct s_minimap
{
	int		x;
	int		y;
	int		size;
	int		cell_size;
	int		radius;
}	t_minimap;

typedef struct s_sprite_draw
{
	int				screen_x;
	int				screen_y;
	int				size;
	double			sprite_distance;
}	t_sprite_draw;

typedef struct s_minimap_params
{
	int		start_map_x;
	int		end_map_x;
	int		map_y;
	int		minimap_row;
}	t_minimap_params;

typedef struct s_img
{
	void			*img_ptr;
	unsigned int	*data;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}	t_img;

typedef struct s_leny
{
	t_img			leny_idle;
	t_img			leny_shoot;
	t_img			leny_shot;
}	t_leny;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*menu;
	void		*menu2;
	void		*menu3;
	void		*wait;
	void		*buftmp;
	void		*pause_menu;
	void		*resume;
	void		*quit;
	void		*gun;
	void		*gun2;
	void		*lifebar[5];
	void		*crosshair1;
	void		*crosshair2;
	void		*respawn1;
	void		*respawn2;
	void		*quitdeath1;
	void		*quitdeath2;
	int			*buf_lifebar[5];
	int			*bufgun;
	int			*bufcrosshair1;
	int			*bufcrosshair2;
	int			*bufgun2;
	int			*buf;
	int			*bufrespawn1;
	int			*bufrespawn2;
	int			*bufquitdeath1;
	int			*bufquitdeath2;
	int			*wait_buf;
	int			width;
	int			height;
	int			menu_mode;
	int			line_len;
	int			bpp;
	int			endian;
	int			host;
	int			join;
	int			sock;
	int			shoot;
	int			crosshair;
	double		crosshair_timer;
	double		delta_time;
	double		shoot_timer;
	double		spawnx;
	double		spawny;
	char		**map;
	char		**tmp;
	char		**final_map;
	double		cam_angle;
	double		cam_target;
	double		z_buffer[WIDTH];
	int			current_wall_start;
	int			current_wall_end;
	double		cached_cos_values[WIDTH];
	double		cached_inv_values[HEIGHT];
	int			cache_initialized;

	t_move_anim	move_anim;
	t_rot_anim	rot_anim;
	t_gb		*garbage;
	t_parse		parse;
	t_player	player;
	t_texture	texture;
	t_color		color;
	t_rotate	rot;
	t_keys		keys;
	t_menu		menuimg;
	t_server	server;
	t_minimap	minimap;
	t_leny		leny;
}	t_game;

void			parsing(int argc, char **argv, t_game *game);
void			destroy_game(t_game *game);
void			load_img(t_game *game);
void			extract_map(char *filename, t_game *game);
void			init_parse(t_parse *parse);
void			destroy_game_failure(t_game *game, const char *message);
void			free_split(char **split);
void			parse_map(t_game *game, t_parse *parse);
void			map_to_finalmap(t_game *game, int i);
void			parse_finalmap(t_game *game);
void			free_oldmap(char **map, t_gb **garbage);
void			move_player(t_game *game, int keycode);
void			extract_texture(t_game *game);
void			convert_texture(t_game *game);
void			raycasting(t_game *game);
void			pause_menu(t_game *game);
void			update_pause_menu(t_game *game, int new_menu_mode);
void			quit_game(t_game *game);
void			mouse_show(t_game *game);
void			mouse_hide(t_game *game);
void			mouse_move(t_game *game, int x, int y);
int				can_move_axis(t_game *game, double x, double y, double buffer);
int				rotate_player_by_mouse(t_game *game, int delta_x, int delta_y);
double			get_delta_time(void);
void			sprint_off(t_game *game);
void			sprint_on(t_game *game);
void			fov_sprint(t_game *game);
void			handle_sprint(t_game *game);
void			init_server(t_game *game);
void			close_server(t_game *game);
void			*server_thread(void *game);
void			join_server(t_game *game, char **argv);
t_other			*_other(void);
void			join_thread(t_game *game);
bool			world_to_screen_simple(t_game *game, double world_x,
					double world_y, int *screen_x);
bool			is_in_fov(double relative_angle);
double			normalize_angle(double angle);
bool			is_position_valid(t_game *game, double x, double y);
void			*join_read(void *arg);
void			*read_thread_func(void *arg);
void			send_map(int client_fd, t_game *game);
void			cast_ray(t_game *game, double raydirx, double raydiry);
void			draw_gun(t_game *game, int start_x, int start_y, int shoot);
void			handle_shoot_animation(t_game *game);
void			draw_crosshair(t_game *game, int start_x, int start_y,
					int shoot);
void			draw_lifebar(t_game *game, int start_x, int start_y);
void			load_crosshair(t_game *game);
void			load_lifebar(t_game *game);
void			is_shot(t_game *game);
void			death_menu(t_game *game);
void			connect_to_server(t_game *game, char **argv);
void			load_death_menu(t_game *game);
void			draw_button(t_game *game, int start_x, int start_y, int *buf);
void			draw_buttons(t_game *game);
void			red_filter(t_game *game);
int				handle_death_pause_menu_mouse_move(int x, int y, t_game *game);
void			update_pause_menu(t_game *game, int new_menu_mode);
void			respawn_player(t_game *game);
int				can_move_to(t_game *game, double x, double y);
void			draw_waiting_screen(t_game *game);
void			handle_rotation(t_game *game);
void			rotate_right(t_game *game, double rotation_speed);
void			rotate_left(t_game *game, double rotation_speed);
void			handle_vertical_rotation(t_game *game);
void			extract_floor(t_game *game);
void			extract_ceiling(t_game *game);
void			init_minimap(t_game *game);
void			draw_minimap(t_game *game);
void			draw_minimap_cell(t_game *game, int map_x, int map_y,
					int color);
void			draw_minimap_player(t_game *game);
int				get_cell_color(t_game *game, int map_x, int map_y);
void			draw_minimap_cell_row(t_game *game, t_minimap_params *params);
void			update_lifbar_state(t_game *game);
int				read_from_server_socket(t_game *game, char *buffer);
void			handle_crosshair_animation(t_game *game);

//TEXTURE COLOR PARSING
void			no_parse(char *filename, t_parse *parse, t_game *game);
void			so_parse(char *filename, t_parse *parse, t_game *game);
void			we_parse(char *filename, t_parse *parse, t_game *game);
void			ea_parse(char *filename, t_parse *parse, t_game *game);
void			f_parse(char *color, t_parse *parse, t_game *game);
void			c_parse(char *color, t_parse *parse, t_game *game);
void			init_player(t_game *game);
void			free_linux(t_game *game);
void			wall_height(t_game *game);
void			draw_wall(t_game *game, int x);
void			draw_fc_row(t_game *game, int params[2], int range[2],
					double raydir[2]);
void			draw_fc_col(t_game *game, int x, double raydirx,
					double raydiry);
unsigned int	get_fc_c_p(t_game *game, int xy[2], int is_f, double raydir[2]);

//MLX HOOKS
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				game_loop(t_game *game);
int				on_mouse_move(int x, int y, t_game *game);
int				on_mouse_click(int button, int x, int y, t_game *game);
void			handle_movement(t_game *game);

//INIT FUNCTIONS
void			init_sides(t_game *game, double raydirx, double raydiry);
void			load_leny(t_game *game);
void			perform_dda(t_game *game);
void			set_sides(t_game *game);
void			color_sides(t_game *game, int x, int y);
void			set_texture(t_game *game, double raydirx, double raydiry);
void			draw_wall_textured(t_game *game, int x, int y);
void			calculate_y_tex(t_game *game);

unsigned int	get_fc_text_color(t_game *game, int is_floor);
unsigned int	apply_shading(unsigned int color, double dist);
void			draw_other_player_sprite(t_game *game);
void			draw_other_player_debug(t_game *game);
void			draw_other_player_simple(t_game *game);
void			draw_leny_at_other_position(t_game *game);
int				ray_hits_player(t_game *game, double target_x, double target_y);
int				is_pixel_visible(t_game *game, int screen_x,
					double sprite_distance);
void			draw_sprite_pixel(t_game *game, t_sprite_draw *draw,
					t_img *sprite);

#endif
