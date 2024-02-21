# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 11:07:12 by aattali           #+#    #+#              #
#    Updated: 2024/02/21 13:08:40 by aattali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#* ************************************************************************** *#
#* *                            GENERAL INFO                                * *#
#* ************************************************************************** *#

TARGET := minishell

#* ************************************************************************** *#
#* *                             COMPILATION                                * *#
#* ************************************************************************** *#

CC := clang
CFLAGS += -Wall -Werror -Wextra
LIBRARY_FLAGS := -L/usr/lib -Lmlx -lXext -lX11 -lz -lm -lreadline

#* ************************************************************************** *#
#* *                              INCLUDES                                  * *#
#* ************************************************************************** *#

INCLUDES := includes
INCLUDES_FLAGS += $(addprefix -I, $(INCLUDES))

#* ************************************************************************** *#
#* *                             LIBRARIES                                * *#
#* ************************************************************************** *#

IS_LIBFT := true
LIBFT_DIR := libft
LIBFT_INCLUDES_DIRS := libft/includes
LIBFT_NAME := libft.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

ifeq ($(IS_LIBFT), true)
	INCLUDES_FLAGS += $(addprefix -I , ${LIBFT_INCLUDES_DIRS})
	ALL_LIBS += $(LIBFT)
endif

IS_MLX := false
MLX_DIR := mlx
MLX_INCLUDES_DIRS := mlx
MLX_NAME := libmlx_Linux.a
MLX = $(MLX_DIR)/$(MLX_NAME)

ifeq ($(IS_MLX), true)
	INCLUDES_FLAGS += $(addprefix -I, ${MLX_INCLUDES_DIRS})
	ALL_LIBS += $(MLX)
endif

#* ************************************************************************** *#
#* *                               SOURCES                                  * *#
#* ************************************************************************** *#

-include make/sources.mk
SRCDIR := src

#* ************************************************************************** *#
#* *                              OBJECTS                                   * *#
#* ************************************************************************** *#

OBJDIR := obj
OBJECTS := ${SOURCES:%.c=${OBJDIR}/%.o}

#* ************************************************************************** *#
#* *                            DEPENDENCIES                                * *#
#* ************************************************************************** *#

DEPENDENCIES := $(OBJECTS:.o=.d)

#* ************************************************************************** *#
#* *                           RULES FILTER                                 * *#
#* ************************************************************************** *#

ifeq (noflag, $(filter noflag,$(MAKECMDGOALS)))
	CFLAGS += -Wall -Wextra
else
	CFLAGS += -Wall -Wextra -Werror
endif

ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS += -g3
endif

ifeq (sanadd, $(filter sanadd,$(MAKECMDGOALS)))
	CFLAGS += -fsanitize=address -g3
endif

ifeq (santhread, $(filter santhread,$(MAKECMDGOALS)))
	CFLAGS += -fsanitize=thread -g3
endif

ifeq (optimize, $(filter optimize,$(MAKECMDGOALS)))
	CFLAGS += -O3
endif

#* ************************************************************************** *#
#* *                          TEXT CONSTANTS                                * *#
#* ************************************************************************** *#

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
THIN = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
RESET_COLOR = \033[0m

#* ************************************************************************** *#
#* *                           PRESENTATION                                 * *#
#* ************************************************************************** *#

define success_message
	@echo "✨ $(GREEN)$(BOLD)COMPILATION SUCCESSFUL$(RESET_COLOR) ✨"
endef

define linking_message
	@echo "$(YELLOW)Linking $(BOLD)$(CYAN)$@ $(RESET_COLOR)$(YELLOW)...$(RESET_COLOR)"
endef

LAST_DIR = ""
FIRST_COMPILE_MESSAGE = true
define compile_message
	@if [ "$(FIRST_COMPILE_MESSAGE)" = "true" ]; then \
		printf "\n"; \
		FIRST_COMPILE_MESSAGE=false; \
	fi
	@if [ "$(dir $<)" != "$(LAST_DIR)" ]; then \
		printf "$(BOLD)$(YELLOW)Compiling files in directory $(RESET_COLOR)$(BOLD)$(CYAN)$(dir $<)$(RESET_COLOR)\n"; \
		LAST_DIR="$(dir $<)"; \
	fi
	printf "$(CYAN)    • $(notdir $<)";
	@$(eval LAST_DIR := $(dir $<))
endef


#* ************************************************************************** *#
#* *                          MAKEFILE RULES                                * *#
#* ************************************************************************** *#

all: $(TARGET)

$(LIBFT):
ifeq ($(IS_LIBFT), true)
	@echo
	@echo "$(CYAN)Compiling library :$(RESET_COLOR)$(BOLD)$(YELLOW) LIBFT $(RESET_COLOR)$(CYAN)...$(RESET_COLOR)"
	@make --silent -C $(LIBFT_DIR) all
	@echo "$(GREEN)$(BOLD)៙ LIBFT$(RESET_COLOR)$(GREEN) successfully compiled ! 👏 $(RESET_COLOR)"
endif

$(MLX):
ifeq ($(IS_MLX), true)
	@echo
	@echo "$(CYAN)Compiling library :$(RESET_COLOR)$(BOLD)$(YELLOW) MLX $(RESET_COLOR)$(CYAN)...$(RESET_COLOR)"
	@make -C $(MLX_DIR) all > /dev/null 2>&1
	@echo "$(GREEN)$(BOLD)៙ MLX$(RESET_COLOR)$(GREEN) successfully compiled ! 👏 $(RESET_COLOR)"
endif

# -------------------- #
# Create object files. #
# -------------------- #

$(OBJECTS): $(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(call compile_message)
	@$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d) $(INCLUDES_FLAGS) -c $< -o $@

# ---------------------------------------- #
# Link the files after compiling them all. #
# ---------------------------------------- #

-include $(DEPENDENCIES)
$(TARGET): $(LIBFT) $(OBJECTS)
	@echo ""
	@$(call linking_message)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -o $@ $(OBJECTS) $(ALL_LIBS) $(LIBRARY_FLAGS)
	@echo ""
	@$(call success_message)

# --------------------- #
# Delete compiled data. #
# --------------------- #

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)Deleting $(CYAN)$(OBJECTS_PATH) $(YELLOW)...$(RESET_COLOR)"

fclean: clean
	@rm -rf $(TARGET)
	@echo "$(YELLOW)Deleting $(CYAN)$(NAME) executable $(YELLOW)...$(RESET_COLOR)"


fcleanlib : fclean
ifeq ($(IS_LIBFT), true)
	@echo "$(YELLOW)Deleting all compiled $(CYAN)LIBFT$(YELLOW) files ...$(RESET_COLOR)"
	@make --silent -C $(LIBFT_DIR) fclean
endif

ifeq ($(IS_MLX), true)
	@echo "$(YELLOW)Deleting all compiled $(CYAN)MLX$(YELLOW) files ...$(RESET_COLOR)"
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
endif

# ------------------------------- #
# Create the list of all sources. #
# ------------------------------- #

gmk:
	if [ -d make ];then echo ok;else mkdir make;fi
	@find -name '*.c' -printf "%d%p\n" | sort -n | grep -v libft | grep -v mlx | sed 's/^[[:digit:]]/SOURCES += /' > make/sources.mk

norm:
	@norminette $(LIBFT_DIR)
	@norminette $(SRCDIR) $(INCLUDES)

vg: debug
	valgrind --track-origins=yes --leak-check=full --suppressions=readline.supp ./minishell

vgc: debug
	valgrind --track-origins=yes --leak-check=full --track-fds=yes --trace-children=yes --suppressions=readline.supp ./minishell

# --------------------- #
#      Recompile.       #
# --------------------- #

re: fclean all

relib : fcleanlib all

bonus: all

optimize: all

debug: all

noflag: all

sanadd: all

santhread: all

.PHONY: bonus clean fclean fcleanlib gmk re relib noflag debug optimize sanadd santhread norm vg vgc
