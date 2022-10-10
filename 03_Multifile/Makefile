GENERATES = prog liboutput_static.a liboutput.so prog-a prog-so README
TRASH = *.o *~ o.* *.txt

%.o:	%.c
		gcc $< -c -o $@

all:	prog liboutput_static.a liboutput.so prog-a prog-so README

prog:	const.o fun.o prog.o
		gcc $^ -o $@

liboutput_static.a:	fun.o const.o
					ar -rcs $@ $^

liboutput.so:	CFLAGS=-fPIC
liboutput.so:	fun.o const.o
				gcc -shared $^ -o $@

prog-a:	prog.o liboutput_static.a
		gcc -L. -loutput_static $< -o $@

prog-so:	prog.o liboutput.so
			gcc -L. -loutput $< -o $@

README:	prog
		./$< 2> $@

distclean:	clean
			rm -rf $(GENERATES)

clean:
		rm -f $(TRASH)

test:	test-0 test-1 test-n

test-0:	prog prog-a prog-so
		make distclean
		make
		./prog 2> t0_prog.txt
		./prog-a 2> t0_prog-a.txt
		LD_LIBRARY_PATH=`pwd` ./prog-so 2> t0_prog-so.txt
		cmp t0_prog.txt t0_prog-a.txt
		cmp t0_prog.txt t0_prog-so.txt
		cmp t0_prog-a.txt t0_prog-so.txt

test-1:	prog prog-a prog-so
		make distclean
		make
		./prog A 2> t1_prog.txt
		./prog-a A 2> t1_prog-a.txt
		LD_LIBRARY_PATH=`pwd` ./prog-so A 2> t1_prog-so.txt
		cmp t1_prog.txt t1_prog-a.txt
		cmp t1_prog.txt t1_prog-so.txt
		cmp t1_prog-a.txt t1_prog-so.txt

test-n:	prog prog-a prog-so
		make distclean
		make
		./prog A B C 2> tn_prog.txt
		./prog-a A B C 2> tn_prog-a.txt
		LD_LIBRARY_PATH=`pwd` ./prog-so A B C 2> tn_prog-so.txt
		cmp tn_prog.txt tn_prog-a.txt
		cmp tn_prog.txt tn_prog-so.txt
		cmp tn_prog-a.txt tn_prog-so.txt
