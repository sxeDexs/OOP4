# Указываем компилятор и компиляцию
CXX = g++
CPP = g++ -c

# Директория с исходниками
SRC_DIR = .
INPUT_DIR = $(SRC_DIR)/input
ABILITIES_DIR = $(SRC_DIR)/abilities
OUTPUT_DIR = $(SRC_DIR)/output
STATE_DIR = $(SRC_DIR)/state
INCLUDE_DIR = $(SRC_DIR)/nlohmann

# Главный исходный файл
MAIN_SRC = main.cpp

# Цель по умолчанию
all: linking clean

# Линковка объектных файлов
linking: main.o \
         gameField.o game.o \
         ship.o shipManager.o abilityManager.o \
         fileHandler.o gameState.o \
         doubleDamage.o bombard.o scanner.o \
         drawField.o fieldRender.o outputMessage.o messageRender.o \
         input.o inputCommands.o
	$(CXX) -o Battleship $^

# Правила для компиляции файлов .cpp в .o
%.o: $(SRC_DIR)/%.cpp
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

%.o: $(INPUT_DIR)/%.cpp
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

%.o: $(ABILITIES_DIR)/%.cpp
	$(CPP) -o $@ $<

%.o: $(OUTPUT_DIR)/%.cpp
	$(CPP) -o $@ $<

%.o: $(STATE_DIR)/%.cpp
	$(CPP) -I$(INCLUDE_DIR) -o $@ $<

# Объектные файлы из разных папок
main.o: $(SRC_DIR)/main.cpp
gameField.o: $(SRC_DIR)/gameField.cpp $(SRC_DIR)/gameField.h
game.o: $(SRC_DIR)/game.cpp $(SRC_DIR)/game.h
ship.o: $(SRC_DIR)/ship.cpp $(SRC_DIR)/ship.h
shipManager.o: $(SRC_DIR)/shipManager.cpp $(SRC_DIR)/shipManager.h
abilityManager.o: $(SRC_DIR)/abilityManager.cpp $(SRC_DIR)/abilityManager.h
fileHandler.o: $(STATE_DIR)/fileHandler.cpp $(STATE_DIR)/fileHandler.h
gameState.o: $(STATE_DIR)/gameState.cpp $(STATE_DIR)/gameState.h
doubleDamage.o: $(ABILITIES_DIR)/doubleDamage.cpp $(ABILITIES_DIR)/doubleDamage.h
bombard.o: $(ABILITIES_DIR)/bombard.cpp $(ABILITIES_DIR)/bombard.h
scanner.o: $(ABILITIES_DIR)/scanner.cpp $(ABILITIES_DIR)/scanner.h
drawField.o: $(OUTPUT_DIR)/drawField.cpp $(OUTPUT_DIR)/drawField.h
fieldRender.o: $(OUTPUT_DIR)/fieldRender.cpp $(OUTPUT_DIR)/fieldRender.h
outputMessage.o: $(OUTPUT_DIR)/outputMessage.cpp $(OUTPUT_DIR)/outputMessage.h
messageRender.o: $(OUTPUT_DIR)/messageRender.cpp $(OUTPUT_DIR)/messageRender.h
input.o: $(INPUT_DIR)/input.cpp $(INPUT_DIR)/input.h
inputCommands.o: $(INPUT_DIR)/InputCommands.cpp $(INPUT_DIR)/InputCommands.h

# Очистка объектных файлов
clean:
	rm -f *.o $(ABILITIES_DIR)/*.o $(INPUT_DIR)/*.o $(OUTPUT_DIR)/*.o $(STATE_DIR)/*.o
