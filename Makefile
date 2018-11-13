CFLAGS=-Wall -g -O0

LDFLAGS=-lm

Project3_main_bkhuu_207: Project3_main_bkhuu_207.o Project3_llist_bkhuu_207.o
	gcc -o Project3_main_bkhuu_207 Project3_main_bkhuu_207.o Project3_llist_bkhuu_207.o $(CFLAGS) $(LDFLAGS)

Project3_main_bkhuu_207.o: Project3_main_bkhuu_207.c Project3_llist_bkhuu_207.h
	gcc -c Project3_main_bkhuu_207.c $(CFLAGS) $(LDFLAGS)
       
Project3_llist_bkhuu_207.o: Project3_llist_bkhuu_207.c Project3_llist_bkhuu_207.h
	gcc -c Project3_llist_bkhuu_207.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f Project3_main_bkhuu_207.o
	rm -f Project3_llist_bkhuu_207.o
	rm -f Project3_main_bkhuu_207
