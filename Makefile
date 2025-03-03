CXX			= g++
CXXFLAGS	= -Wall -MMD -MP -I/usr/include/freetype2 -O2
LDFLAGS		= -lSDL2 -lGLEW -lGL -lfreetype
DEBUG_FLAGS	= -g -fsanitize=address

SRCS		= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

INCLUDE_DIR	= ./include

OBJ_DIR		= .obj
OBJS		= $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

NAME		= mineclone

all: debug

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(NAME)

release: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

-include $(OBJS:.o=.d)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(NAME)

re: clean all release debug
