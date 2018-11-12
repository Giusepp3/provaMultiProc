start: master.o prod.o cons.o procedure.o
	gcc -o start master.o

master.o: master.c procedure.c header.h 
	gcc -c master.c procedure.c

cons.o: procedure.c cons.c header.h
	gcc -c cons.c procedure.c

prod.o: prod.c procedure.c header.h
	gcc -c prod.c procedure.c

procedure.o: procedure.c header.h
	gcc -c procedure.c
	
clean: 
	rm -rf *.o
	rm -rf start


