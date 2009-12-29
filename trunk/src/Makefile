SRCS := $(shell ls -1 *.cpp)
OBJS := $(SRCS:.cpp=.o)
CXXFLAGS := -g -Wall
EXE := ../supersnake
DEPENDENCIES := $(SRCS:.cpp=.d)


-include $(DEPENDENCIES)

all: $(OBJS)
	g++ -g -o $(EXE) $(OBJS) -lcurses

clean: 
	$(RM) -f *.o *.d

%.d:%.cpp
	g++ -MM $(CXXFLAGS) $< | sed 's/\(.*\).o:/\1.o \1.d:/' > $@
