FLAG = -Wall -Werror -Wextra
FILES=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o, ${FILES})
GCO=--coverage
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	GFLAGS = -lcheck -lpthread -lrt -lm -lsubunit
endif

ifeq ($(UNAME), Darwin)
	GFLAGS = -lcheck
endif

all: clean install dvi run

install: uninstall
	mkdir build
	cd 3D_Viewer_v1_front/ && qmake && make && make clean && rm Makefile && cd ..
	mv 3D_Viewer_v1_front/3D_Viewer_v1_front.app build/
	
uninstall:
	rm -rf build

run:
	@open ./build/3D_Viewer_v1_front.app

dvi: 
	@open ./info_3d_viewer.md

dist: 
	@mkdir C8_3DViewer_v1.0-1/ 
	@mkdir C8_3DViewer_v1.0-1/src 
	cp -R 3D_Viewer_v1_front test_3d_Viewer *.c *.h Makefile C8_3DViewer_v1.0-1/src 
	tar cvzf C8_3DViewer_v1.0-1.tgz C8_3DViewer_v1.0-1/ 
	rm -rf C8_3DViewer_v1.0-1

test: clean
	@gcc $(FLAG) -g -o test test_3d_Viewer/*.c $(FILES) $(GFLAGS)
	@./test

gcov_report: clean
	@gcc $(FLAG) -o test ./test_3d_Viewer/*.c $(FILES) $(GCO) $(GFLAGS)
	./test
	lcov --capture --directory . --output-file=coverage.info
	genhtml coverage.info --output-directory=res
	open ./res/index.html

clean:
	rm -rf main *.dSYM test *.gcda *.gcno *.info ./res 
	rm -rf build/
	rm -rf *.tgz
	clear

leaks: 
	@leaks -atExit -- ./test

valgrind:
	@valgrind --tool=memcheck --leak-check=yes ./test

style: 
	cp ../materials/linters/.clang-format .
	clang-format -n *.c  *.h ./test_3d_Viewer/*.c *.h ./3D_Viewer_v1_front/*.cpp *.h
	rm -rf .clang-format
	