# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gricquie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/21 20:51:53 by gricquie          #+#    #+#              #
#    Updated: 2017/02/05 01:11:32 by gricquie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c flags1.c flags2.c flags3.c mod_init.c print.c ft_atoi.c\
		ft_wcswrite.c ft_isdigit.c ft_isalpha.c ft_isupper.c ft_putchar.c\
		ft_putnbrl.c ft_putnbr.c ft_putstr.c ft_strchr.c ft_isspace.c\
		ft_strlen.c ft_wcslen.c ft_tolower.c ft_isupper.c ft_max.c\
		double.c flag_g.c flags_bonus.c ft_strnequ.c type.c ft_power.c

OBJS = $(SRCS:.c=.o)

HEADER = ft_printf.h libft.h

FLAGS = -Werror -Wextra -Wall

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	@ar -rc $(NAME) $(OBJS) 
	@ranlib $(NAME)

%.o : %.c
	@gcc -o $@ -c $< $(FLAGS)

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
