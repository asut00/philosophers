# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asuteau <asuteau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 16:29:10 by asuteau           #+#    #+#              #
#    Updated: 2024/08/22 09:59:46 by asuteau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------------------------- VARIABLES --------------------------------- #

NAME		= 	philo

SRC			= 	philo.c\
				check_args.c \
				philo_utils.c \
				init.c \
				init_philos_array.c \
				precise_usleep.c \
				get_timestamps.c \
				clean_and_close.c \
				destroy.c \
				destroy2.c \
				death_check.c \
				getters.c \
				setters.c \
				print_message.c \
				is_monophil.c \
				routine.c \
				routine_utils.c \
				routine_eat.c \
				wait.c

VPATH		=	src src/check_args src/philo_utils src/init \
				src/time_handling src/clean_and_close src/death_check \
				src/getters_and_setters src/print_message \
				src/routine src/wait

INCL_DIR	=	inc/

OBJECTS		= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR		=	build

CC			= 	cc

CFLAGS		= 	-Wall -Wextra -Werror #-g


# ---------------------------------- RULES ----------------------------------- #

.c.o:	
				$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ_DIR) $(OBJECTS)
				$(CC) $(CFLAGS) -I $(INCL_DIR) -o $(NAME) $(OBJECTS)

$(OBJ_DIR):
				mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:		%.c
				$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $@

all: 			$(NAME)

clean:
				rm -f $(OBJECTS)
				rm -f -r $(OBJ_DIR)

fclean:		clean
				rm -f $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
