CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
NAME = ex04

SRCS = main.cpp multiplier.cpp adder.cpp RPN.cpp AST.cpp truth_table.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re