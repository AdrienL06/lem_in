##
## EPITECH PROJECT, 2023
## lem_in
## File description:
## Makefile | Originally created by Adrien LACHAMBRE | Edited by Virgile LEGROS
##

ifeq ($(shell uname),Linux)
    ECHO := echo -e
else ifeq ($(OS),Windows_NT)
    ECHO := echo.
else
    ECHO := echo
endif
DEFAULT 	=	"\033[0m"
BOLD_T  	=	"\033[1m"
DIM_T   	=	"\033[2m"
UNDLN_T 	=	"\033[4m"
RED_C   	=	"\033[31m"
GREEN_C 	=	"\033[32m"
LIGHT_RED	=	"\033[91m"
LIGHT_GREEN	=	"\033[92m"
LIGHT_CYAN	=	"\033[96m"
define success_message
	@$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN)	\
		"$(1)\n"$(DEFAULT) || $(ECHO) $(BOLD_T)$(RED_C)"[✘]				   	\
		"$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(1)\n"$(DEFAULT)
endef

MAIN 		= 	src/main.c													\

MINI_LIB	= 	src/mini_lib/mini_lib.c										\
				src/mini_lib/mini_lib2.c									\
				src/mini_lib/mini_lib3.c									\
				src/mini_lib/my_str_to_word_array.c							\

LL  		= 	src/linked_list/ll_string.c									\
				src/linked_list/ll_void.c									\
				src/linked_list/stack.c										\

GRAPH		= 	src/graph/graph.c											\

HASHMAP 	= 	src/hashmap/hashmap.c										\
				src/hashmap/hashmap1.c										\

PARSING 	=	src/parsing/load_file.c										\
				src/parsing/parsing_main.c									\
				src/parsing/parsing_utils.c									\
				src/parsing/parsing_rooms.c									\
				src/parsing/parsing_tunnels.c								\

DISPLAY 	=	src/display/display.c										\

ALGORITHM 	=	src/algorithm/routes.c										\
				src/algorithm/moves.c										\
				src/algorithm/ant.c											\


SRC 		= 	$(MAIN) $(MINI_LIB) $(LL) $(GRAPH) $(HASHMAP) $(PARSING) 	\
				$(DISPLAY) $(ALGORITHM)
OBJ 		= 	$(patsubst src/%.c,object/%.o,$(SRC))

NAME		=	lem_in

CFLAGS  	+=	-Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wshadow	\
				-Wredundant-decls -I./include								\

ifeq ($(shell uname),Linux)
	CFLAGS += -Wlogical-op
endif

OPTIFLAGS	=	-O3 -ffast-math -march=native -msse2 -mfpmath=sse

CRITFLAGS	=	-lcriterion --coverage -L/opt/homebrew/lib -I./include      \
				-I/opt/homebrew/Cellar/criterion/2.4.1_2/include/

all:	$(NAME)

$(NAME): $(OBJ)
	@gcc $(OBJ) -o $(NAME) $(CFLAGS)
	$(call success_message, $(NAME))

optimization:
	@gcc $(SRC) -o $(NAME) $(CFLAGS) $(OPTIFLAGS)
	$(call success_message, $(NAME))
	@make clean

g3only:
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g3
	$(call success_message, $(NAME))
	@make clean

gprof	$(ARGS):
	@$(ECHO) $(GREEN_C)"\nRunning gprof" $(DEFAULT)
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -pg
	$(call success_message, $(NAME))
	@./$(NAME) $(ARGS)
	@make clean
	@gprof -b -p $(NAME)

gprof_plus	$(ARGS):
	@$(ECHO) $(GREEN_C)"\nRunning gprof_plus" $(DEFAULT)
	@gcc $(SRC) -o $(NAME) $(CFLAGS) $(OPTIFLAGS) -pg
	$(call success_message, $(NAME))
	@./$(NAME) $(ARGS)
	@make clean
	@gprof -b -p $(NAME)

valgrind $(ARGS):
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g3
	$(call success_message, $(NAME))
	@make clean
	@valgrind -s ./$(NAME) $(ARGS)

valgrind_plus $(ARGS):
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g3
	$(call success_message, $(NAME))
	@make clean
	@valgrind -s --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS)

debug:
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g
	$(call success_message, $(NAME))

clean:
	@find . -type f \( -iname "*~" \) -delete
	@find . -name "*.gcno" -delete
	@find . -name "*.gcda" -delete
	@$(RM) coverage.*
	@$(RM) -f tests/unit_tests
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s unit_test"$(DEFAULT)
	@$(RM) -rf object/
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.*
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"Valgrind files"$(DEFAULT)

fclean:	clean
	@$(RM) $(NAME)
	@$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"Binary $(NAME)"$(DEFAULT)

re:	fclean all

object/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< && $(ECHO) $(GREEN_C)[OK]  	\
		$(BOLD_T) $< $(DEFAULT) || $(ECHO) $(RED_C)[KO]$(BOLD_T) $< $(DEFAULT)

GITIGNORE_FILES = *.o *.a *.log *.json *.vscode vgcore.* .idea/ *.txt		\
					$(NAME) .devcontainer/ lem_in.dSYM/ .DS_Store .gitignore\
					*.gcno *.gcda tests/unit_tests html/ coverage.*         \

gitignore:
	@$(ECHO) $(LIGHT_CYAN)$(BOLD_T)[DOING GITIGNORE]$(DEFAULT)$(GREEN_C);	\
	for file in $(GITIGNORE_FILES); do										\
	    $(ECHO) $$file; 													\
	done >> .gitignore;														\

.PHONY: all optimization g3only gprof gprof_plus valgrind valgrind_plus     \
		debug clean fclean re gitignore
