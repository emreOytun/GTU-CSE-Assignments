all: clean compile run

compile: lab6.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test lab6.c

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./test
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test
