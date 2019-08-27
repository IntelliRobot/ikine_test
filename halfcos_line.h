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
	//Posi_Pose PPn;//当前位置
	//Vector V_n;//当前末端速度
	//Vector A_n;//当前末端速度加速度
	//int Na;//插值步数
	//double qd_percent;//最大角速度百分比
	
	//Ksew Ksew_n;//当前关节奇异值
	//Ksew Ksew_L;//前一个关节奇异值

public:
	halfcos_line(Posi_Pose PP0, Posi_Pose PPf, enum TIMEorSPEED method=speed, double tf_vcaverage=0.1, double t_interval =0.01, double V0_1= 0, double Vf_1= 0);

	void realtime(double t);

	~halfcos_line();

private:

};

