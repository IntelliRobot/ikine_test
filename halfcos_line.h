#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "Quaternion.h"
#include "global.h"
#include "math_addition.h"
#include <math.h>
#include "trajectory_plan.h"

class halfcos_line : public traj_plan
{
public:
	//Posi_Pose PPn;//��ǰλ��
	//Vector V_n;//��ǰĩ���ٶ�
	//Vector A_n;//��ǰĩ���ٶȼ��ٶ�
	//int Na;//��ֵ����
	//double qd_percent;//�����ٶȰٷֱ�
	
	//Ksew Ksew_n;//��ǰ�ؽ�����ֵ
	//Ksew Ksew_L;//ǰһ���ؽ�����ֵ

public:
	halfcos_line(Posi_Pose PP0, Posi_Pose PPf, enum TIMEorSPEED method=speed, double tf_vcaverage=0.1, double t_interval =0.01, double V0_1= 0, double Vf_1= 0);

	void realtime(double t);

	~halfcos_line();

private:

};

