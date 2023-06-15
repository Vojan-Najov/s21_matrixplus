NAME = s21_matrix_oop.a
TEST = test

CXX = gcc
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
AR = ar rcs

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_LIBS = -lgtest -lstdc++ -pthread -lm

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
TEST_SRC_DIR = ./tests
TEST_OBJ_DIR = ./tests/obj

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cc=.o)))
INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cc)
TEST_OBJ = $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.cc=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $?

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(INCLUDE)
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

$(TEST): $(TEST_OBJ) $(NAME)
	$(CXX) -o $@ $? $(TEST_LIBS)
	./$(TEST)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cc $(INCLUDE)
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

clean:
	$(RMDIR) $(TEST_OBJ_DIR)
	$(RM) $(TEST)
	$(RMDIR) $(OBJ_DIR)
	$(RM) $(NAME)

.PHONY: all clean $(TEST)

