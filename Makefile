EXEC_DIR	= exec/
EXEC_SRC	= binary.c exec.c exec_utils.c pipes.c signals.c
EXEC_SRC	:= $(addprefix ${EXEC_DIR}, ${EXEC_SRC})

BUILT_DIR	= buildins/
BUILT_SRC	= build_utils.c builtins.c cd.c echo.c env.c exit.c export.c export_add.c export_utils.c
BUILT_SRC	:= $(addprefix ${BUILT_DIR}, ${BUILT_SRC})

PARSER_DIR	= parser/
PARSER_SRC	= lst_utils.c make_comm_list.c make_comm_lst_utils.c make_redirect.c parse_dollar.c \
 			parse_quote.c parse_utils.c parse_utils_2.c parser.c
PARSER_SRC	:= $(addprefix ${PARSER_DIR}, ${PARSER_SRC})

AST_DIR		= ${PARSER_DIR}ast/
AST_SRC		= ast_utils.c create_ast.c
AST_SRC		:= $(addprefix ${AST_DIR}, ${AST_SRC})

SRCS		= ${EXEC_SRC} ${BUILT_SRC} ${PARSER_SRC} ${AST_SRC} er_exit.c main.c

USR			=   ${USER}
OBJS		=	$(SRCS:.c=.o)
NAME		=	minishell
LIBFT_DIR	=	libft/
LIBFT		=	libft.a
INCLUDES	=	-I$(LIBFT_DIR) -I$(BUILT_DIR) -I$(PARSER_DIR) -I$(AST_DIR)
HEADERS		=	${INCLUDES}
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g3  #-o2
%.o			:	%.c $(HEADERS)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)
all			:	$(NAME)

$(NAME)		:	$(LIBFT_DIR)$(LIBFT) $(OBJS)
				$(CC) $(OBJS) $(INCLUDES) -L$(LIBFT_DIR) -L/Users/${USER}/.brew/opt/readline/lib -lft -lreadline -ltermcap -o $(NAME)

$(LIBFT_DIR)$(LIBFT):	$(LIBFT_DIR)
						$(MAKE) -j4 -C  $(LIBFT_DIR) all
						$(MAKE) -j4 -C  $(LIBFT_DIR) bonus
bonus		:	$(NAME)

clean		:
				$(RM) $(OBJS)
				$(MAKE) -C $(LIBFT_DIR) clean

fclean		:	clean
				$(RM) $(NAME) 
				$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re