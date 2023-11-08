#ifndef	COUNTGRAIN_H
#define	COUNTGRAIN_H

#ifdef ALGORITHM_EXPORTS
#define DLLEXPORT_API extern "C" _declspec(dllexport)
#else
#define DLLEXPORT_API extern "C" _declspec(dllimport)
#endif
#include "XVBase.h"

namespace XVL
{
	class GrainDataLearnIn //学习
	{
	public:
		vector<float>      data;
	};
	class GrainDataLearnOut
	{
	public:
		float              minThreshold; //最小阈值
		float              maxThreshold; //最大阈值
		int                GrainDataLearnResult; //1成功 -1失败
	};
	//输入数据个数不能少于100
	DLLEXPORT_API void grainDataLearn(GrainDataLearnIn& grainDataLearnIn, GrainDataLearnOut& grainDataLearnOut);
}
#endif
