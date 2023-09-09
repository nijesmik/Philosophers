CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo
BONUS_NAME = philo_bonus

INCLUDES = ./includes/
HEADER = $(INCLUDES)philosophers.h

SRCS_DIR = ./srcs/
SRCS = \
	$(SRCS_DIR)main.c			\
	$(SRCS_DIR)init.c			\
	$(SRCS_DIR)util.c			\
	$(SRCS_DIR)error.c			\
	$(SRCS_DIR)check.c			\
	$(SRCS_DIR)simulation.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS_DIR = ./srcs/bonus/
BONUS_SRCS = \

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDES) $^ -o $(NAME)

# bonus : $(BONUS_NAME)

$(BONUS_NAME) : $(BONUS_OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDES) $^ -o $(BONUS_NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : 
	make clean
	rm -f $(NAME) $(BONUS_NAME)

re :
	make fclean 
	make all

.PHONY : all clean fclean re # bonus