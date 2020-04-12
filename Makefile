CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla
EXEC = biquadris
OBJECTS = textdisplay.o cell.o main.o controller.o grid.o levels.o block.o jblock.o oblock.o lblock.o sblock.o zblock.o tblock.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o iblock.o player.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
