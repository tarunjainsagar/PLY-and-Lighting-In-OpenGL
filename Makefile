COMMAND = g++
PROG = *.cpp
OUTPUT = bunny
EXTRA = -lglut -lGL -lGLU
TITLE = MT2015120_TARUN_JAIN_ASSIGNMENT_2

all:
	$(COMMAND) $(PROG) -o $(OUTPUT) $(EXTRA)
	./$(OUTPUT) $(TITLE) &
	
clean: 
	rm -f $(OUTPUT) 
