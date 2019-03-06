#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main()
{
	char tmp = 11;
	while(1) {
		double a = 0, b = 100, step = 0.001, x, f = 0, k = 0, one = 1;
		printf("Enter min numb\n");
		scanf_s("%lf", &a);
		printf("Enter  max numb\n");
		scanf_s("%lf", &b);
		printf("Enter  max step\n");
		scanf_s("%lf", &step);
		x = a;

		clock_t start, end;
		start = clock();
		while (x <= b)
		{
			f += pow(x, 4) - pow(x, 3) + pow(x, 2) - x + 1;
			x += step;
		}
		end = clock();
		printf("%f\n", f);
		printf("time c   %f\n", (double)(end - start) / CLK_TCK);

		x = a;
		f = 0;
		start = clock();
	
		_asm {
			finit
			fld b
			fld x 
			loop_start : 
			fcom 
				fstsw ax 
				and ah, 01000101b 
				jz loop_end 

				fld x 
				fmul x 
				fmul x
				fmul x

				fld x 
				fmul x
				fmul x

				fsub

				fld x 
				fmul x
				fadd

				fsub x
				fadd one

				fadd f 
				fstp f 

				fadd step 
				fst x
				jmp loop_start 
				loop_end :
			fwait 
		}
		end = clock(); 
		printf("%f\n", f); 
		printf("time asm %f\n", (double)(end - start) / CLK_TCK); // our tim
		printf("press f to break ore other key to continue\n");
		rewind(stdin);
		tmp = getchar();
		if (tmp == 'f')
			break;
	}
	return 0;
}