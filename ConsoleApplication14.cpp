// ConsoleApplication14.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <math.h> 
#include <iostream>
#include <thread>
#include <chrono>
#include<fstream>
using namespace std;
double x_start = 0.36089632, R = 3.86;
double* r = new double;
double* x = new double;
int ilosc = 40000;

char table1[10000];
char table2[10000];
char table3[10000];
char table4[10000];
int licznik = 0;
ofstream zapis("dane.txt");
//float *r1, float *r2, float *r3, float *r4, float* x, float x_prim, float r_prim//
void program(int k,int licznik, int alpha) {
	int c = 0;
	double r1;
	double y[4];
	double r_prim[4];
	while (c != alpha)
	{
		r1 = *r;
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j <= 2; j++) {
				x[0] = r1*x[0]*(1 - x[0]);
				x[0] = (x[0] * 1000) - floor(x[0] * 1000);

			}
			////??? co faktycznie jest to y ??
			y[i] = 3.86 + (x[0]*0.14);
		}
		//cout << x1<<" ";
		for (int i = 0; i < 3; i++) {
			if (x[0] >= 0.5) {
				r_prim[0] = (y[0] + y[2]) / 2;
				r_prim[1] = (y[0] + y[2]) / 2;
				r_prim[2] = (y[1] + y[3]) / 2;
				r_prim[3] = (y[1] + y[3]) / 2;
			}
			else {
				r_prim[0] = (y[0] + y[1] + y[2] + y[3]) / 4;
				r_prim[1] = (y[0] + y[1] + y[2] + y[3]) / 4;
				r_prim[2] = (y[0] + y[1] + y[2] + y[3]) / 4;
				r_prim[3] = (y[0] + y[1] + y[2] + y[3]) / 4;
				
			}
			for (i = 0 ; i < 4; i++) {
				for (int j = 0; j < 2; j++) {
					 x[0] = x[0] * r_prim[i] * (1 - x[0]);
					
					*x = (x[0] * 1000) - floor(x[0] * 1000);

				}
				///???
				y[i] = 3.86 + (x[0] + 0.14);
			}
			
			
		}
		*r = (y[0] + y[1] + y[2] + y[3]) / 4;
		
		c++;
	}
	//cout << *x << " ";
	/* (int)(table1[i]) ;
	zapis << (int)(table2[i]) + 128 << " ";
	zapis << (int)(table3[i]) + 128 << " ";
	zapis << (int)(table4[i]) + 128 << " ";
	if (k == 1) { zapis << (int)(*x * 256)  << " "; }
	if (k == 2) { zapis << (int)(*x * 256)  << " "; }
	if (k == 3) { zapis << (int)(*x * 256)  << " "; }
	if (k == 4) { zapis << (int)(*x * 256)  << " "; }
	*/
	//cout << table[licznik] << " ";
	//return x[0] * 256;

	if (k == 1) { table1[licznik] = (char)(*x * 256); }
	if (k == 2) { table2[licznik] = (char)(*x * 256); }
	if (k == 3) { table3[licznik] = (char)(*x * 256); }
	if (k == 4) { table4[licznik] = (char)(*x * 256); }

};


int main(int argc, char** argv)
{
	ilosc = atoi(argv[1]);
	int alpha = atoi(argv[2]);
	*r = 3.86;
	*x = x_start;

	//for(int i = 0; i <10; i++){

		for (int i = 0; i < ilosc/4; i++) {
			
			thread thr3(program, 3, i, alpha);
			thread thr4(program, 4, i, alpha);
			thread thr1(program, 1, i, alpha);
			thread thr2(program, 2, i, alpha);
			
			thr3.join();
			thr4.join();
			thr1.join();
			thr2.join();
			//cout << "done" << endl;

		}
	
		for (int i = 0; i < ilosc / 4; i++) {
			//cout << table1[i] << " ";
			zapis << (int)(table1[i]) + 128 << " ";
			zapis << (int)(table2[i]) + 128 << " ";
			zapis << (int)(table3[i]) + 128 << " ";
			zapis << (int)(table4[i]) + 128 << " ";
		}
		cout << "done " << /*((float)(i)/2)<<"%"<<*/endl;

	//}
	zapis.close();
		/*while (true)
		{

		}*/
	delete r, x;
    return 0;
}

