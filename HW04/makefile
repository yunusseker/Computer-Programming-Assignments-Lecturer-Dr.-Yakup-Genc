all: clean compile run

compile: main.c util.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o program main.c

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./program
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f program
