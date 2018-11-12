all:
	gcc-o start master.c procedure.c
	gcc -o prod prod.c procedure.c
	gcc -o cons cons.c procedure.c

start: master.c procedure.c header.h
	gcc -o start master.c procedure.c

prod: prod.c procedure.c header.h
	gcc -o prod prod.c procedure.c

cons: cons.c procedure.c header.h
	gcc -o cons cons.c procedure.c

clean: 
	rm -rf *.o
	rm -rf start


