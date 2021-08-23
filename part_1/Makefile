OBJDIR = plots
mkdir_shell = $(shell if [ ! -d $(OBJDIR) ]; then echo "noexist"; else echo "exist"; fi)

ifeq ("$(mkdir_shell)", "noexist")
$(shell mkdir -p $(OBJDIR))
endif
$(info $(mkdir_shell))

main : main.cpp
	g++ -o main main.cpp
	./main
	xelatex work.tex
.PHONY : clean

clean :
	rm work.aux work.log