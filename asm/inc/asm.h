/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:10:01 by tvisenti          #+#    #+#             */
/*   Updated: 2016/08/29 09:25:00 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "../../libft/ft_printf/include/fpf_printf.h"
# include "../../libft/libft.h"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define T_REG					1
# define T_DIR					2
# define T_IND					2

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define REG_NUMBER				16

int						g_line;
int						g_pos;
int						g_temp;

/*
** Labels
*/

typedef struct			s_label
{
	char				*name;
	unsigned int		pos;
	struct s_label		*next;

}						t_label;

/*
** Header
*/

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

/*
** Library
*/

int						asm_error(int error);
int						asm_error_sec(int error);

t_header				*asm_header_init(void);
t_label					*asm_label_init(t_label *label, char *line);

int						asm_ret_header(t_header *head, char *line);
int						asm_free_label(t_label *label);
int						asm_free_tab(char **tab, int ret);
char					*asm_free_join(char *line, char *file);
char					*asm_realloc(char *line, char *file, int i);

/*
**	Main
*/

void					asm_init_global(void);
int						asm_argc_check(int argc);

/*
** Parse_instruct
*/

int						asm_instruct_name_sec(char *line);
int						asm_instruct_name(char *line);
int						asm_move_my_i(int i, char *file);
int						asm_calculate_i(char *file, t_label *label);

/*
** Check_arg
*/

int						asm_check_arg(char **line, int op);
int						asm_check_arg_sec(char **line, int op);

/*
** Parsing
*/

int						asm_check_champ(char *champ);
char					*asm_put_line_in_file(char *line, int i, char *file);
t_label					*asm_parse_line(int fd, char **file);
void					asm_bonus_champ(t_header *head);
int						asm_parsing(char *champion, t_header *head, int check);

/*
** Copy header
*/

int						asm_header_pass(char *line, int name, int com,
						int check);
int						asm_header_pass_end(char *line, int i);
t_header				*asm_copy_header(char *line, t_header *head, int check);
int						asm_copy_name_comment(char *line, t_header *head,
						int name, int com);
int						asm_handler_name_comment(int fd, t_header *head);

/*
** Check_instruct
*/

int						asm_check_virgule(char **line);
int						asm_check_dir(char **line, int op, int check);
int						asm_check_reg(char **line, int check);
int						asm_check_ind(char **line, int check);
int						check_valid_line(char *line);

/*
** Writer
*/

int						cw_invert_endian2(int x);
int						cw_invert_endian(int x);
int						asm_header_creator(int fd, t_header *header);
char					*asm_morph_cor(char *champ);
int						asm_reader(t_label *label, t_header *header,
						char *champ, char *file);

/*
** Binary_writer
*/

int						asm_move_g_file(int fct);
int						asm_move_separator(char **file);
int						asm_call_good_function(int fct, int fd, t_label *label,
						char **file);
int						asm_binary_creator(int fd, t_label *label, char *file);

/*
** Check_label
*/

int						asm_match_label(t_label *label, char *str);
int						asm_check_label_exist(t_label *label, char *str);
int						asm_check_label(char *str);
int						asm_check_double_label(t_label *label);

/*
** Write_Octal
*/

int						asm_opcode(int fd, int arg, int i, char *file);
int						asm_write_dir(int fd, int size, t_label *label,
						char **file);
int						asm_write_ind(int fd, t_label *label, char **file);
int						asm_write_reg(int fd, char **file);

#endif
