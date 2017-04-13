all: mobius
	
mobius: mobius.c
	gcc mobius.c -lm -O3 -o mobius
