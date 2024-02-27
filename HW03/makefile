all: clean compile run

compile: main.c util.c util.h 
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Compiling... "
	@gcc -o test main.c util.c


run:
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Running the tests...."
	@./test
	

clean:
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test