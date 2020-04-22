CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla 
EXEC = biquadris
OBJECTS = textdisplay.o cell.o graphics.o window.o main.o command.o controller.o grid.o levels.o block.o jblock.o oblock.o lblock.o sblock.o zblock.o tblock.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o levelfive.o levelsix.o iblock.o player.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
