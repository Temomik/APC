/*
������� ���������� ����������, ������� ��������� �������� ���������� (� ������������ � ���������) ����� ���������:
1) � �������������� ������ MMX
2) �� ����������, ��� ������������� ������ MMX
3) �� ����� ��
����� ���������� ������ ���� �������� ����� ���������� � ��������� ��� ������� ������.
�������� ��������� ������ ������������ ����������� (�� �������� � ����������). 
���������� ������������ ��������� (1 ���) ���. 
������ ������ (��������) ������ ���������� ��������� � �������� ���.

������� 6:
���������� ����� ���� ��������� �������.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <conio.h>

using namespace std;

const int length_matrix = 16;			//����� ������� ������ ���� ������ 4
const int height_matrix = 4;
const int amount_reiteration = 1000000;

int main()
{
	setlocale (LC_ALL, "Russian");
	unsigned _int64 time_start, time_end, time_c, time_asm, time_asm_mmx;
	short matrix[height_matrix*length_matrix], matrix_MMX[4];
	short sum = 0;
	int i, j, k;

	cout << "�������: " <<endl;
	for ( i = 0; i < height_matrix; i++)
	{
		for (j = 0; j < length_matrix; j++)
		{
			matrix[i*length_matrix+j] = rand() % 10;				//��������� ���������� ������� ���������� �� 10
			cout << " " << matrix[i*length_matrix+j];			//����� �������
		}
		cout << endl;
	}

	time_start = __rdtsc();
	for (k = 0; k < amount_reiteration; k++)					//��

	{
		for ( sum = 0, i = 0; i < height_matrix; i++)	
		{
			for (j = 0; j < length_matrix; j++)
			{
				sum += matrix[i*length_matrix+j];
			}	
		} 
	}	
	time_end = __rdtsc();
	time_c = time_end - time_start;
	cout << "��������� ���������� ������� (�) = \t" << sum << endl;
	cout << "����� ���������� ������� (�) = \t" << time_c << endl << endl <<endl;

	sum = 0;
	
	time_start = __rdtsc();
	for (k = 0; k < amount_reiteration; k++)					//��������� ��� MMX
	{
		int counter=height_matrix*length_matrix;
		_asm
		{
			pusha
			xor esi, esi
			xor cx,cx
			loop1:
				add cx,matrix[esi]
				add esi, 2
				dec	counter
			jnz loop1
			mov sum, cx
			popa
		}
	}
	time_end = __rdtsc();
	time_asm = time_end - time_start;
	cout << "��������� ���������� ������� (asm ��� MMX) = \t" << sum << endl;
	cout << "����� ���������� ������� (asm ��� MMX) = \t" << time_asm << endl << endl;
	
	
	sum = 0;
	time_start = __rdtsc();
	for (k = 0; k < amount_reiteration; k++)					//��������� � MMX
	{
		int counter=height_matrix*length_matrix;
		_asm
		{
			pusha
			lea esi, [matrix]
			lea edi, [matrix_MMX] 
			pxor MM0, MM0
			pxor MM7, MM7
			movq MM7, [esi]
			loop2:
				add esi, 8
				movq MM0, [esi]
				paddsw MM7, MM0
				sub counter, 4
				cmp counter, 4
			jne loop2
			xor ecx,ecx
			movq [edi], MM7
			add ecx, [edi]
			add ecx, [edi+2]
			add ecx, [edi+4]
			add ecx, [edi+6]
			mov sum, cx
			popa
		}
	}
	_asm emms
	time_end = __rdtsc();
	time_asm_mmx = time_end - time_start;
	cout << "��������� ���������� ������� (asm � MMX) = \t" << sum << endl;
	cout << "����� ���������� ������� (asm � MMX) = \t" << time_asm_mmx << endl << endl;
	if (time_asm < time_asm_mmx && time_asm < time_c) cout << "��������� ��� MMX ��������� ������� ����!" <<endl;
	if (time_asm_mmx < time_asm && time_asm_mmx < time_c) cout << "��������� � MMX ��������� ������� ����!" <<endl;
	if (time_c < time_asm_mmx && time_c < time_asm) cout << "�� ��������� ������� ����!" <<endl;
	system ("pause");
	return 0;
}