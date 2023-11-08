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
	class GrainDataLearnIn //ѧϰ
	{
	public:
		vector<float>      data;
	};
	class GrainDataLearnOut
	{
	public:
		float              minThreshold; //��С��ֵ
		float              maxThreshold; //�����ֵ
		int                GrainDataLearnResult; //1�ɹ� -1ʧ��
	};
	//�������ݸ�����������100
	DLLEXPORT_API void grainDataLearn(GrainDataLearnIn& grainDataLearnIn, GrainDataLearnOut& grainDataLearnOut);
}
#endif
