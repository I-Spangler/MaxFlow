#
# makefile
# ingrid, 2017-05-21 20:09
#

all:
	gcc *.c -Wall -Wextra -Werror -std=c99 -pedantic -g -o TP1

clean:
	rm -f TP1 *.o 

# vim:ft=make
#
