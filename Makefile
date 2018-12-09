# Makefile
# this makefile is set up to compile two class implementations,
# as well as a main driver, and to link the three object files
#
CMP = g++
CLASS1 = circleBoard
MAIN = circleGame
EXEC = playCircle

$(EXEC): $(MAIN).o $(CLASS1).o
	$(CMP) $(MAIN).o $(CLASS1).o gfx_mac.o -I/opt/X11/include/ -L/opt/X11/lib/ -lX11 -std=c++11 -o $(EXEC)

$(CLASS1).o: $(CLASS1).h $(CLASS1).cpp
	$(CMP) -c $(CLASS1).cpp -I/opt/X11/include/ -std=c++11 -o $(CLASS1).o

$(MAIN).o: $(MAIN).cpp $(CLASS1).h
	$(CMP) -c $(MAIN).cpp -I/opt/X11/include/ -std=c++11 -o $(MAIN).o

clean:
	rm $(MAIN).o
	rm $(CLASS1).o
	rm $(EXEC)