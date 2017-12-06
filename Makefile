# Generic Makefile
# Note. Comments are preceded with #.
# A "Makefile" allows you to compile an entire project at once.
#
# Makefile for any project
#
# Sep. 21, 2015
#

# some settings...
# use the gnu C++ compiler program, g++
CCC = g++
# list all warnings
CCCFLAGS = -Wall -g -std=gnu++11 -lpthread -lX11

# all is called a target, after the colon you have dependencies
# ie. "the target all is dependent on the executables
all : RB-1

# the target <excecutable1> is dependent on the list of dependencies
# the line following  is the required executable (don't need to adjust it)
# Note: executable lines, ie. $(CCC) ..., must always begin with a tab.
# $^ = this/these dependencies
# $@ = this target

#colour2 : colour2.o
#	$(CCC) $(CCCFLAGS) -o $@ $^

# if there is more than one problem to do on an assignment you can compile
# all the questions at the same time
RB-1 : RB-1.o
	$(CCC) $(CCCFLAGS) -o $@ $^

# default rule compiling .cc to .o
# all .o file targets are dependent on the corresponding .cc files
# $< = the corresponding .cc file
%.o : %.cc
	$(CCC) -c $(CCCFLAGS) $<

# If you are using .h files you need to indicate that the .o file targets
# are dependent on corresponding .h files
# Ex. file.o : file.h
#<executable1 dependency1> : <what this target depends on> (usually .h files)


# Clean out your directory but keep executables with command "clean".  Gets rid 
# of files you don't need anymore
clean:
	rm -f *.o *~ *% *# .#*

# Clean out your directory including executables with command "clean-all"
clean-all: clean
	rm -f RB-1
