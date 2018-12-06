#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmatvien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/06 20:11:35 by lmatvien          #+#    #+#              #
#    Updated: 2018/09/29 16:05:42 by lmatvien         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
HEADER =	\n █░░ █▀▄▀█ █▀▀█ ▀▀█▀▀ ▀█░█▀ ░▀░ █▀▀ █▀▀▄ \n \
			█░░ █░▀░█ █▄▄█ ░░█░░ ░█▄█░ ▀█▀ █▀▀ █░░█ \n \
			▀▀▀ ▀░░░▀ ▀░░▀ ░░▀░░ ░░▀░░ ▀▀▀ ▀▀▀ ▀░░▀ \

#COLORSs
VIOLET      = \033[01;38;05;201m
RESET		= \033[m
RED         = \033[1;31m
CYAN        = \033[1;36m

NAME			= ft_ssl
LIB_MINI_NAME 	= lib_mini.a
PARSER_LIB	= 	parserlib.a
ODIR 			= obj
SDIR 			= src
LDIR 			= ./src/libft_mini
FT_PRINTF		= ./src/ft_printf/libftprintf.a

FLAGS  			= -Wall -Wextra -Werror

PARSER_FILES	= ssl_hash_mod.c \
				ssl_main.c \
				ssl_reader_stdin.c \
				ssl_handle.c \
				ssl_flags_mod.c \
				ssl_file_reader.c \
				ssl_flag_effect.c \
				

LIBFILE =   ft_atoi_base.c \
			ft_itoa.c \
			ft_strnew.c \
			ft_pow.c \
			ft_strchr.c \
			ft_dgt_quntt_i.c \
			ft_isdigit.c  \
			ft_strrchr.c \
			ft_putnbr_fd.c \
			ft_putstr_error.c \
			ft_str_del_newline.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcmp.c \
			ft_strequ.c \
			ft_strlen.c \
			ft_strnlen.c \
	 		ft_strdup.c \
			ft_strjoin.c \
			ft_strstr.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_strncat.c \
			ft_strcat.c \
			get_next_line.c \
			ft_strsplit.c \
			ft_atoi.c \
			ft_swap.c \
			ft_to_uppercase.c \
			ft_to_lowercase.c \

MD5_LIB = ssl_md5.a
MD5 = ./src/md5
MD5_FILES =	ft_ssl_md5_print.c \
			h_md5.c \
			h_md5_transforrm.c \

SHA256_LIB = ssl_sha256.a
SHA256 = ./src/sha256
SHA256_FILES =	ft_ssl_sha256.c \
				ft_ssl_sha256_tools.c \
				ft_ssl_sha256_tranforrm.c \
				ft_ssl_sha256_mode.c \

SHA224_LIB = ssl_sha224.a
SHA224 = ./src/sha224
SHA224_FILES =	ft_ssl_sha224.c \
				ft_ssl_sha224_tools.c \
				ft_ssl_sha224_tranforrm.c \
				ft_ssl_sha224_mode.c \

SHA512_LIB = ssl_sha512.a
SHA512 = ./src/sha512
SHA512_FILES =	ft_ssl_sha512.c \
				ft_ssl_sha512_tools.c \
				ft_ssl_sha512_tranforrm.c \
				ft_ssl_sha512_mode.c \

SHA384_LIB = ssl_sha384.a
SHA384 = ./src/sha384
SHA384_FILES =	ft_ssl_sha384.c \
				ft_ssl_sha384_tools.c \
				ft_ssl_sha384_tranforrm.c \
				ft_ssl_sha384_mode.c \

LIB_OBJ =	$(addprefix $(ODIR)/, $(patsubst %.c,%.o,$(LIBFILE)))
PARSER_OBJ = $(addprefix $(ODIR)/, $(patsubst %.c,%.o,$(PARSER_FILES)))
MD5_OBJ = $(addprefix $(ODIR)/, $(patsubst %.c,%.o,$(MD5_FILES)))
SHA256_OBJ = $(addprefix $(ODIR)/, $(patsubst %.c,%.o,$(SHA256_FILES)))
SHA224_OBJ = $(addprefix $(ODIR)/, $(patsubst %.c,%.o,$(SHA224_FILES)))
SHA512_OBJ = $(addprefix $(ODIR)/, $(patsubst %.c,%.o,$(SHA512_FILES)))
SHA384_OBJ = $(addprefix $(ODIR)/, $(patsubst %.c,%.o,$(SHA384_FILES)))

INC_PARSER = -I ./include -I $(LDIR) -I src/ft_printf/includes/

all: $(NAME)

$(ODIR)/%.o: $(LDIR)/%.c | $(ODIR)
	@gcc -c $< -o $@
	@echo "$(VIOLET)█$(RESET)\c)"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@gcc -c $(INC_PARSER) $< -o $@
	@echo "$(VIOLET)█$(RESET)\c)"

$(ODIR)/%.o: $(MD5)/%.c | $(ODIR)
	@gcc -c $(INC_PARSER) $< -o $@
	@echo "$(VIOLET)█$(RESET)\c)"

$(ODIR)/%.o: $(SHA256)/%.c | $(ODIR)
	@gcc -c $(INC_PARSER) $< -o $@
	@echo "$(VIOLET)█$(RESET)\c)"

$(ODIR)/%.o: $(SHA224)/%.c | $(ODIR)
	@gcc -c $(INC_PARSER) $< -o $@
	@echo "$(VIOLET)█$(RESET)\c)"

$(ODIR)/%.o: $(SHA512)/%.c | $(ODIR)
	@gcc -c $(INC_PARSER) $< -o $@
	@echo "$(VIOLET)█$(RESET)\c)"

$(ODIR)/%.o: $(SHA384)/%.c | $(ODIR)
	@gcc -c $(INC_PARSER) $< -o $@
	@echo "$(VIOLET)█$(RESET)\c)"

$(ODIR):
	@echo "\033[35;1m>>>Creating objects folder...\033[0m"
		@echo "$(CYAN)Linking files ... $(RESET)\c)"
	@mkdir $(ODIR)

$(NAME): $(LIB_OBJ) $(PARSER_OBJ) $(MD5_OBJ) $(SHA256_OBJ) $(SHA224_OBJ) $(SHA512_OBJ) $(SHA384_OBJ)
	@ar rcs ./obj/$(PARSER_LIB) $(PARSER_OBJ)
	@echo "$(CYAN)█$(RESET)\c)"
	@ar rcs ./obj/$(LIB_MINI_NAME) $(LIB_OBJ)
	@echo "$(CYAN)█$(RESET)\c)"
	@ar rcs ./obj/$(MD5_LIB) $(MD5_OBJ)
	@echo "$(CYAN)█$(RESET)\c)"
	@ar rcs ./obj/$(SHA256_LIB) $(SHA256_OBJ)
	@echo "$(CYAN)█$(RESET)\c)"
	@ar rcs ./obj/$(SHA224_LIB) $(SHA224_OBJ)
	@echo "$(CYAN)█$(RESET)\c)"
	@ar rcs ./obj/$(SHA512_LIB) $(SHA512_OBJ)
	@echo "$(CYAN)█$(RESET)\c)"
	@ar rcs ./obj/$(SHA384_LIB) $(SHA384_OBJ)
	@echo "$(CYAN)█$(RESET)\c)"
	@make -C ./src/ft_printf/
	@echo "$(CYAN)█$(RESET)\c)"
	@gcc -o $(NAME) ./obj/$(PARSER_LIB) ./obj/$(LIB_MINI_NAME) ./obj/$(MD5_LIB) ./obj/$(SHA256_LIB) ./obj/$(SHA512_LIB) ./obj/$(SHA224_LIB) ./obj/$(SHA384_LIB) $(FT_PRINTF)
	@echo "$(RED)███$(RESET)\c)"
	@echo "\033[0;31m\nDone$(HEADER)\033[0m";
clean:
	@/bin/rm -rf $(LIB_OBJ) $(PARSER_OBJ) $(MD5_OBJ) $(SHA256_OBJ) $(SHA512_OBJ) $(SHA224_OBJ) $(SHA384_OBJ)
	@make clean -C ./src/ft_printf/
	@echo "\033[35;1m>>>Removed OBJ Files\033[0m"
	
fclean: clean
	@/bin/rm -rf $(ODIR) $(NAME)
	@make fclean -C ./src/ft_printf/
	@echo "\033[35;1m>>>Removed executed files\033[0m"

re: fclean all
