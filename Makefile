BIN=points

CXX=g++
SHELL=/bin/sh
MKDIR_P = mkdir -p

# Optimization flags
CXXFLAGS=-O3 -Wall
# Debugging flags
# CXXFLAGS=-g -Wall

LIBS=

SRCS=\
$(BIN).cpp\
randmt.cpp

HDRS=\
rand.h\

OBJS=\
$(BIN).o\
randmt.o

all: $(BIN)

$(BIN): $(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(BIN)

clean:
	$(RM) *.o $(BIN) *.tar
