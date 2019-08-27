#include "stdafx.h"
#include <stdio.h>
#include <math.h>

#include "matrix.h"
#include "vector.h"
#include "Quaternion.h"
#include "global.h"
#include "math_addition.h"
#include "P2P.h"
//#include <time.h>

using namespace std;

int main()
{
	Vector q0(0, 0, 0, 0, 0, 0);
	Vector qf(PI / 2, PI / 3, PI / 4, PI / 5, PI / 6, PI/2);

	Vector qd0(0, 0, 0, 0, 0, 0);
	Vector qdf(0, 0, 0, 0, 0, 0);
	P2P_ P1(q0,qf,trapez,time,10,qd0,qdf,1);
	//P1.realtime(0.4); 
	P1.offline();
	//double element = 1;
	//matrix mat_test(4,4);
	//for (int i = 1; i < 5; i++)
	//{
	//	for (int j = 1; j < 5; j++)
	//	{
	//		mat_test(i, j) = element;
	//		printf("this is %d row and %d col, data is %f\n\r", i, j, element);
	//		element++;
	//	}
	//}


	printf("\n\r"); _wsystem(_T("pause"));

}