CXX			= g++
CXXFLAGS	= -Wall -MMD -MP
LDFLAGS		= -lSDL2 -lGLEW -lGL
DEBUG_FLAGS	= -fsanitize=address -g

SRCS	= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

OBJ_DIR	= .obj
OBJS	= $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

NAME	= mineclone

all: $(NAME)

echo:
	@echo $(CXXFLAGS)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) 

-include $(OBJS:.o=.d)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(NAME)

re: clean all
