CC		= g++
CFLAGS	= -Wall
LDFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -lGL
DEBUG_FLAGS	= -fsanitize=address -g

SRCS	= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

OBJ_DIR	= .obj
OBJS	= $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

NAME	= mineclone

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(NAME)

re: clean all
