obj = main.o kbd.o command.o display.o insert.o search.o file.o utils.o
edit : $(obj)
	cc -o edit $(obj)

main.o : defs.h

kbd.o : defs.h command.h

.PHONY : clean
clean:
	rm edit $(obj)
