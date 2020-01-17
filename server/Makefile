##
## EPITECH PROJECT, 2019
## 301dannon_2019
## File description:
## Makefile
##

CXX	:= g++ -std=c++17

RM	:= rm -f

CXXFLAGS	:= -W -Wall -Wextra -g3
CPPFLAGS	:= -I./include
LDFLAGS		:= -pthread -lboost_system

NAME	:= server


SRC	:=	\
	src/main.cpp	\
	src/Profile.cpp	\
	src/Database.cpp	\
	src/Server.cpp

OBJ	:=	$(SRC:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $@ $(LDFLAGS)


clean:

fclean:	clean
	$(RM) $(OBJ)

re:	fclean all

.PHONY:	clean fclean re all
