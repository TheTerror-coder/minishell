# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/10 15:29:29 by TheTerror         #+#    #+#              #
#    Updated: 2023/08/11 12:13:12 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = 		libft.a
PRINTF_LIB = $(PRINTF_PATH)libftprintf.a

# FT_PRINTF PATHS

PRINTF_PATH = 		./ft_printf/

# LIBFT PATHS

CHAR_TOOLS_PATH = 	./char_tools/
GNL_PATH = 			./get_next_line/
LIST_TOOLS_PATH = 	./list_tools/
MEM_TOOLS_PATH = 	./mem_tools/
PRINT_TOOLS_PATH = 	./print_tools/
STR_TOOLS_PATH = 	./str_tools/
VARIOUS_PATH = 		./various/

INCLUDE = 	libft.h $(GNL_PATH)get_next_line.h $(GNL_PATH)lget_next_line.h \
			$(PRINTF_PATH)ft_printf.h \

CFLAGS = 	-Wall -Werror -Wextra
CC = 		cc
AR = 		ar -rc
RM =		rm -rf


# GET_NEXT_LINE'S SOURCES

SRC_GNL = 			$(addprefix $(GNL_PATH), get_next_line.c get_next_line_utils.c)

# LIBFT'S SOURCES

SRC_CHAR_TOOLS =	$(addprefix $(CHAR_TOOLS_PATH), ft_isalpha.c ft_isdigit.c ft_isalnum.c \
					ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c)
SRC_MEM_TOOLS =		$(addprefix $(MEM_TOOLS_PATH), ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
					ft_memchr.c ft_memcmp.c ft_calloc.c ft_free2str.c ft_freestr.c)
SRC_PRINT_TOOLS = 	$(addprefix $(PRINT_TOOLS_PATH), ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c)
SRC_STR_TOOLS =		$(addprefix $(STR_TOOLS_PATH), ft_strlen.c ft_strlcpy.c ft_strlcat.c  ft_strchr.c \
					ft_strrchr.c ft_strncmp.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
					ft_strnstr.c ft_striteri.c ft_strmapi.c ft_splitwset.c ft_2strlen.c)
SRC_VARIOUS =		$(addprefix $(VARIOUS_PATH), ft_atoi.c ft_itoa.c)
SRC_LIST_TOOLS =	$(addprefix $(LIST_TOOLS_PATH), ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c)
SRC =		 		$(SRC_CHAR_TOOLS) $(SRC_MEM_TOOLS) $(SRC_PRINT_TOOLS) $(SRC_STR_TOOLS) $(SRC_VARIOUS) \
					$(SRC_LIST_TOOLS) $(SRC_GNL)


# LIBFT'S & GET_NEXT_LINE'S OBJECTS

OBJ		 	= 	$(SRC:.c=.o)


all : make_printf $(NAME)

$(OBJ) : %.o : %.c $(INCLUDE)
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME) : $(OBJ) $(INCLUDE) $(PRINTF_LIB)
	cp $(PRINTF_LIB) ./$(NAME)
	$(AR) $@ $(OBJ)
	@ranlib $(NAME)

make_printf :
	make -C $(PRINTF_PATH)

clean :
	@make clean -C $(PRINTF_PATH)
	@$(RM) $(OBJ) $(PRINTF_OBJ)
fclean : clean
	@make fclean -C $(PRINTF_PATH)
	@$(RM) $(NAME) $(PRINTF_LIB)
re : fclean all