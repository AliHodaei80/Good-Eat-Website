CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) goodeats.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp examples/handlers.hpp examples/good_eat.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/good_eat.o: examples/good_eat.hpp examples/good_eat.cpp examples/sorting.hpp examples/person.hpp examples/chef.hpp examples/user.hpp examples/inputs.hpp examples/recipe.hpp examples/shelf.hpp examples/consts.hpp
	$(CC) $(CF) -c examples/good_eat.cpp -o $(BUILD_DIR)/good_eat.o

$(BUILD_DIR)/user.o: examples/user.hpp examples/user.cpp examples/shelf.hpp
	$(CC) $(CF) -c examples/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/sorting.o: examples/sorting.hpp examples/sorting.cpp examples/recipe.hpp examples/person.hpp
	$(CC) $(CF) -c examples/sorting.cpp -o $(BUILD_DIR)/sorting.o

$(BUILD_DIR)/shelf.o: examples/shelf.hpp examples/shelf.cpp examples/recipe.hpp
	$(CC) $(CF) -c examples/shelf.cpp -o $(BUILD_DIR)/shelf.o

$(BUILD_DIR)/recipe.o: examples/recipe.hpp examples/recipe.cpp examples/consts.hpp
	$(CC) $(CF) -c examples/recipe.cpp -o $(BUILD_DIR)/recipe.o

$(BUILD_DIR)/person.o: examples/person.hpp examples/person.cpp examples/consts.hpp
	$(CC) $(CF) -c examples/person.cpp -o $(BUILD_DIR)/person.o

$(BUILD_DIR)/inputs.o: examples/inputs.hpp examples/inputs.cpp
	$(CC) $(CF) -c examples/inputs.cpp -o $(BUILD_DIR)/inputs.o

$(BUILD_DIR)/chef.o: examples/chef.hpp examples/chef.cpp examples/sorting.hpp examples/inputs.hpp examples/recipe.hpp examples/shelf.hpp
	$(CC) $(CF) -c examples/chef.cpp -o $(BUILD_DIR)/chef.o

$(BUILD_DIR)/main.o: examples/main.cpp examples/good_eat.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

goodeats.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/chef.o $(BUILD_DIR)/person.o $(BUILD_DIR)/user.o $(BUILD_DIR)/sorting.o $(BUILD_DIR)/shelf.o $(BUILD_DIR)/recipe.o $(BUILD_DIR)/inputs.o $(BUILD_DIR)/good_eat.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/chef.o $(BUILD_DIR)/person.o $(BUILD_DIR)/user.o $(BUILD_DIR)/sorting.o $(BUILD_DIR)/shelf.o $(BUILD_DIR)/recipe.o $(BUILD_DIR)/inputs.o $(BUILD_DIR)/good_eat.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o goodeats.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
