NAME = s21_matrix_oop.a

CXX = gcc
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
AR = ar rcs

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))
INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $?

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE)
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

clean:
	$(RMDIR) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean

