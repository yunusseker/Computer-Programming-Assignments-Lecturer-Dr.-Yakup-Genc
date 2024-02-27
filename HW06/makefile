all: clear clean compile run

clear:
	clear

compile: main.c util.c util.h
	@echo "\n-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c util.c

run:
	@echo "\n-------------------------------------------"
	@echo "Running the tests...."
	@echo "\n================================================================================="
	./test
	@echo "\n================================================================================="
	@echo "Completed tests...."

clean:
	@echo "\n-------------------------------------------"
	@echo "Removing excess files..."
	@rm -f *.o
	@rm -f test
	@rm -f customer*.txt
	@rm -f *.out
	@rm -f *.s
