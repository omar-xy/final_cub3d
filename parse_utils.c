/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:03:19 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 14:35:41 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "incs/cub3d.h"

int set_color(t_cub *cub, char **str, char flag)
{
    if (flag == 'F' || flag == 'C')
    {
        if ((ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255)\
            || (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)\
            || (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255))
            return (0);
        if (flag == 'F')
        {
            cub->map.floor.floor = "F";
            cub->map.floor.r = ft_atoi(str[0]);
            cub->map.floor.g = ft_atoi(str[1]);
            cub->map.floor.b = ft_atoi(str[2]);
        }
        else
        {
            cub->map.ceiling.ceiling = "C";
            cub->map.ceiling.r = ft_atoi(str[0]);
            cub->map.ceiling.g = ft_atoi(str[1]);
            cub->map.ceiling.b = ft_atoi(str[2]);
        }
    }
    return 1;
}


static int count_comas(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(line[i])
    {
        if (line[i] == ',')
            count++;
        i++;
    }
    if (count != 2)
        return (0);
    return (1);
}

int count_towd_arr(char **str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

void free_towd(char **str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}


int  parse_color(t_cub *cub, char *line, char flag)
{
    int i;
    int j;
    char **str;

    i = 0;
    if (!line)
        return (ft_error(cub, "Error: Wrong color0\n"));
    if (!count_comas(line))
        return (ft_error(cub, "Error: Wrong color1\n"));
    str = ft_split(line, ',');
    i = count_towd_arr(str);
    if (i != 3)
        return (free_towd(str), ft_error(cub, "Error: Wrong color2\n"));
    i = 0;
    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (free_towd(str), ft_error(cub, "Error: Wrong color3\n"));
            j++;
        }
        i++;
    }
    if (!set_color(cub, str, flag))
        return (free_towd(str), ft_error(cub, "Error: Wrong color4\n"));
    return (free_towd(str), 1);
}

int store_textures(t_cub *cub, char *line)
{
    char *str;
    char *trimed_str;
    int bool_color = 0;

    trimed_str = NULL;
    str = ft_strtrim(line, "\n");
    if (!str)
        return (0);
    if (!ft_strncmp(str, "NO ", 3))
        cub->map.no_path = ft_strtrim(&str[2], " ");
    else if (!ft_strncmp(str, "SO ", 3))
        cub->map.so_path = ft_strtrim(&str[2], " ");
    else if (!ft_strncmp(str, "WE ", 3))
        cub->map.we_path = ft_strtrim(&str[2], " ");
    else if (!ft_strncmp(str, "EA ", 3))
        cub->map.ea_path = ft_strtrim(&str[2], " ");
    else if (!ft_strncmp(str, "F ", 2))
    {
        trimed_str = ft_strtrim(&str[2], " ");
        bool_color = parse_color(cub, trimed_str, 'F');
        if (bool_color == 0)
            return (free(str), free(trimed_str), 0);
    }
    else if (!ft_strncmp(str, "C ", 2))
    {
        trimed_str = ft_strtrim(&str[2], " ");
        bool_color = parse_color(cub, trimed_str, 'C');
        if (bool_color == 0)
            return (free(str), free(trimed_str), 0);
    }
    else
        return (free(str), ft_error(cub, "Error: in map\n"));
    return (free(trimed_str), free(str), 1);
}


bool detect_map(char *line)
{
    int i = -1;
    while (line[++i] == ' ' || line[i] == '\t')
        ;
    if (line[i] == '1')
        return (true);
    return (false);
}

void    calculate_map_size(t_cub *cub)
{
    int i;
	int j;
    int max_width;

    i = 0;
	max_width = 0;
    while (cub->map.store_map[i])
        i++;
    cub->map.height = i;
    i = 0;
    while(cub->map.store_map[i])
    {
        j = 0;
        while(cub->map.store_map[i][j])
            j++;
        if (j > max_width)
            max_width = j;
        i++;
    }
    cub->map.width = max_width;
}

void fill_empty_spaces(t_cub *cub)
{
    int i;
    int j;
    char **map;

    map = cub->map.store_map;
    i = -1;
    while(map[++i])
    {
        j = ft_strlen(map[i]);
        while(j < cub->map.width)
        {
            cub->map.store_map[i] = ft_strjoin_free(map[i], " ");
            j++;
        }
    }
}



int check_textures(t_cub *cub)
{
    if (!cub->map.no_path || !cub->map.so_path || !cub->map.we_path || !cub->map.ea_path
        || !cub->map.floor.floor || !cub->map.ceiling.ceiling)
        return (0);
    if (open(cub->map.no_path, O_RDONLY) < 0 || open(cub->map.so_path, O_RDONLY) < 0 
        || open(cub->map.we_path, O_RDONLY) < 0 || open(cub->map.ea_path, O_RDONLY) < 0)
        return (0);
    return (1);
}


// void free_towd(char **str)
// {
//     int i;

//     i = 0;
//     while(str[i])
//     {
//         free(str[i]);
//         i++;
//     }
//     free(str);
// }

int check_map(t_cub *cub)
{
    // char **map;
    int i = -1;
    int j;

    cub->player.dir = '\0';
    // map = cub->map.store_map;
    while(cub->map.store_map[++i])
    {
        j = -1;
        while(cub->map.store_map[i][++j])
        {
            if (!(cub->map.store_map[i][j] == 'N' || cub->map.store_map[i][j] == 'S' || cub->map.store_map[i][j] == 'W' || cub->map.store_map[i][j] == 'E'
                    || cub->map.store_map[i][j] == '0' || cub->map.store_map[i][j] == '1' || cub->map.store_map[i][j] == ' '))
                return (0);
            if (i == 0 || i == cub->map.height - 1 || j == 0 || j == cub->map.width - 1)
            {
                if (cub->map.store_map[i][j] != '1' && cub->map.store_map[i][j] != ' ')
                    return (0);
            }
            else if (i > 0 && j > 0 && (i < cub->map.height - 1) && (j < cub->map.width - 1) 
                && (cub->map.store_map[i][j] == '0' || cub->map.store_map[i][j] == 'N' || cub->map.store_map[i][j] == 'S' || cub->map.store_map[i][j] == 'W' || cub->map.store_map[i][j] == 'E'))
            {
                if (cub->map.store_map[i][j + 1] == ' ' || cub->map.store_map[i][j - 1] == ' ' || cub->map.store_map[i + 1][j] == ' ' || cub->map.store_map[i - 1][j] == ' ')
                    return (0);
            }
            if (cub->map.store_map[i][j] == 'N' || cub->map.store_map[i][j] == 'S' || cub->map.store_map[i][j] == 'W' || cub->map.store_map[i][j] == 'E')
            {
                cub->player.x = j * 64 + (64 / 2);
                cub->player.y = i * 64 + (64 / 2);
                cub->player.dir = cub->map.store_map[i][j];
                cub->map.store_map[i][j] = '0';
            }
        }
    }
    if (cub->player.dir == '\0')
        return (0);
	return (1);
}

int ft_store_data(t_cub *cub, int count, char *hold_file)
{
    char    *tmp_line;

    tmp_line = NULL;
    if (count != 6)
        return (ft_error(NULL, "Error: Wrong number of textures, 1\n"));
    tmp_line = ft_strtrim(hold_file, "\n");
    // if (ft_strnstr(tmp_line, "\n\n", ft_strlen(tmp_line)))
    //     return (ft_error(cub, "Error: Wrong map oupss, 2\n"));
    cub->map.store_map = ft_split(tmp_line, '\n');
    calculate_map_size(cub);
    fill_empty_spaces(cub);
    free(tmp_line);
    return (1);
}

int ft_parse_map(t_cub *cub, int fd)
{
    char *line;
    char *hold_file;
    int flg;
    int count;

    flg = 0;
    count = 0;
    hold_file = ft_strdup("");
    while(true)
    {
        line =  get_next_line(fd);
        if (!line)
            break;
        if ((detect_map(line) || line[0] == '\n'))
        {
            if (detect_map(line))
                flg = 1;
            hold_file = ft_strjoin_free(hold_file, line);
        }
        if (line[0] != '\n' && !detect_map(line))
        {
            if (flg == 1)
                return (ft_error(cub, "Error: Wrong map, 0\n"));
            if (!store_textures(cub, line))
                return (free(hold_file), free(line), ft_error(cub, "Error: Wrong texture !1\n"));
            count++;
        }
        free(line);
    }
    free(line);
    if (!ft_store_data(cub, count, hold_file))
        return (free(hold_file), ft_error(cub, "Error: Wrong map, 1\n"));
    free(hold_file);
    hold_file = NULL;
    return (1);
}
