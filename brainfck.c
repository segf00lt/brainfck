#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 30000
#define PROGSIZE 10000

char MEMORY[MEMSIZE];
char PROGRAM[PROGSIZE];

char *mem;
char *prog;

int main(int argc, char *argv[]) {
	FILE *fp;
	char *dp, *pp, *end;
	int i;

	if(argc != 2) {
		fprintf(stderr, "error: one file argument required\n");
		exit(1);
	}

	if(!(fp = fopen(argv[1], "r"))) {
		fprintf(stderr, "error: %s: no such file\n", argv[1]);
		exit(1);
	};

	dp = mem = MEMORY;
	pp = prog = PROGRAM;
	end = prog + fread(prog, 1, PROGSIZE, fp);

	fclose(fp);

	for(i = 0; pp < end; ++pp) {
		if(*pp == '[')
			++i;
		else if(*pp == ']')
			--i;
	}

	if(i != 0) {
		fprintf(stderr, "error: mismatched parenthisis\n");
		exit(1);
	}

	for(pp = prog; pp < end; ++pp) {
		switch(*pp) {
		case '>': ++dp; break;
		case '<': --dp; break;
		case '+': ++*dp; break;
		case '-': --*dp; break;
		case '.': putchar(*dp); break;
		case ',': *dp = getchar(); break;
		case '[':
			if(!*dp) {
				i = 1;
				while(i > 0) {
					++pp;
					if(*pp == '[')
						++i;
					else if(*pp == ']')
						--i;
				}
			}
			break;
		case ']':
			if(*dp) {
				i = 1;
				while(i > 0) {
					--pp;
					if(*pp == '[')
						--i;
					else if(*pp == ']')
						++i;
				}
			}
			break;
		}
	}
}
