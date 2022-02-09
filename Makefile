all:
	g++ src/main.cpp `pkg-config gtkmm-3.0 --libs --cflags` -std=c++17 -o tartic
