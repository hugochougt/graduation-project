main : main.cpp 
	g++ -ggdb `pkg-config --cflags` -o recognition main.cpp `pkg-config --libs opencv`

train : train.cpp 
	g++ -ggdb `pkg-config --cflags` -o train train.cpp `pkg-config --libs opencv`
