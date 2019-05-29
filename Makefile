#CC specifies which compiler we're using
CC = g++

#flags for compilation
COMPILER_FLAGS = -Iinclude -Wall -pedantic -Wextra -g -c -std=c++14

#COMPILER_SDL_FLAGS = -Wall -pedantic -Wextra -g -c -std=c++11

#flags to link sdl libraries
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#directory in which I will store all binary files and also the final executable file
BUILD_DIR = build

#directory in which I will store the application binary
COMPILE_DIR = build

#name of the directory where documentation will be stored
DOCUMENTATION_DIR = doc

#directory with all source files
SOURCE_DIR = src

#directory of module with files decribing user interface
USER_INTERFACE_DIR = src/user_interface

#directory of module with files describing chess figures
FIGURES_DIR = src/figures

#directory of module with files describing rules of the game
RULES_DIR = src/rules

#directory of modules with files describing main logic of the application (main function, controller, game, board and constants)
MAIN_LOGIC_DIR = src/main_logic

#final executable
TARGET_EXEC = zieliwoj

.PHONY: all compile run doc clean

#builds all from the sources
all: compile doc

#compiles the application binary, the output binary will be stored at zieliwoj/zieliwoj
compile: $(BUILD_DIR)/AppWindow.o \
	     $(BUILD_DIR)/Bishop.o \
	 	 $(BUILD_DIR)/Board.o \
	 	 $(BUILD_DIR)/Castling.o \
	 	 $(BUILD_DIR)/Check.o \
	 	 $(BUILD_DIR)/CheckAttacksOnField.o \
	 	 $(BUILD_DIR)/Checkmate.o \
	 	 $(BUILD_DIR)/ChoosePlayersView.o \
	 	 $(BUILD_DIR)/ConstantsAndEnums.o \
	 	 $(BUILD_DIR)/Draw.o \
	 	 $(BUILD_DIR)/DrawBoardRect.o \
	 	 $(BUILD_DIR)/EndGameView.o \
	 	 $(BUILD_DIR)/EnPassant.o \
	 	 $(BUILD_DIR)/Figure.o \
	 	 $(BUILD_DIR)/Game.o \
	 	 $(BUILD_DIR)/HelpView.o \
	 	 $(BUILD_DIR)/King.o \
	 	 $(BUILD_DIR)/Knight.o \
	 	 $(BUILD_DIR)/LoadGameView.o \
	 	 $(BUILD_DIR)/main.o \
	 	 $(BUILD_DIR)/MainController.o \
	 	 $(BUILD_DIR)/MainMenuView.o \
	 	 $(BUILD_DIR)/Move.o \
	 	 $(BUILD_DIR)/NewGameView.o \
	 	 $(BUILD_DIR)/Pawn.o \
	 	 $(BUILD_DIR)/Promotion.o \
	 	 $(BUILD_DIR)/PromotionView.o \
	 	 $(BUILD_DIR)/Queen.o \
	 	 $(BUILD_DIR)/ReadState.o \
	 	 $(BUILD_DIR)/Rook.o \
	 	 $(BUILD_DIR)/SaveState.o \
	 	 $(BUILD_DIR)/SDL_Button.o \
	 	 $(BUILD_DIR)/Stalemate.o
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(COMPILE_DIR)
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/AppWindow.o \
							  $(BUILD_DIR)/Bishop.o \
							  $(BUILD_DIR)/Board.o \
							  $(BUILD_DIR)/Castling.o \
							  $(BUILD_DIR)/Check.o \
							  $(BUILD_DIR)/CheckAttacksOnField.o \
							  $(BUILD_DIR)/Checkmate.o \
							  $(BUILD_DIR)/ChoosePlayersView.o \
							  $(BUILD_DIR)/ConstantsAndEnums.o \
							  $(BUILD_DIR)/Draw.o \
							  $(BUILD_DIR)/DrawBoardRect.o \
							  $(BUILD_DIR)/EndGameView.o \
							  $(BUILD_DIR)/EnPassant.o \
							  $(BUILD_DIR)/Figure.o \
							  $(BUILD_DIR)/Game.o \
							  $(BUILD_DIR)/HelpView.o \
							  $(BUILD_DIR)/King.o \
							  $(BUILD_DIR)/Knight.o \
							  $(BUILD_DIR)/LoadGameView.o \
							  $(BUILD_DIR)/MainController.o \
							  $(BUILD_DIR)/MainMenuView.o \
							  $(BUILD_DIR)/Move.o \
							  $(BUILD_DIR)/NewGameView.o \
							  $(BUILD_DIR)/Pawn.o \
							  $(BUILD_DIR)/Promotion.o \
							  $(BUILD_DIR)/PromotionView.o \
							  $(BUILD_DIR)/Queen.o \
							  $(BUILD_DIR)/ReadState.o \
							  $(BUILD_DIR)/Rook.o \
							  $(BUILD_DIR)/SaveState.o \
							  $(BUILD_DIR)/SDL_Button.o \
							  $(BUILD_DIR)/Stalemate.o \
							  -o $(TARGET_EXEC) $(LINKER_FLAGS)

#executes the binary
run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

#run: $(COMPILE_DIR)/$(TARGET_EXEC)
#	./$(COMPILE_DIR)/$(TARGET_EXEC)

#create a documentation
doc:
	cd ./$(SOURCE_DIR); mkdir $(DOCUMENTATION_DIR); doxygen; mv doc ..; cd ..;
	#mkdir -p $(DOCUMENTATION_DIR)
	#cd $(DOCUMENTATION_DIR) ; \
	#doxygen -g sample_text.conf ; \
	#doxygen sample_text.conf ; \
	#cd .. ; \
	#cp ./$(DOCUMENTATION_DIR)/html/index.html ./$(DOCUMENTATION_DIR)/index.html

#delete all directories and files created with make
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(COMPILE_DIR)
	rm -rf $(DOCUMENTATION_DIR)
	rm -f $(TARGET_EXEC)

#I will store if alfabethically inside modules


#---------------------------------------------------------------------------------------------------------------------------
#---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---
#---------------------------------------------------------------------------------------------------------------------------

#Bishop.
$(BUILD_DIR)/Bishop.o: $(FIGURES_DIR)/Bishop.cpp $(FIGURES_DIR)/Figure.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(FIGURES_DIR)/Bishop.cpp -o $(BUILD_DIR)/Bishop.o

#Figure.
$(BUILD_DIR)/Figure.o: $(FIGURES_DIR)/Figure.cpp $(FIGURES_DIR)/Figure.hpp $(RULES_DIR)/Check.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(FIGURES_DIR)/Figure.cpp -o $(BUILD_DIR)/Figure.o

#King.
$(BUILD_DIR)/King.o: $(FIGURES_DIR)/King.cpp $(FIGURES_DIR)/Figure.hpp $(RULES_DIR)/Castling.hpp $(RULES_DIR)/CheckAttacksOnField.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(FIGURES_DIR)/King.cpp -o $(BUILD_DIR)/King.o

#Knight.
$(BUILD_DIR)/Knight.o: $(FIGURES_DIR)/Knight.cpp $(FIGURES_DIR)/Figure.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(FIGURES_DIR)/Knight.cpp -o $(BUILD_DIR)/Knight.o

#Pawn.
$(BUILD_DIR)/Pawn.o: $(FIGURES_DIR)/Pawn.cpp $(FIGURES_DIR)/Figure.hpp $(RULES_DIR)/EnPassant.hpp $(RULES_DIR)/Check.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(FIGURES_DIR)/Pawn.cpp -o $(BUILD_DIR)/Pawn.o

#Queen.
$(BUILD_DIR)/Queen.o: $(FIGURES_DIR)/Queen.cpp $(FIGURES_DIR)/Figure.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(FIGURES_DIR)/Queen.cpp -o $(BUILD_DIR)/Queen.o

#Rook.
$(BUILD_DIR)/Rook.o: $(FIGURES_DIR)/Rook.cpp $(FIGURES_DIR)/Figure.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(FIGURES_DIR)/Rook.cpp -o $(BUILD_DIR)/Rook.o

#---------------------------------------------------------------------------------------------------------------------------
#---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---FIGURES---
#---------------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------------
#----MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC-----
#---------------------------------------------------------------------------------------------------------------------------

#Board.
$(BUILD_DIR)/Board.o: $(MAIN_LOGIC_DIR)/Board.cpp $(MAIN_LOGIC_DIR)/Board.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(MAIN_LOGIC_DIR)/Board.cpp -o $(BUILD_DIR)/Board.o

#ConstantsAndEnums.
$(BUILD_DIR)/ConstantsAndEnums.o: $(MAIN_LOGIC_DIR)/ConstantsAndEnums.cpp $(MAIN_LOGIC_DIR)/ConstantsAndEnums.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(MAIN_LOGIC_DIR)/ConstantsAndEnums.cpp -o $(BUILD_DIR)/ConstantsAndEnums.o

#Game.
$(BUILD_DIR)/Game.o: $(MAIN_LOGIC_DIR)/Game.cpp $(MAIN_LOGIC_DIR)/Game.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(MAIN_LOGIC_DIR)/Game.cpp -o $(BUILD_DIR)/Game.o

#main.
$(BUILD_DIR)/main.o: $(MAIN_LOGIC_DIR)/main.cpp $(MAIN_LOGIC_DIR)/MainController.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(MAIN_LOGIC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

#MainController.
$(BUILD_DIR)/MainController.o: $(MAIN_LOGIC_DIR)/MainController.cpp $(MAIN_LOGIC_DIR)/MainController.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(MAIN_LOGIC_DIR)/MainController.cpp -o $(BUILD_DIR)/MainController.o

#ReadState.
$(BUILD_DIR)/ReadState.o: $(MAIN_LOGIC_DIR)/ReadState.cpp $(MAIN_LOGIC_DIR)/ReadState.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(MAIN_LOGIC_DIR)/ReadState.cpp -o $(BUILD_DIR)/ReadState.o

#SaveState.
$(BUILD_DIR)/SaveState.o: $(MAIN_LOGIC_DIR)/SaveState.cpp $(MAIN_LOGIC_DIR)/SaveState.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(MAIN_LOGIC_DIR)/SaveState.cpp -o $(BUILD_DIR)/SaveState.o

#---------------------------------------------------------------------------------------------------------------------------
#----MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC---MAIN_LOGIC-----
#---------------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------------
#---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---
#---------------------------------------------------------------------------------------------------------------------------

#Castling.
$(BUILD_DIR)/Castling.o: $(RULES_DIR)/Castling.cpp $(RULES_DIR)/Castling.hpp $(RULES_DIR)/Check.hpp $(RULES_DIR)/CheckAttacksOnField.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/Castling.cpp -o $(BUILD_DIR)/Castling.o

#Check.
$(BUILD_DIR)/Check.o: $(RULES_DIR)/Check.cpp $(RULES_DIR)/Check.hpp $(RULES_DIR)/CheckAttacksOnField.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/Check.cpp -o $(BUILD_DIR)/Check.o	

#CheckAttacksOnField.
$(BUILD_DIR)/CheckAttacksOnField.o: $(RULES_DIR)/CheckAttacksOnField.cpp $(RULES_DIR)/CheckAttacksOnField.hpp $(RULES_DIR)/EnPassant.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/CheckAttacksOnField.cpp -o $(BUILD_DIR)/CheckAttacksOnField.o

#Checkmate.
$(BUILD_DIR)/Checkmate.o: $(RULES_DIR)/Checkmate.cpp $(RULES_DIR)/Checkmate.hpp $(RULES_DIR)/CheckAttacksOnField.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/Checkmate.cpp -o $(BUILD_DIR)/Checkmate.o

#EnPassant.
$(BUILD_DIR)/EnPassant.o: $(RULES_DIR)/EnPassant.cpp $(RULES_DIR)/EnPassant.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/EnPassant.cpp -o $(BUILD_DIR)/EnPassant.o

#Move.
$(BUILD_DIR)/Move.o: $(RULES_DIR)/Move.cpp $(RULES_DIR)/Move.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/Move.cpp -o $(BUILD_DIR)/Move.o

#Promotion.
$(BUILD_DIR)/Promotion.o: $(RULES_DIR)/Promotion.cpp $(RULES_DIR)/Promotion.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/Promotion.cpp -o $(BUILD_DIR)/Promotion.o

#Stalemate.
$(BUILD_DIR)/Stalemate.o: $(RULES_DIR)/Stalemate.cpp $(RULES_DIR)/Stalemate.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(RULES_DIR)/Stalemate.cpp -o $(BUILD_DIR)/Stalemate.o

#---------------------------------------------------------------------------------------------------------------------------
#---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---RULES---
#---------------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------------
#---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE----
#---------------------------------------------------------------------------------------------------------------------------

#AppWindow .
$(BUILD_DIR)/AppWindow.o: $(USER_INTERFACE_DIR)/AppWindow.cpp $(USER_INTERFACE_DIR)/AppWindow.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/AppWindow.cpp -o $(BUILD_DIR)/AppWindow.o

#ChoosePlayersView.
$(BUILD_DIR)/ChoosePlayersView.o: $(USER_INTERFACE_DIR)/ChoosePlayersView.cpp $(USER_INTERFACE_DIR)/ChoosePlayersView.hpp $(USER_INTERFACE_DIR)/DrawBoardRect.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/ChoosePlayersView.cpp -o $(BUILD_DIR)/ChoosePlayersView.o

#Draw.
$(BUILD_DIR)/Draw.o: $(USER_INTERFACE_DIR)/Draw.cpp $(USER_INTERFACE_DIR)/Draw.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/Draw.cpp -o $(BUILD_DIR)/Draw.o

#DrawBoardRect.
$(BUILD_DIR)/DrawBoardRect.o: $(USER_INTERFACE_DIR)/DrawBoardRect.cpp $(USER_INTERFACE_DIR)/DrawBoardRect.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/DrawBoardRect.cpp -o $(BUILD_DIR)/DrawBoardRect.o

#EndGameView.
$(BUILD_DIR)/EndGameView.o: $(USER_INTERFACE_DIR)/EndGameView.cpp $(USER_INTERFACE_DIR)/EndGameView.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/EndGameView.cpp -o $(BUILD_DIR)/EndGameView.o

#HelpView.
$(BUILD_DIR)/HelpView.o: $(USER_INTERFACE_DIR)/HelpView.cpp $(USER_INTERFACE_DIR)/HelpView.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/HelpView.cpp -o $(BUILD_DIR)/HelpView.o

#LoadGameView.
$(BUILD_DIR)/LoadGameView.o: $(USER_INTERFACE_DIR)/LoadGameView.cpp $(USER_INTERFACE_DIR)/LoadGameView.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/LoadGameView.cpp -o $(BUILD_DIR)/LoadGameView.o

#MainMenuView.
$(BUILD_DIR)/MainMenuView.o: $(USER_INTERFACE_DIR)/MainMenuView.cpp $(USER_INTERFACE_DIR)/MainMenuView.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/MainMenuView.cpp -o $(BUILD_DIR)/MainMenuView.o

#NewGameView.
$(BUILD_DIR)/NewGameView.o: $(USER_INTERFACE_DIR)/NewGameView.cpp $(USER_INTERFACE_DIR)/NewGameView.hpp $(RULES_DIR)/Move.hpp $(RULES_DIR)/Check.hpp \
							$(RULES_DIR)/Checkmate.hpp $(RULES_DIR)/Promotion.hpp $(USER_INTERFACE_DIR)/PromotionView.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/NewGameView.cpp -o $(BUILD_DIR)/NewGameView.o

#PromotionView.
$(BUILD_DIR)/PromotionView.o: $(USER_INTERFACE_DIR)/PromotionView.cpp $(USER_INTERFACE_DIR)/PromotionView.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/PromotionView.cpp -o $(BUILD_DIR)/PromotionView.o

#SDL_Button.
$(BUILD_DIR)/SDL_Button.o: $(USER_INTERFACE_DIR)/SDL_Button.cpp $(USER_INTERFACE_DIR)/SDL_Button.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(USER_INTERFACE_DIR)/SDL_Button.cpp -o $(BUILD_DIR)/SDL_Button.o

#---------------------------------------------------------------------------------------------------------------------------
#---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE---USER_INTERFACE----
#---------------------------------------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------------------------------------


















#main function
#$(BUILD_DIR)/main.o: $(SOURCE_DIR)/main.cpp	$(SOURCE_DIR)/Figure.hpp $(SOURCE_DIR)/Board.hpp $(SOURCE_DIR)/Game.hpp $(SOURCE_DIR)/MainMenu.hpp
#	@mkdir -p $(BUILD_DIR)
#	$(CC) $(COMPILER_FLAGS) $(SOURCE_DIR)/main.cpp -o $(BUILD_DIR)/main.o 
#
#classes describing figures
#$(BUILD_DIR)/Figure.o: $(SOURCE_DIR)/Figure.cpp $(SOURCE_DIR)/Figure.hpp
#	@mkdir -p $(BUILD_DIR)
#	$(CC) $(COMPILER_FLAGS) $(SOURCE_DIR)/Figure.cpp -o $(BUILD_DIR)/Figure.o
#
#class of board
#$(BUILD_DIR)/Board.o: $(SOURCE_DIR)/Board.cpp $(SOURCE_DIR)/Board.hpp $(SOURCE_DIR)/Figure.hpp
#	@mkdir -p $(BUILD_DIR) 
#	$(CC) $(COMPILER_FLAGS) $(SOURCE_DIR)/Board.cpp -o $(BUILD_DIR)/Board.o
#
#class of game
#$(BUILD_DIR)/Game.o: $(SOURCE_DIR)/Game.cpp $(SOURCE_DIR)/Game.hpp $(SOURCE_DIR)/Figure.hpp $(SOURCE_DIR)/Board.hpp
#	@mkdir -p $(BUILD_DIR) 
#	$(CC) $(COMPILER_FLAGS) $(SOURCE_DIR)/Game.cpp -o $(BUILD_DIR)/Game.o
#
#class of main menu
#$(BUILD_DIR)/MainMenu.o: $(SOURCE_DIR)/MainMenu.cpp $(SOURCE_DIR)/MainMenu.hpp $(SOURCE_DIR)/Draw.hpp 
#	@mkdir -p $(BUILD_DIR) 
#	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(SOURCE_DIR)/MainMenu.cpp -o $(BUILD_DIR)/MainMenu.o
#
#$(BUILD_DIR)/Draw.o: $(SOURCE_DIR)/Draw.cpp $(SOURCE_DIR)/Draw.hpp 
#	@mkdir -p $(BUILD_DIR) 
#	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(SOURCE_DIR)/Draw.cpp -o $(BUILD_DIR)/Draw.o


#my implementation of button in SDL based a little on LazyFoo tutorials about SDL2
#$(BUILD_DIR)/Button.o: $(SOURCE_DIR)/SDL_Button.cpp $(SOURCE_DIR)/SDL_Button.hpp
#	@mkdir -p $(BUILD_DIR) 
#	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(SOURCE_DIR)/SDL_Button.cpp -o $(BUILD_DIR)/SDL_Button.o