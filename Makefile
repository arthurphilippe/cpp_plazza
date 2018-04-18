##
## EPITECH PROJECT, 2018
## nanotekspice
## File description:
## Makefile
##

CXX		=	g++

NAME		=	plazza

RM		=	rm -vf

MAIN		=	src/main.cpp

SRCS		=	src/Command.cpp

OBJ_MAIN	=	$(MAIN:.cpp=.o)

OBJS		=	$(SRCS:.cpp=.o)

TEST		=	unit_tests.out

SRCS_TEST	=	tests/test-Command.cpp

SRCS_TEST	+=	$(OBJS)

OBJS_TEST	=	$(SRCS_TEST:.cpp=.o)

CPPFLAGS	=	-W -Wextra -Wall -Iinclude/ -std=c++17

%.o: %.cpp
	@printf "[\033[0;36mcompiling\033[0m]% 39s\r" $< | tr " " "."
	@$(CXX) -c -o $@ $< $(CPPFLAGS)
	@printf "[\033[0;32mcompiled\033[0m]% 40s\n" $< | tr " " "."

all: $(NAME)

debug: CPPFLAGS += -ggdb
debug: fclean
debug: $(NAME)

tests: CXX=g++
tests: $(TEST)

tests_run: tests
	@./$(TEST)

$(NAME): $(OBJ_MAIN) $(OBJS)
	@printf "[\033[0;36mlinking\033[0m]% 41s\r" $(NAME) | tr " " "."
	@$(CXX) $(OBJ_MAIN) $(OBJS) -o $(NAME)
	@printf "[\033[0;36mlinked\033[0m]% 42s\n" $(NAME) | tr " " "."

$(TEST): $(OBJS_TEST)
	@printf "[\033[0;36mlinking\033[0m]% 41s\r" $(TEST) | tr " " "."
	@$(CXX) $(OBJS_TEST) -o $(TEST) -lcriterion
	@printf "[\033[0;36mlinked\033[0m]% 42s\n" $(TEST) | tr " " "."
clean:
	@printf "[\033[0;31mdeletion\033[0m][objects]% 31s\n" `$(RM) $(OBJ_MAIN) $(OBJS) $(OBJS_TEST) | wc -l | tr -d '\n'` | tr " " "."

fclean: clean
	@$(RM) $(NAME) $(TEST) > /dev/null
	@printf "[\033[0;31mdeletion\033[0m][binary]% 32s\n" $(NAME) | tr " " "."

re: fclean all

.PHONY: all clean fclean re debug tests
