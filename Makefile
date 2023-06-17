NAME = s21_matrix_oop.a
TEST = test
REPORT = gcov_report

CXX = gcc
#RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
AR = ar rcs

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_LIBS = -lgtest -lstdc++ -pthread -lm
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -g -O0

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
TEST_SRC_DIR = ./tests
TEST_OBJ_DIR = ./tests/obj
GCOV_DIR = ./gcov_report
GCOV_OBJ_DIR = ./gcov_report/obj

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cc=.o)))
INCLUDE = $(wildcard $(INCLUDE_DIR)/*.h)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cc)
TEST_OBJ = $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.cc=.o)))
GCOV_OBJ = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(SRC:.cc=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $?

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(INCLUDE)
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

$(TEST): $(TEST_OBJ) $(NAME)
	$(CXX) -g -o $@ $? $(TEST_LIBS)
	./$(TEST)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cc $(INCLUDE)
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

$(REPORT): $(GCOV_OBJ) $(TEST_OBJ)
	$(CXX) $(GCOV_FLAGS) -o $(TEST) $? $(TEST_LIBS)
	./$(TEST)
	$(RM) stl_algobase.h.gcov move.h.gcov
	gcov $(GCOV_OBJ_DIR)/*.gcno
	mv *.gcov $(GCOV_OBJ_DIR)/
	lcov -c -t "s21_matrix_oop" -o $(GCOV_DIR)/report.info -d $(GCOV_OBJ_DIR)
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/report.info

$(GCOV_OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(INCLUDE)
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) $(GCOV_FLAGS) -I$(INCLUDE_DIR) -o $@ -c $<
	

clean:
	$(RMDIR) $(TEST_OBJ_DIR)
	$(RM) $(TEST)
	$(RMDIR) $(OBJ_DIR)
	$(RM) $(NAME)
	$(RMDIR) $(GCOV_DIR)

format:
	cp materials/linters/.clang-format .
	clang-format -i $(SRC) $(TEST_SRC) $(INCLUDE) $(TEST_INCLUDE)
	rm .clang-format

.PHONY: all clean $(TEST) format

