# Makefile automatically generated by MakeMake for 044101 - HW3
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC) $(CFLAGS)
LIBS = 
OBJS = Course.o CS_Course.o EE_Course.o main.o Person.o StArray.o Student.o
RM = rm -f
# Create the executable
students: $(OBJS)
	$(CCLINK) -o students $(OBJS) $(LIBS)
# Create object files
Course.o: Course.cpp Course.h
	$(CCLINK) -c Course.cpp
CS_Course.o: CS_Course.cpp CS_Course.h Course.h
	$(CCLINK) -c CS_Course.cpp
EE_Course.o: EE_Course.cpp EE_Course.h Course.h
	$(CCLINK) -c EE_Course.cpp
main.o: main.cpp Proj.h StArray.h Student.h Person.h EE_Course.h Course.h CS_Course.h
	$(CCLINK) -c main.cpp
Person.o: Person.cpp Person.h
	$(CCLINK) -c Person.cpp
StArray.o: StArray.cpp StArray.h Student.h Proj.h Person.h EE_Course.h Course.h CS_Course.h
	$(CCLINK) -c StArray.cpp
Student.o: Student.cpp Student.h Proj.h Person.h EE_Course.h Course.h CS_Course.h
	$(CCLINK) -c Student.cpp

# Cleaning old files before new make
clean:
	$(RM) students *.o *.bak *~ "#"* core
