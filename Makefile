# Makefile for lab 10
# #   "make" or "make all : creates all three executables
# #   "make symbol" : creates the symbol executable
# #   (similar for "make bounce" and "make funanim")

circleGame: circleGame.cpp
	g++ circleboard.cpp circleGame.cpp gfx_mac.o -I/opt/X11/include/ -L/opt/X11/lib/ -lX11 -o circleGame

clean:
	rm circleGame

