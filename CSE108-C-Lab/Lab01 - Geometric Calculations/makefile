all: clear clean compile run

compile: main.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -c main.c
	@gcc main.c -o main.out

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	@./main.out
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f *main.o
	@rm -f *main.out
	
clear:
	@echo "-----------------------------"
	@echo "Terminal is cleaning..."
	clear
	
