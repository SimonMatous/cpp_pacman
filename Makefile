TARGET = matousi1
CXX = g++ -g
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++14
BUILD_DIR = build
MKDIR     = mkdir -p

.PHONY: all
all: compile

.PHONY: compile
compile:$(TARGET)

.PHONY: run
run:$(TARGET)
	./$(TARGET)

$(TARGET): $(BUILD_DIR)/CApplication.o $(BUILD_DIR)/CBlueGhostEasy.o $(BUILD_DIR)/CGhost.o $(BUILD_DIR)/CMap.o $(BUILD_DIR)/COrangeGhostEasy.o $(BUILD_DIR)/COrangeGhostMedium.o $(BUILD_DIR)/CPacman.o $(BUILD_DIR)/CPinkGhostEasy.o $(BUILD_DIR)/CRedGhostEasy.o $(BUILD_DIR)/CRedGhostMedium.o $(BUILD_DIR)/CSession.o $(BUILD_DIR)/main.o $(BUILD_DIR)/CPinkGhostMedium.o $(BUILD_DIR)/CBlueGhostMedium.o $(BUILD_DIR)/CPinkGhostHard.o $(BUILD_DIR)/CBlueGhostHard.o $(BUILD_DIR)/CRedGhostHard.o $(BUILD_DIR)/COrangeGhostHard.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

doc: doc src/CApplication.h src/CBlueGhostEasy.h src/CBlueGhostHard.h src/CBlueGhostMedium.h src/CGhost.h src/CMap.h src/COrangeGhostEasy.h src/COrangeGhostHard.h src/COrangeGhostMedium.h src/CPacman.h src/CPinkGhostEasy.h src/CPinkGhostHard.h src/CPinkGhostMedium.h src/CRedGhostEasy.h src/CRedGhostHard.h src/CRedGhostMedium.h src/CSession.h
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ 2>/dev/null


# Dependencies
CApplication.o: src/CApplication.cpp src/CApplication.h src/CSession.h src/CMap.h src/CGhost.h src/COrangeGhostEasy.h src/CRedGhostEasy.h src/CPinkGhostEasy.h src/CBlueGhostEasy.h src/CRedGhostMedium.h src/COrangeGhostMedium.h src/CPinkGhostMedium.h src/CBlueGhostMedium.h src/CRedGhostHard.h src/COrangeGhostHard.h src/CPinkGhostHard.h src/CBlueGhostHard.h src/CPacman.h
CBlueGhostEasy.o: src/CBlueGhostEasy.cpp src/CBlueGhostEasy.h src/CGhost.h
CBlueGhostHard.o: src/CBlueGhostHard.cpp src/CBlueGhostHard.h src/CGhost.h
CBlueGhostMedium.o: src/CBlueGhostMedium.cpp src/CBlueGhostMedium.h src/CGhost.h
CGhost.o: src/CGhost.cpp src/CGhost.h
CMap.o: src/CMap.cpp src/CMap.h
COrangeGhostEasy.o: src/COrangeGhostEasy.cpp src/COrangeGhostEasy.h src/CGhost.h
COrangeGhostHard.o: src/COrangeGhostHard.cpp src/COrangeGhostHard.h src/CGhost.h
COrangeGhostMedium.o: src/COrangeGhostMedium.cpp src/COrangeGhostMedium.h src/CGhost.h
CPacman.o: src/CPacman.cpp src/CPacman.h src/CSession.h src/CMap.h src/CGhost.h src/COrangeGhostEasy.h src/CRedGhostEasy.h src/CPinkGhostEasy.h src/CBlueGhostEasy.h src/CRedGhostMedium.h src/COrangeGhostMedium.h src/CPinkGhostMedium.h src/CBlueGhostMedium.h src/CRedGhostHard.h src/COrangeGhostHard.h src/CPinkGhostHard.h src/CBlueGhostHard.h
CPinkGhostEasy.o: src/CPinkGhostEasy.cpp src/CPinkGhostEasy.h src/CGhost.h
CPinkGhostHard.o: src/CPinkGhostHard.cpp src/CPinkGhostHard.h src/CGhost.h
CPinkGhostMedium.o: src/CPinkGhostMedium.cpp src/CPinkGhostMedium.h src/CGhost.h
CRedGhostEasy.o: src/CRedGhostEasy.cpp src/CRedGhostEasy.h src/CGhost.h
CRedGhostHard.o: src/CRedGhostHard.cpp src/CRedGhostHard.h src/CGhost.h
CRedGhostMedium.o: src/CRedGhostMedium.cpp src/CRedGhostMedium.h src/CGhost.h
CSession.o: src/CSession.cpp src/CSession.h src/CMap.h src/CGhost.h src/COrangeGhostEasy.h src/CRedGhostEasy.h src/CPinkGhostEasy.h src/CBlueGhostEasy.h src/CRedGhostMedium.h src/COrangeGhostMedium.h src/CPinkGhostMedium.h src/CBlueGhostMedium.h src/CRedGhostHard.h src/COrangeGhostHard.h src/CPinkGhostHard.h src/CBlueGhostHard.h src/CPacman.h
main.o: src/main.cpp src/CApplication.h src/CSession.h src/CMap.h src/CGhost.h src/COrangeGhostEasy.h src/CRedGhostEasy.h src/CPinkGhostEasy.h src/CBlueGhostEasy.h src/CRedGhostMedium.h src/COrangeGhostMedium.h src/CPinkGhostMedium.h src/CBlueGhostMedium.h src/CRedGhostHard.h src/COrangeGhostHard.h src/CPinkGhostHard.h src/CBlueGhostHard.h src/CPacman.h
