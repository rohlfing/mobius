all: mobius
	
mobius:
	gcc mobius.c -lm -O3 -o mobius
