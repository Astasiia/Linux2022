all:	range

range:
		gcc -g -O0 range.c -o range

clean:
		rm -f result*
		rm -f range

test:
		make clean
		make
		gdb ./range -x gdb1.py | grep '@@@' > result1.txt
		cmp result1.txt check1.txt
		gdb ./range -x gdb2.py | grep '@@@' > result2.txt
		cmp result2.txt check2.txt
