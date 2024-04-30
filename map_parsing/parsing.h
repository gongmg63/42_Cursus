#ifndef PARSING_H
#define PARSING_H

# include "../essential.h"

# define BUFFER_SIZE    5

typedef enum e_prefix_type
{
    NORTH,
    SOUTH,
    WEST,
    EAST,
    FLOOR,
    CEILING,
    MAP,
    NONE
}	t_prefix_type;

typedef struct s_texture
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     is_set[4]; // 0: north, 1: south, 2: west, 3: east가 설정되었는지 확인하는 플래그(중복 체크용)
}	t_texture;

typedef struct s_color
{
    int floor[3];
    int ceiling[3];
    int is_set[2];  // 0: floor, 1: ceiling가 설정되었는지 확인하는 플래그(중복 체크용)
}	t_color;

typedef struct s_map
{
    char    **arr;
    int     width;
    int     height;
    char    player_dir; // N, S, W, E 중 하나
    int     pos_x;
    int     pos_y;
    int     is_set; // map이 설정되었는지 확인 (중복 체크용)
    int     is_news_set;
}	t_map;

typedef struct t_map_info
{
    t_texture	*texture;
    t_color		*color;
    t_map		*map;
    int         fd;
}   t_map_info;

t_map_info      *parsing(char *cube_file);
t_map_info      *initialize_info(void);
int             validate_and_open_file(char *filename);
int             is_line_only_spaces(char *str);
char            *get_next_line(int fd);
t_prefix_type   get_prefix_type(char *line);
void            free_every_info(t_map_info *info);
int             set_texture(t_map_info *info, char *line, t_prefix_type prefix);
int             set_color(t_map_info *info, char *line, t_prefix_type type);
void            free_rgb(char **rgb);
int             set_map(t_map_info *info, char **line);
int             is_map_composed_of_valid_characters(t_list *map_lst);
int             is_map_surrounded_by_walls(t_list *map_lst, t_map_info *info);
char            **convert_map_lst_to_arr(t_list *map_lst, t_map_info *info);
int             is_valid_space(t_map_info *info);
int             clean_up_map_lst(t_list **map_lst);
t_list          *initialize_map_lst(void);
int             is_every_wall_surrounded_by_1(t_map_info *info);
int             count_comma(char *str);
int             is_digit(char *str);
int             line_to_map_lst(t_map_info *info, t_list **map_lst, char **line);
int             is_all_texture_and_color_set(t_map_info *info);
int             is_valid_rgb(char **rgb);

#endif
