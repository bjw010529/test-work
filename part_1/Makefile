OBJDIR = plots
mkdir_shell = $(shell if [ ! -d $(OBJDIR) ]; then echo "noexist"; else echo "exist"; fi)

ifeq ("$(mkdir_shell)", "noexist")
$(shell mkdir -p $(OBJDIR))
endif
$(info $(mkdir_shell))

main : main.cpp work.tex work.bib
	g++ -o main main.cpp
	./main
	xelatex work.tex
	bibtex work.aux
	xelatex work.tex
	xelatex work.tex
.PHONY : clean

clean :
	