# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 11:10:39 by mschroed          #+#    #+#              #
#    Updated: 2018/12/12 12:16:18 by mschroed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C libft
	clang -o test_gnl -g main.c get_next_line.c -I libft/includes -L libft/ -lft

re: all
