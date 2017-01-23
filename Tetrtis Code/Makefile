CXX = g++-5
CXXFLAGS = -std=c++14 -Werror=vla
EXEC = quadris
OBJECTS = main.o Level.o Level0.o Level1.o Level2.o Level3.o Level4.o Grid.o Row.o Cell.o Observer.o Subject.o DroppedBlock.o TextDisplay.o GraphicsDisplay.o Trie.o

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

main.o: main.cc
	${CXX} ${CXXFLAGS} -c main.cc

Level.o: Level.cc Level.h
	${CXX} ${CXXFLAGS} -c Level.cc

Level0.o: Level0.cc Level0.h
	${CXX} ${CXXFLAGS} -c Level0.cc

Level1.o: Level1.cc Level1.h
	${CXX} ${CXXFLAGS} -c Level1.cc

Level2.o: Level2.cc Level2.h
	${CXX} ${CXXFLAGS} -c Level2.cc

Level3.o: Level3.cc Level3.h
	${CXX} ${CXXFLAGS} -c Level3.cc

Level4.o: Level4.cc Level4.h
	${CXX} ${CXXFLAGS} -c Level4.cc

Grid.o: Grid.cc Grid.h
	${CXX} ${CXXFLAGS} -c Grid.cc

Row.o: Row.cc Row.h
	${CXX} ${CXXFLAGS} -c Row.cc

Cell.o: Cell.cc Cell.h
	${CXX} ${CXXFLAGS} -c Cell.cc

Observer.o: Observer.cc Observer.h
	${CXX} ${CXXFLAGS} -c Observer.cc

Subject.o: Subject.cc Subject.h
	${CXX} ${CXXFLAGS} -c Subject.cc

DroppedBlock.o: DroppedBlock.cc DroppedBlock.h
	${CXX} ${CXXFLAGS} -c DroppedBlock.cc

TextDisplay.o: TextDisplay.cc TextDisplay.h
	${CXX} ${CXXFLAGS} -c TextDisplay.cc

GraphicsDisplay.o: GraphicsDisplay.cc GraphicsDisplay.h
	${CXX} ${CXXFLAGS} -c GraphicsDisplay.cc

Trie.o: Trie.cc Trie.h
	${CXX} ${CXXFLAGS} -c Trie.cc

clean:
	rm ${OBJECTS} ${EXEC}
