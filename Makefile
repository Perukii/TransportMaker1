
all:
	g++ -o main main.cpp `pkg-config --libs --cflags gtkmm-3.0`
	./main
	rm -r main