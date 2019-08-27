#include "stdafx.h"
#include "P2P.h"
#include "vector.h"



P2P_::P2P_(Vector q0_1, Vector qf_1, enum P2Pmethod cht_1,enum TIMEorSPEED method_1 , double tf_s , Vector qd0_1 , Vector qdf_1 ,double qddp,double t_interval_)
{
	//成员变量赋值
	q0 = q0_1;
	qf = qf_1;
	qd0 = qd0_1;
	qdf = qdf_1;
	delta_q = qf - q0;
	cht = cht_1;
	method = method_1;
	t_interval = t_interval_;


		
	//指定速度方法，指定速度百分比值	
	if (0 < tf_s && tf_s<= 1 && method == speed) 
	{
		qd_percent = tf_s;
		qdd_percent = qddp;

		qd = qd_percent *Qd_max;
		qdd = qdd_percent*Qdd_max;

		switch (cht)
		{
		case cubic:
			P2P_cubic_coef_speed();
			break;
		case halfcos:
			P2P_halfcos_coef_speed();
			break;
		case trapez:
			P2P_trapez_coef_speed();
			break;
		default:
			break;
		}

		

	}

	// 指定时间方法，指定总时间。总时间如果过小，可能超速。
	if (tf_s>0 && method == time) 
	{
		tf = tf_s;
		qdd_percent = qddp;
		qdd = qdd_percent*Qdd_max;
		switch (cht)
		{
		case cubic:
			P2P_cubic_coef_time();
			break;
		case halfcos:
			P2P_halfcos_coef_time();
			break;
		case trapez:
			P2P_trapez_coef_time();
			break;
		default:
			break;
		}
		
	}
	
}

P2P_::~P2P_()
{}

void P2P_:: P2P_cubic_coef_speed()
{
	//根据各个轴速度算出最大时间。
	if (qd_percent > 0)
	{ 
		tf = Cubic_max_tf(delta_q, qd0, qdf, qd);
	}
	if (t_interval > 0)
	{
		Na = floor(tf / t_interval) + 1;
	}

	Cubic_spline_coef(q0,qf,qd0,qdf,tf,cubic_coef);

}

void P2P_::P2P_halfcos_coef_speed()
{
	if (qd_percent > 0)
	{
		Halfcos_coef(q0, qf, qd0, qdf, tf, speed, qd,qdd, halfcos_coef);

	}
	if (t_interval > 0)
	{
		Na = floor(tf / t_interval) + 1;
	}



}

void P2P_::P2P_trapez_coef_speed()
{
	if (qd_percent > 0)
	{
		Trapez_coef(q0, qf, qd0, qdf, speed, tf, qd, qdd, trapez_coef);
	}
	if (t_interval > 0)
	{
		Na = floor(tf / t_interval) + 1;
	}

}


void P2P_::P2P_cubic_coef_time()
{
	
	
	tf_min_limit = Cubic_max_tf( delta_q, qd0,  qdf, Qd_max);

	tf = tf > tf_min_limit ? tf : tf_min_limit;

	Cubic_spline_coef(q0, qf, qd0, qdf, tf,	cubic_coef);

	if (t_interval > 0)
	{
		Na = floor(tf / t_interval) + 1;
	}
}

void P2P_::P2P_halfcos_coef_time()
{
	Halfcos_coef(q0, qf, qd0, qdf, tf, time, qd,qdd, halfcos_coef);

	if (t_interval > 0)
	{
		Na = floor(tf / t_interval) + 1;
	}
}

void P2P_::P2P_trapez_coef_time()
{
	Trapez_coef(q0, qf, qd0, qdf, time, tf,qd, qdd,trapez_coef);
	if (t_interval > 0)
	{
		Na = floor(tf / t_interval) + 1;
	}
}


void P2P_::realtime(double t_now)
{
	t = t_now;//分数比例
	//if (t >= 0 && t <= 1 && method == speed)

	//{
	//	t = t*tf;

	//}

	if (t<=tf)
	{
		switch (cht)
		{
		case cubic:
			Cubic_spline_rt(qt, qdt, qddt, cubic_coef, t);
			break;
		case halfcos:
			Halfcos_rt(qt, qdt, qddt, halfcos_coef, t);
			break;
		case trapez:
			Trapez_rt(qt, qdt, qddt, trapez_coef, t);
			break;
		default:
			break;
		}
		
		
		
		

	
	}

}



void P2P_::offline(double interval_out)
{
	t_interval = interval_out;
	if (t_interval > 0)
	{
		Na = floor(tf / t_interval) + 1;
	}

	//qN(N, 6);

	ofstream outFile; //输出文件流(输出到文件)

	outFile.open("D:\\qN.csv", ios::out);//打开模式可省略

	for (int i = 0; i < Na; i++)

	{
		double tt = i*t_interval;
		realtime(tt);

		outFile << i << ',' << qt(1) << ',' << qt(2) << ',' << qt(3) << ',' << qt(4)
			<< ',' << qt(5) << ',' << qt(6) << endl;
	}
	outFile.close();

	outFile.open("D:\\qddN.csv", ios::out);//打开模式可省略

	for (int i = 0; i < Na; i++)

	{
		double tt = i*t_interval;
		realtime(tt);

		outFile << i << ',' << qddt(1) << ',' << qddt(2) << ',' << qddt(3) << ',' << qddt(4) 
			<< ',' << qddt(5) << ',' << qddt(6) << endl;
	}
	outFile.close();

	outFile.open("D:\\qdN.csv", ios::out);//打开模式可省略

	for (int i = 0; i < Na; i++)

	{
		double tt = i*t_interval;
		realtime(tt);

		outFile << i << ',' << qdt(1) << ',' << qdt(2) << ',' << qdt(3) << ',' << qdt(4)
			<< ',' << qdt(5) << ',' << qdt(6) << endl;
	}
	outFile.close();


}