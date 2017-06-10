###############################################################################
# compiler setting
###############################################################################
CC       = gcc
CXX      = g++
CFLAGS   = -g -Wall
CXXFLAGS = $(CFLAGS) -Weffc++
LIBS     = -lm -lpthread
INCPATH  =
DIR     = $(shell pwd)

###############################################################################
# source files setting
###############################################################################
C_SOURCES   = $(shell find . -name "*.c")
CXX_SOURCES = $(shell find . -name "*.cpp")
C_OBJS      = $(patsubst %.c,%.o,$(wildcard $(C_SOURCES)))
CXX_OBJS    = $(patsubst %.cpp,%.o,$(wildcard $(CXX_SOURCES)))
OBJS        = $(C_OBJS) $(CXX_OBJS)
EXEC      = $(shell basename $(DIR))

###############################################################################
.PHONY : clean clean_all
###############################################################################
all: client

%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) $< -o $@

server: server.o
	$(CXX) $< -o $@ $(LIBS)

client: client.o
	$(CXX) $< -o $@ $(LIBS)
###############################################################################
clean:
	@rm -vfr $(OBJS)
clean_all: clean
	@rm -vfr $(EXEC)
###############################################################################

