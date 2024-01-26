CC		= g++
CFLAGS	= -Wall
LDFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -lGL
DEBUG_FLAGS	= -fsanitize=address -g

SRCS	= $(wildcard src/*.cpp)

OBJ_DIR	= .obj
OBJS	= $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

NAME	= mineclone

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(NAME)

re: clean all
