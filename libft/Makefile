# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/10 15:29:29 by TheTerror         #+#    #+#              #
#    Updated: 2023/05/12 02:22:36 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = 		libft.a
PRINTF_LIB = $(PRINTF_PATH)libftprintf.a

# FT_PRINTF PATHS

PRINTF_PATH = 		./ft_printf/
PRINTF_SRCS_PATH = 	$(PRINTF_PATH)srcs/
PRINTF_UTILS_PATH = $(PRINTF_PATH)utils/
PRINTF_BONUS_PATH = $(PRINTF_PATH)bonus/

# LIBFT PATHS

CHAR_TOOLS_PATH = 	./char_tools/
GNL_PATH = 			./get_next_line/
LIST_TOOLS_PATH = 	./list_tools/
MEM_TOOLS_PATH = 	./mem_tools/
PRINT_TOOLS_PATH = 	./print_tools/
STR_TOOLS_PATH = 	./str_tools/
VARIOUS_PATH = 		./various/

INCLUDE = 	libft.h $(GNL_PATH)get_next_line.h $(GNL_PATH)lget_next_line.h \
			$(PRINTF_PATH)ft_printf.h $(PRINTF_PATH)ft_lprintf.h \
			$(PRINTF_PATH)ft_preprcss.h $(PRINTF_SRCS_PATH)ft_srcs.h \
			$(PRINTF_UTILS_PATH)ft_utils.h $(PRINTF_BONUS_PATH)ft_bonus.h

CFLAGS = 	-Wall -Werror -Wextra
CC = 		cc
AR = 		ar -rc
RM =		rm -rf

# FT_PRINTF'S SOURCES

PRINTF_SRC =		$(PRINTF_PATH)ft_printf.c \
					$(addprefix $(PRINTF_SRCS_PATH), ft_hexa_base.c ft_islowcase.c \
					ft_print_char.c ft_isupcase.c ft_print_adr.c ft_print_hex.c \
					ft_print_int.c ft_print_unsign.c ft_print_str.c) \
					$(addprefix $(PRINTF_UTILS_PATH), ft_utils1.c ft_utils2.c ft_utils3.c) \
					$(addprefix $(PRINTF_BONUS_PATH), ft_put_spaces.c ft_put_zeros.c ft_sw_optionals.c)

# GET_NEXT_LINE'S SOURCES

SRC_GNL = 			$(addprefix $(GNL_PATH), get_next_line.c get_next_line_utils.c)

# LIBFT'S SOURCES

SRC_CHAR_TOOLS =	$(addprefix $(CHAR_TOOLS_PATH), ft_isalpha.c ft_isdigit.c ft_isalnum.c \
					ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c)
SRC_MEM_TOOLS =		$(addprefix $(MEM_TOOLS_PATH), ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
					ft_memchr.c ft_memcmp.c ft_calloc.c ft_freesplit.c)
SRC_PRINT_TOOLS = 	$(addprefix $(PRINT_TOOLS_PATH), ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c)
SRC_STR_TOOLS =		$(addprefix $(STR_TOOLS_PATH), ft_strlen.c ft_strlcpy.c ft_strlcat.c  ft_strchr.c \
					ft_strrchr.c ft_strncmp.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
					ft_strnstr.c ft_striteri.c ft_strmapi.c)
SRC_VARIOUS =		$(addprefix $(VARIOUS_PATH), ft_atoi.c ft_itoa.c)
SRC_LIST_TOOLS =	$(addprefix $(LIST_TOOLS_PATH), ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c)
SRC =		 		$(SRC_CHAR_TOOLS) $(SRC_MEM_TOOLS) $(SRC_PRINT_TOOLS) $(SRC_STR_TOOLS) $(SRC_VARIOUS) \
					$(SRC_LIST_TOOLS) $(SRC_GNL)


# LIBFT'S & GET_NEXT_LINE'S OBJECTS

OBJ		 	= 	$(SRC:.c=.o)

# LIBFT'S OBJECTS

PRINTF_OBJ 	= 	$(PRINTF_SRC:.c=.o)


all : $(NAME) $(PRINTF_LIB)

$(PRINTF_OBJ) : %.o : %.c $(INCLUDE) $(OBJ)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ) : %.o : %.c $(INCLUDE)
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME) : $(OBJ) $(INCLUDE)
	$(AR) $@ $^
	@ranlib $(NAME)

$(PRINTF_LIB) : $(PRINTF_OBJ) $(INCLUDE)
	@$(AR) $@ $^
	@$(AR) $(NAME) $@
	@ranlib $(NAME)

clean :
	@$(RM) $(OBJ) $(PRINTF_OBJ)
fclean : clean
	@$(RM) $(NAME) $(PRINTF_LIB)
re : fclean all