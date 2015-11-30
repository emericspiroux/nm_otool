#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/11 12:43:05 by espiroux          #+#    #+#              #
#    Updated: 2013/12/17 12:29:57 by espiroux         ###   ########.fr        #
#                                                                              #
#******************************************************************************#


export CC= gcc
export CFLAGS= -Werror -Wall -Wextra


NAME_NM=ft_nm
NAME_OT=ft_otool
LIBFT_DIR=libft/

INC_DIR=includes/
SRC_NM=src/nm/
SRC_OT=src/otools/
SRC_COM=src/common/

FT_C_COM = 	$(SRC_COM)list_off.c \
			$(SRC_COM)catch_size.c \
			$(SRC_COM)catch_name.c \
			$(SRC_COM)swap_uint32.c \
			$(SRC_COM)browse_cmd.c \
			$(SRC_COM)displayRes.c

FT_C_NM =	$(SRC_NM)main_nm.c \
			$(SRC_NM)browse_ar_nm.c \
			$(SRC_NM)doArchive.c \
			$(SRC_NM)doFat.c \
			$(SRC_NM)addElem.c \
			$(SRC_NM)getSection.c \
			$(SRC_NM)endNm.c \
			$(SRC_NM)typing.c \
			$(SRC_NM)doNm.c \
			$(FT_C_COM)

FT_C_OT =	$(SRC_OT)main_ot.c \
			$(SRC_OT)doOtool.c \
			$(SRC_OT)browse_ar_tool.c \
			$(SRC_OT)doArchiveTool.c \
			$(SRC_OT)doFatTool.c \
			$(FT_C_COM)



FT_O_NM = $(FT_C_NM:.c=.o)
FT_O_OT = $(FT_C_OT:.c=.o)

all: $(NAME_NM) $(NAME_OT)

$(NAME_NM): a nm

$(NAME_OT): a otools

nm:
	@echo CREATE $(NAME_NM)
	@gcc $(CFLAGS) -I $(INC_DIR) $(FT_C_NM) ./libft/libft.a -o $(NAME_NM) -g

otools:
	@echo CREATE $(NAME_OT)
	@gcc $(CFLAGS) -I $(INC_DIR) $(FT_C_OT) ./libft/libft.a -o $(NAME_OT) -g

a:
		@(cd $(LIBFT_DIR) && $(MAKE))

clean:
		@(cd $(LIBFT_DIR) && $(MAKE) $@)
		@/bin/rm -rf $(NAME_OT).dSYM
		@/bin/rm -rf $(NAME_NM).dSYM


fclean: clean
		@/bin/rm $(NAME_OT)
		@/bin/rm $(NAME_NM)

re: fclean all
