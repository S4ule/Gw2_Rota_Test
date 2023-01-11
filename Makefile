
SRCS =		srcs/rota.c\
			srcs/utils.c\
			srcs/pars.c\
			srcs/main.c

SRCS_OLD = 	srcs/rota_save.c\
			srcs/utils.c\
			srcs/pars.c\
			srcs/main.c

OBJS =		${SRCS:.c=.o}

OBJS_OLD = ${SRCS_OLD:.c=.o}

INC=		-I include -L gnl -lget_next_line -L libft -lft

NAME =		rota

NAME_OLD = 	rota_old

LIB = 		libft/libft.a\
			gnl/libget_next_line.a

CC =		gcc

FLAGS =		-Wall -Wextra -Werror -g

all:		$(NAME)

old:		$(NAME_OLD)

$(NAME):	$(LIB) $(OBJS)
			$(CC) $(FLAGS) $(OBJS) $(INC) -o $(NAME)

$(NAME_OLD):	$(LIB) $(OBJS_OLD)
			$(CC) $(FLAGS) $(OBJS_OLD) $(INC) -o $(NAME_OLD)

.c.o:
			$(CC) $(FLAGS) $(INC) -c $< -o $@

$(LIB):
			make -C libft
			make -C gnl

clean:
			make clean -C libft
			make clean -C gnl
			rm -f $(OBJS) $(OBJS_OLD)

fclean:
			make clean
			make fclean -C libft
			make fclean -C gnl
			rm -f $(NAME) $(NAME_OLD)

re:
			make fclean
			make all

.PHONY:		re fclean clean all old
