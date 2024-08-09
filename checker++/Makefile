.PHONY: all

CPP=clang++
BOOST_INCLUDE=/opt/homebrew/Cellar/boost/1.85.0/include/

all: checker.cpp Makefile
	$(CPP) -I$(BOOST_INCLUDE) -std=c++17 -Wall -pedantic -O2 checker.cpp -o checker
