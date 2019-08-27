#pragma once
#include "stdafx.h"
//#include "Vector.h"
//#include "Quaternion.h"
#include "global.h"
//#include "math_addition.h"
//#include <math.h>
//#include <iostream>
//#include <fstream> 
using namespace std;
//#include <algorithm>

//struct P_Q
//{
//	Vector P;
//	Quaternion Q;
//};

class Vector;



class P2P_
{
public:

	double	t_interval = 0.01;
	int Na = 0;
	Vector q0 = ZeroVector6;
	Vector qf = ZeroVector6;
	Vector qd0 = ZeroVector6;
	Vector qdf = ZeroVector6;
	Vector delta_q=ZeroVector6;

	Cubic_Coef cubic_coef={ ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6};
	Halfcos_Coef halfcos_coef= { ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,
		ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6 };

	Trapez_Coef trapez_coef = { ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6,ZeroVector6 };
	
	//Vector A = ZeroVector6;
	//Vector B = ZeroVector6;
	//Vector C = ZeroVector6;
	//Vector D = ZeroVector6;
	
	double tf;
	double tf_min_limit;

	double qd_percent=0.5;
	Vector qd= ZeroVector6;
	double qdd_percent = 0.8;
	Vector qdd = ZeroVector6;
	Vector qd_const = ZeroVector6;

	double t;
	Vector qt= ZeroVector6;
	Vector qdt= ZeroVector6;
	Vector qddt= ZeroVector6;
	enum TIMEorSPEED method ;
	enum P2Pmethod cht;

	//matrix qN;


public:
	//P2P();

	P2P_(Vector q0_1, Vector qf_1, enum P2Pmethod cht= halfcos, enum TIMEorSPEED method=speed, double tf_s=0.1,Vector qd0_1=ZeroVector6, Vector qdf_1=ZeroVector6, double qddp=0.8,double t_interval_=0.01);

	~P2P_();

	void P2P_cubic_coef_speed();
	void P2P_halfcos_coef_speed();
	void P2P_trapez_coef_speed();
	void P2P_cubic_coef_time();
	void P2P_halfcos_coef_time();
	void P2P_trapez_coef_time();
	//void Cubic_min_tf(Vector qd0, Vector qdf, Vector qdmax );
	void realtime(double t);
	void offline(double interval_out=0.01);


private:

};

