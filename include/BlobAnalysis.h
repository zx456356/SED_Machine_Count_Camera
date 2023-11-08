 //#pragma once
#ifndef BLOBANALYSIS_H
#define BLOBANALYSIS_H
#include "XVBase.h"
#include <string>
namespace XVL{
	//��������ö��
	enum XVClassifyFeature{
		XCF_Area,           //���
		XCF_Circularity_boundingCircle,//��Բ��_���Բ
		XCF_Circularity_radius,    //��Բ��_�뾶
		XCF_Convexity,             //͹��
		XCF_Elogation,        //������
		XCF_MassCenterX,     //����x
		XCF_MassCenterY,     //����y
		XCF_MajorAxis,       //���᳤
		XCF_MinorAxis,       //���᳤
		XCF_Orientation,     //����
		XCF_Rectangularity,  //���ζ�
		XCF_UpperLeftX,//���Ͻ�X
		XCF_UpperLeftY//���Ͻ�Y
	};

	struct XVBlobPreIn{
		XVImage *inImage;//����ͼ��
		XVRegion inRoi;//����ѧϰ���򣬲���Ϊ��
		//�������������������ѡ���ѡ����(Ĭ��)����Ҷ���Сֵ��Ϊ140�����ֵ��Ϊ255����ѡ�񰵣���Ҷ���Сֵ��Ϊ0�����ֵ��Ϊ130��
		float inMinThre;//�Ҷ�ֵ��Сֵ
		float inMaxThre;//�Ҷ�ֵ���ֵ
	};
	struct XVBlobPreOut{
		vector<XVRegion> outRegions;//�����������
		float outTime;//ʱ��
	};
	//�������ƣ��ߵ㶨λԤ����
	__declspec(dllexport)int blobPre(XVBlobPreIn &XVBlobPre_In, XVBlobPreOut &XVBlobPre_Out);
	//����0�� Ԥ����ɹ�
	//����-1��Ԥ����ʧ��(����ͼ��Ϊ��)
	//����-2��Ԥ����ʧ��(ѧϰ����Ϊ��)
	//����-3��Ԥ����ʧ��(��ֵ��ִ��ʧ��)
	//����-4, Ԥ����ʧ��(��ͨ�Էָ�ʧ��)
	//����-5��Ԥ����ʧ��(�׳��쳣)

	struct XVBlobLearnIn{//�ߵ�ѧϰ����
		vector<XVRegion> inRegions;//������������
		vector<XVClassifyFeature> inFeatures;//ѧϰ������Ϣ������Ϊ��
		int inSelectedIndex;//ѡ�������������Ĭ��0
	};
	struct XVBlobLearnOut{//�ߵ�ѧϰ���
		XVRegion outRegion;//ѧϰ�õ�������
		vector<XVClassifyFeature> outFeatures;//ѧϰ����
		vector<float> outValues;//��������ֵ
		XVPoint2D outCenter;//ѧϰ������������
		float outTime;//ʱ��
	};
	//�������ƣ��ߵ�ѧϰ
	__declspec(dllexport)int blobPatternLearn(XVBlobLearnIn &XVBlobLearn_In, XVBlobLearnOut &XVBlobLearn_Out);
	//����0�� ģ��ѧϰ�ɹ�
	//����-1��ģ��ѧϰʧ��(������������Ϊ��)
	//����-2��ģ��ѧϰʧ��(ѧϰ����Ϊ��)
	//����-3��ģ��ѧϰʧ��(�׳��쳣)
	
	struct XVBlobMatchIn{//�ߵ㶨λ����
		XVImage *inImage;//����ͼ��
		XVRegion inSearchRoi;//��������Ĭ��ȫͼ
		XVBlobLearnOut inModel;//Blobģ��
		//�������������������ѡ���ѡ����(Ĭ��)����Ҷ���Сֵ��Ϊ140�����ֵ��Ϊ255����ѡ�񰵣���Ҷ���Сֵ��Ϊ0�����ֵ��Ϊ130��
		float inThreMin;//�Ҷ���Сֵ
		float inThreMax;//�Ҷ����ֵ
		float inSimilarity;//���ƶ���ֵ�����������Ĭ��ֵ0.8
		bool inMatchMulti;//�Ƿ�����������������������˵���������ѡ��true/false��Ĭ��false
	};
	struct XVBlobMatchOut{//�ߵ㶨λ���
		vector<XVRegion> outRegions;//ƥ��õ�������
		vector<float> outScores;//�÷�
		vector<XVPoint2D> outCenters;//��������
		vector<vector<float>> outValues;//���������Ӧ������ֵ
		float outTime;//ʱ��
	};
	//��������:�ߵ㶨λ
	__declspec(dllexport)int blobPatternMatch(XVBlobMatchIn &XVBlobMatch_In, XVBlobMatchOut &XVBlobMatch_Out);
	//����0��ģ��ƥ��ɹ�
	//����-1��ģ��ƥ��ʧ��(ͼ��Ϊ��)
	//����-2��ģ��ƥ��ʧ��(��ֵ��ʧ��)
	//����-3��ģ��ƥ��ʧ�ܣ�δ�ҵ�Ŀ��)
	//����-4��ģ��ƥ��ʧ��(�׳��쳣)
	//����-5��ģ��ƥ��ʧ��(��ͨ�Էָ�ʧ��)
	//����-6��ģ��ƥ��ʧ��(ģ��Ϊ��)

	/*ͨ���㷨*/
	enum XVImageType{//ͼ������
		RGB,
		HSI,
		HSL,
		HSV
	};



	struct XVInfoOfChannel{//ͨ����Ϣ
		float outMinimumValue;//��С����ֵ
		XVPoint2D outMinimumLocation;//��С����ֵ��λ��
		float outMaximumValue;//�������ֵ
		XVPoint2D outMaximumLocation;//�������ֵ��λ��
		float outAverageValue;//ƽ������ֵ
		float outSumValue;//����ֵ�ܺ�
		float outStdValue;//����ֵ��׼��
	};



	struct XVThresholdImageToRegionMonoIn{
		XVImage *inImage; //����ͼ��
		XVRegion inRegion;//��������ͼ������(Բ�����ε�)������������ROI������������������Ƿ�Ϊ��
		XVCoordinateSystem2D inAlignment;//����ֲ�����ϵ
		float inMin;    //�Ҷ���Сֵ�����������Ĭ��ֵ0
		float inMax;    //�Ҷ����ֵ�����������Ĭ��ֵ255
	};
	struct XVThresholdImageToRegionMonoOut{
		XVRegion outRegion;//��ֵ������
		float outTime;//�㷨����ʱ��,��λms
	};
	//�������ƣ��Ҷ���ֵ��
	__declspec(dllexport)int XVThresholdImageToRegionMono(XVThresholdImageToRegionMonoIn & XVThresholdImageToRegionMono_In, XVThresholdImageToRegionMonoOut & XVThresholdImageToRegionMono_Out);
	//����0���㷨���гɹ�
	//����-1��ͼ������Ϊ��
	//����-2����������Ҷ�ͼ��



	struct XVRegionAreaIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionAreaOut{
		int outArea;//������
		float outTime;//�㷨����ʱ��,��λms 
	};
	//�������ƣ��������
	__declspec(dllexport)int XVRegionArea(XVRegionAreaIn & XVRegionArea_In, XVRegionAreaOut & XVRegionArea_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��



	struct XVRegionCenterIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionCenterOut{
		XVPoint2D outCenter;//�������
		float outTime;//�㷨����ʱ��,��λms
	};
	//�������ƣ���������
	__declspec(dllexport)int XVRegionCenter(XVRegionCenterIn & XVRegionCenter_In, XVRegionCenterOut & XVRegionCenter_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��



	struct XVRegionRectangularityIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionRectangularityOut{
		float outRectangularity;//������ζ�
		float outTime;//�㷨����ʱ��,��λms
	};
	//�������ƣ�������ζ�
	__declspec(dllexport)int XVRegionRectangularity(XVRegionRectangularityIn & XVRegionRectangularity_In, XVRegionRectangularityOut & XVRegionRectangularity_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��



	struct XVRegionBoundingBoxIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionBoundingBoxOut{
		XVBox outBox;//�����ӿ�
		XVPoint2D outLeftTop;//�����ӿ����Ͻ�
		XVPoint2D outRightDown;//�����ӿ����½�
		float outTime;//�㷨����ʱ��,��λms
	};
	//�������ƣ�������ӿ�
	__declspec(dllexport)int XVRegionBoundingBox(XVRegionBoundingBoxIn & XVRegionBoundingBox_In, XVRegionBoundingBoxOut & XVRegionBoundingBox_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��



	struct XVSplitRegionToBlobsIn{
		XVRegion inRegion;//��������
		int inNeighborhood;//��ͨ�ԡ���������������˵���ֻ��4��8����ѡ�Ĭ��Ϊ8
	};
	struct XVSplitRegionToBlobsOut{
		vector<XVRegion> outRegions;//����ָ�������
		float outTime;//�㷨����ʱ��,��λms
	};
	//�������ƣ��ָ�����
	__declspec(dllexport)int XVSplitRegionToBlobs(XVSplitRegionToBlobsIn & XVSplitRegionToBlobs_In, XVSplitRegionToBlobsOut & XVSplitRegionToBlobs_Out);
	//����0���㷨���гɹ�
	//����-1,��������Ϊ��



	struct XVClassifyRegionsIn{
		vector<XVRegion> inRegions;//��������
		XVClassifyFeature inFeature;//������������������������˵�����11��ѡ�Ĭ�����
		float inMin;//������Сֵ
		float inMax;//�������ֵ
	};
	struct XVClassifyRegionsOut{
		vector<XVRegion> outAcceptedRegions; //��������������
		vector<XVRegion> outRejectedRegions; //����������������
		vector<float> outAcceptedValues;    //�������������ֵ
		vector<float> outRejectedValues;    //�ܾ����������ֵ
		float outTime;//�㷨����ʱ��
	};
	//�������ƣ��������
	__declspec(dllexport)int XVClassifyRegions(XVClassifyRegionsIn &XVClassifyRegions_In, XVClassifyRegionsOut &XVClassifyRegions_Out);
	//����0���㷨���гɹ�
	//����-1,��������Ϊ��


	//Բ�ζ�=�������/Բ�������Բ��������һ����ͬ������������:
	enum XVCircularityMeasure{
		radius,//�뾶
		boundingCircle,//���Բ
		perimeter//�ܳ�
	};
	struct XVRegionCircularityIn{
		XVRegion inRegion;//��������
		XVCircularityMeasure inMeasure;//������ʽ��������������˵���ֻ��3��ѡ�Ĭ��ֵradius
	};
	struct XVRegionCircularityOut{
		float outCircularity;//�����Բ��
		float outTime;//����ʱ��,ms
	};
	//�������ƣ�����Բ��
	__declspec(dllexport)int XVRegionCircularity(XVRegionCircularityIn & XVRegionCircularity_In, XVRegionCircularityOut & XVRegionCircularity_Out);
	//����0���㷨���гɹ�
	//����-1,��������Ϊ��



	struct XVRegionConvexHullIn{
		XVRegion inRegion;//��������
		bool inFlag;//���������ʶ������������������˵���ֻ��true��false����ѡ�Ĭ��Ϊfalse
	};
	struct XVRegionConvexHullOut{
		XVPath outHull;//���͹��
		float outHullArea;//���͹�����
		float outTime;//����㷨����ʱ��
	};
	//�������ƣ�����͹��
	__declspec(dllexport)int XVRegionConvexHull(XVRegionConvexHullIn & XVRegionConvexHull_In, XVRegionConvexHullOut & XVRegionConvexHull_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��



	struct XVRegionBoundingCircleIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionBoundingCircleOut{
		XVCircle2D outCircle;//�����С���Բ
		float outTime;//����㷨����ʱ��
	};
	//�������ƣ��������Բ
	__declspec(dllexport)int XVRegionBoundingCircle(XVRegionBoundingCircleIn & XVRegionBoundingCircle_In, XVRegionBoundingCircleOut & XVRegionBoundingCircle_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��



	struct XVRegionSecondOrderMomentsIn{
		XVRegion inRegion;//��������
		bool inCentral;//�Ƿ����Ļ�,��������������˵�����true/false����ѡ�Ĭ��false
		bool inNormalized;//�Ƿ��һ��,��������������˵�����true/false����ѡ�Ĭ��false
	};
	struct XVRegionSecondOrderMomentsOut{
		float out_11;//���׾�_11
		float out_02;//���׾�_02
		float out_20;//���׾�_20
		float outTime;//����㷨����ʱ��
	};
	//�������ƣ�������׾�
	__declspec(dllexport)int XVRegionSecondOrderMoments(XVRegionSecondOrderMomentsIn & XVRegionSecondOrderMoments_In, XVRegionSecondOrderMomentsOut & XVRegionSecondOrderMoments_Out);                                 //������׾�
	//����0�����гɹ�
	//����-1����������Ϊ��



	struct XVRegionElogationIn {
		XVRegion inRegion;//��������
	};
	struct XVRegionElogationOut{
		float outElogation;//����������
		float outTime;//����㷨����ʱ��
	};
	//�������ƣ�����������
	__declspec(dllexport)int XVRegionElogation(XVRegionElogationIn & XVRegionElogation_In, XVRegionElogationOut & XVRegionElogation_out);                                                                             //����������
	//����0�����гɹ�
	//����-1����������Ϊ��



	struct XVRegionEllipticAxisIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionEllipticAxisOut{
		float outMajorAxis;//�����Ч��Բ���᳤
		float outMinorAxis;//�����Ч��Բ���᳤
		float outTime;//����㷨����ʱ��
	};
	//�������ƣ������Ч��Բ
	__declspec(dllexport)int XVRegionEllipticAxis(XVRegionEllipticAxisIn &XVRegionEllipticAxis_In, XVRegionEllipticAxisOut &XVRegionEllipticAxis_Out);                                 //������Բ�ĳ����ᣬ����Բ�������������ͬ��һ�ס����׾�
	//����0�����гɹ�
	//����-1����������Ϊ��



	struct XVRegionOrientationIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionOrientationOut{
		float outOrientation;//����Ƕȣ���λ����(��)
		float outTime;//����㷨����ʱ��
	};
	//�������ƣ�����Ƕ�
	__declspec(dllexport)int XVRegionOrientation(XVRegionOrientationIn & XVRegionOrientation_In, XVRegionOrientationOut & XVRegionOrientation_Out);                                                                    //����������Ƕ�
	//����0�����гɹ�
	//����-1����������Ϊ��



	struct XVAlignPointIn{
		XVPoint2D inPoint;//�����
		XVCoordinateSystem2D inAlignment;//����ֲ�����ϵ��Ĭ�ϲ�ʹ��(XVOptionalType::NUL)
		bool inInverse;//�Ƿ��л�����任�����������Ĭ��ֵfalse
	};
	struct XVAlignPointOut{
		XVPoint2D outPoint;//�������ϵ�����ĵ�
		float outTime;//���ʱ��
	};
	//�������ƣ���任
	__declspec(dllexport)int XVAlignPoint(XVAlignPointIn &XVAlignPoint_In, XVAlignPointOut &XVAlignPoint_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��



	struct XVAlignRegionIn{
		XVRegion inRegion;//��������
		XVCoordinateSystem2D inAlignment;//����ֲ�����ϵ��Ĭ�ϲ�ʹ��(XVOptionalType::NUL)
		bool inInverse;//�Ƿ��л�����任�����������Ĭ��ֵfalse
		int inWidth;//����֡��(��Ϊͼ����)
		int inHeight;//����֡�ߣ���Ϊͼ��߶�)
	};
	struct XVAlignRegionOut{
		XVRegion outRegion;//�������ϵ����������
		float outTime;//���ʱ��
	};
	//�������ƣ�����任
	__declspec(dllexport)int XVAlignRegion(XVAlignRegionIn &XVAlignRegion_In, XVAlignRegionOut &XVAlignRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(��������Ϊ��)



	struct XVRegionIntersectionIn{
		XVRegion inRegion1;//��������1������������Ƿ�Ϊ��
		XVRegion inRegion2;//��������2������������Ƿ�Ϊ��
	};
	struct XVRegionIntersectionOut{
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ����򽻼�
	__declspec(dllexport)int XVRegionIntersection(XVRegionIntersectionIn &XVRegionIntersection_In, XVRegionIntersectionOut &XVRegionIntersection_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��



	struct XVRegionUnionIn{
		XVRegion inRegion1;//��������1������������Ƿ�Ϊ��
		XVRegion inRegion2;//��������2������������Ƿ�Ϊ��
	};
	struct XVRegionUnionOut{
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ����򲢼�
	__declspec(dllexport)int XVRegionUnion(XVRegionUnionIn &XVRegionUnion_In, XVRegionUnionOut &XVRegionUnion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��



	struct XVRegionDifferenceIn{
		XVRegion inRegion1;//��������1������������Ƿ�Ϊ��
		XVRegion inRegion2;//��������2������������Ƿ�Ϊ��
	};
	struct XVRegionDifferenceOut{
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ�����
	__declspec(dllexport)int XVRegionDifference(XVRegionDifferenceIn &XVRegionDifference_In, XVRegionDifferenceOut &XVRegionDifference_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��



	struct XVRegionComplementaryIn{
		XVRegion inRegion;//������������������Ƿ�Ϊ��
	};
	struct XVRegionComplementaryOut{
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ����򲹼�
	__declspec(dllexport)int XVRegionComplementary(XVRegionComplementaryIn &XVRegionComplementary_In, XVRegionComplementaryOut &XVRegionComplementary_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��



	enum XVMorphType{//��̬ѧ��������
		Dilate,//����
		Erode,//��ʴ
		Open,//������
		Close,//�ղ���
	};
	enum XVMorphShape{//��̬ѧ������
		Rect,//����
		Cross,//������
	};
	struct XVRegionMorphIn{
		XVRegion inRegion;//��������
		XVMorphType inMorphType;//��̬ѧ�������ͣ����������Ĭ��ֵDilate
		XVMorphShape inKernel;//�����ͣ����������Ĭ��ֵRect
		int inRadiusX;//�˿�һ�룬���������Ĭ��ֵ1����Χ[0,999999]
		int inRadiusY;//�˸�һ�룬���������Ĭ��ֵ1����Χ[0,999999]
	};
	struct XVRegionMorphOut{
		XVRegion outRegion;//�������
		float outTime;//ʱ��
	};
	//�������ƣ�������̬�任
	__declspec(dllexport)int XVRegionMorph(XVRegionMorphIn &XVRegionMorph_In, XVRegionMorphOut &XVRegionMorph_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(��������Ϊ��)



	struct XVSortRegionIn{
		vector<XVRegion> inRegions;
		XVClassifyFeature inFeature;//�������������������Ĭ��ֵXVClassifyFeature::Area(���)
		bool inAscending;//�������,���������Ĭ��ֵtrue(����)
	};
	struct XVSortRegionOut{
		vector<XVRegion> outSortedRegions;//����������
		vector<float> outValues;//���������Ķ�Ӧ����ֵ
		float outTime;//ʱ��
	};
	//�������ƣ���������
	__declspec(dllexport)int XVSortRegions(XVSortRegionIn &XVSortRegion_In, XVSortRegionOut &XVSortRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(��������Ϊ��)



	struct XVMonoImageStatisticsIn{
		XVImage *inImage;//����ͼ��
		XVRegion inRoi;//����Ȥ��������������Ƿ�Ϊ��
	};
	struct XVMonoImageStatisticsOut{
		XVInfoOfChannel outInfo;//������Ϣ
		float outTime;//ʱ��
	};
	//�������ƣ��Ҷ�ͼ��ͳ��
	__declspec(dllexport)int XVMonoImageStatistics(XVMonoImageStatisticsIn & XVMonoImageStatistics_In, XVMonoImageStatisticsOut & XVMonoImageStatistics_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(ͼ������Ϊ��)
	//����-2���㷨����ʧ��(���ǻҶ�ͼ��)

	enum XVRectangleOrientation {
		XVO_Horizonal,//ˮƽ
		XVO_Vertical//��ֱ
	};

	struct XVRegionBoundingRectIn{
		XVRegion inRegion;//��������
		XVRectangleOrientation inOrientation;//����Ĭ��ˮƽ
	};
	struct XVRegionBoundingRectOut{
		XVRectangle2D outRect;//�����С��Ӿ���
		XVPoint2D outLeftUp;//��С��Ӿ��ε����϶���
		XVPoint2D outRightUp;//��С��Ӿ��ε����϶���
		XVPoint2D outRightDown;//��С��Ӿ��ε����¶���
		XVPoint2D outLeftDown;//��С��Ӿ��ε����¶���
		XVPoint2D outCenter;//��С��Ӿ��ε����ĵ�
		float outTime;
	};
	//�������ƣ�������Ӿ���
	__declspec(dllexport)int XVRegionBoundingRect(XVRegionBoundingRectIn &XVRegionBoundingRect_In, XVRegionBoundingRectOut &XVRegionBoundingRect_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��



	struct XVThresholdImageToRegionColorIn{
		XVImage *inImage;//����ͼ��
		XVRegion inRegion;//����Ȥ����Ĭ��ȫͼ�����Ƶ���������ܹ����棬����������Ƿ�Ϊ��
		XVImageType inType;//ͼ�����ͣ������Ĭ��RGB
		int inFirstMin;//��1ͨ����Сֵ�����������Ĭ��ֵ0����Χ0~255
		int inFirstMax;//��1ͨ�����ֵ�����������Ĭ��ֵ255����Χ0~255
		int inSecondMin;//��2ͨ����Сֵ�����������Ĭ��ֵ0����Χ0~255
		int inSecondMax;//��2ͨ�����ֵ�����������Ĭ��ֵ255����Χ0~255
		int inThirdMin;//��3ͨ����Сֵ�����������Ĭ��ֵ0����Χ0~255
		int inThirdMax;//��3ͨ�����ֵ�����������Ĭ��ֵ255����Χ0~255
	};
	struct XVThresholdImageToRegionColorOut{
		XVRegion outRegion;//�������
		float outTime;//ʱ��
	};
	//�������ƣ���ɫ��ֵ��
	__declspec(dllexport)int XVThresholdImageToRegionColor(XVThresholdImageToRegionColorIn & XVThresholdImageToRegionColor_In, XVThresholdImageToRegionColorOut & XVThresholdImageToRegionColor_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(ͼ��Ϊ��)
	//����-2���㷨����ʧ��(���������ɫͼ��)



	struct XVRegionToImageIn{
		XVRegion inRegion;
	};
	struct XVRegionToImageOut{
		XVImage outImage;
		float outTime;
	};
	//�������ƣ�����תͼ��
	__declspec(dllexport)int XVRegionToImage(XVRegionToImageIn &XVRegionToImage_In, XVRegionToImageOut &XVRegionToImage_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��



	struct XVColorImageStatisticsIn{
		XVImage *inImage;//�����ɫͼ��
		XVRegion inRoi;//����Ȥ���򣬹ر���������Ȥ�����豣������������������Ƿ�Ϊ��
		XVImageType inType;//ͼ�����ͣ���������������˵���Ĭ��RGB
	};
	struct XVColorImageStatisticsOut{
		XVInfoOfChannel outFirstChannel;//��1ͨ��
		XVInfoOfChannel outSecondChannel;//��2ͨ��
		XVInfoOfChannel outThirdChannel;//��3ͨ��
		float outTime;//ʱ��
	};
	//�������ƣ���ɫͼ��ͳ��
	__declspec(dllexport)int XVColorImageStatistics(XVColorImageStatisticsIn &XVColorImageStatistics_In, XVColorImageStatisticsOut &XVColorImageStatistics_Out);
	//����0, �㷨���гɹ�
	//����-1,�㷨����ʧ��(ͼ������Ϊ��)
	//����-2,�㷨����ʧ��(����ͼ���ǲ�ɫͼ��)



	struct XVRegionHolesIn{
		XVRegion inRegion; //��������
		int inNeighborhood;//��ͨ�ԡ���������������˵���ֻ��4��8����ѡ�Ĭ��Ϊ8
		int inMinHoleArea; //����С�����Ĭ��ֵΪ1
		int inMaxHoleArea;//����������Ĭ��ֵΪ999999
	};
	struct XVRegionHolesOut{
		vector<XVRegion> outHoles;//����׶�
		float outTime;//ʱ��
	};
	//�������ƣ�����׶�
	__declspec(dllexport)int XVRegionHoles(XVRegionHolesIn &XVRegionHoles_In, XVRegionHolesOut &XVRegionHoles_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��


	struct XVFillRegionHolesIn{
		XVRegion inRegion; //��������
		int inNeighborhood;//��ͨ�ԡ���������������˵���ֻ��4��8����ѡ�Ĭ��Ϊ8
		int inMinHoleArea; //���Ŀ׵���С�����Ĭ��ֵΪ1
		int inMaxHoleArea;//���Ŀ׵���������Ĭ��ֵΪ99999999
	};
	struct XVFillRegionHolesOut{
		XVRegion outRegion;//���������
		float outTime;//ʱ��
	};
	//�������ƣ��������׶�
	__declspec(dllexport)int XVFillRegionHoles(XVFillRegionHolesIn &XVFillRegionHoles_In, XVFillRegionHolesOut &XVFillRegionHoles_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ�� 


	struct XVGetMaximumAndMinimumRegionIn{
		vector<XVRegion> inRegions;//��������������ж��Ƿ�Ϊ�գ���Ϊ�գ�����ʾ����
		XVClassifyFeature inFeature;//������������������˵���Ĭ��ֵ:���(XVClassifyFeature::Area)
	};
	struct XVGetMaximumAndMinimumRegionOut{
		int outMiniIndex;//��С��������
		XVRegion outMiniRegion;//��С����
		float outMiniValue;//��С��������ֵ
		int ouMaxIndex;//�����������
		XVRegion outMaxRegion;//�������
		float outMaxValue;//�����������ֵ
		float outTime;//ʱ��
	};
	//�������ƣ���ȡ��ֵ����
	__declspec(dllexport)int XVGetMaximumAndMinimumRegion(XVGetMaximumAndMinimumRegionIn &XVGetMaximumAndMinimumRegion_In, XVGetMaximumAndMinimumRegionOut &XVGetMaximumAndMinimumRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ�� 
	/*ͨ���㷨*/


	struct XVRectangleRegionIn{
		XVRectangle2D inRectangle;//���Σ��������Ĭ��ֵ(origin=(0,0),angle=0,width=200,height=120)
		XVCoordinateSystem2D inAlignment;//�ο�����ϵ
		int inFrameWidth;//��Ч��ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
		int inFrameHeight;//��Ч�߶ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
	};
	struct XVRectangleRegionOut{ 
		XVRegion outRegion;//��������
		float outTime;//ʱ��
	};
	//�������ƣ�������������
	__declspec(dllexport)int XVRectangleRegion(XVRectangleRegionIn &XVRectangleRegion_In, XVRectangleRegionOut &XVRectangleRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	struct XVCircleRegionIn{
		XVCircle2D inCircle;//Բ�Σ��������Ĭ��ֵ(center=(50,50),radius=50)
		XVCoordinateSystem2D inAlignment;//�ο�����ϵ
		int inFrameWidth;//��Ч��ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
		int inFrameHeight;//��Ч�߶ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
	};
	struct XVCircleRegionOut{
		XVRegion outRegion;//Բ������
		float outTime;//ʱ��
	};
	//�������ƣ�����Բ������
	__declspec(dllexport)int XVCircleRegion(XVCircleRegionIn &XVCircleRegion_In, XVCircleRegionOut &XVCircleRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	struct XVRingRegionIn{
		XVCircleFittingField inRing;//�������������ȷ��inRing.axis.radius>=0��inRing.width>=0
		XVCoordinateSystem2D inAlignment;//�ο�����ϵ
		int inFrameWidth;//��Ч��ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
		int inFrameHeight;//��Ч�߶ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
	};
	struct XVRingRegionOut{
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ�����Բ������
	__declspec(dllexport)int XVRingRegion(XVRingRegionIn& XVRingRegion_In, XVRingRegionOut& XVRingRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	struct XVRingSectionRegionIn {
		XVCircleFittingField inRing;//�������������ȷ��inRing.axis.radius>0��inRing.width>0
		XVCoordinateSystem2D inAlignment;//�ο�����ϵ
		float inStartAngle;//��ʼ�Ƕ�
		float inDeltaAngle;//��ԽǶ�
		int inNum;//�ֶθ�����Ĭ��ֵ1����Χ��>=1������
		int inFrameWidth;//��Ч��ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
		int inFrameHeight;//��Ч�߶ȣ�Ĭ��ֵ1000������ͼ���л�������������Ϊͼ���
	};
	struct XVRingSectionRegionOut {
		XVRegion outRegion;//�������
		float outTime;
	};
	//�������ƣ�����Բ��������
	__declspec(dllexport)int XVRingSectionRegion(XVRingSectionRegionIn& XVRingSectionRegion_In, XVRingSectionRegionOut& XVRingSectionRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨�׳��쳣����鿴�㷨��־
	//����-2��ɨ����̫�󣬵�����Բ�뾶С��0��ɨ���ȱ���<=2*Բ�뾶
	//����-3���ۺϽǶȳ���360�ȣ��ֶθ���̫�����ԽǶ�̫��

	struct XVJudgePointInRegionIn{
		XVRegion inRegion;//��������������ж��Ƿ�Ϊ�գ��ղ�ִ��
		XVPoint2D inPt;//����㣬������ж��Ƿ�Ϊ�գ��ղ�ִ��
	};
	struct XVJudgePointInRegionOut{
		bool outIsContained;//������־
		float outTime;//ʱ��
	};
	//�������ƣ�����������
	__declspec(dllexport)int XVJudgePointInRegion(XVJudgePointInRegionIn &XVJudgePointInRegion_In, XVJudgePointInRegionOut &XVJudgePointInRegion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��


	struct XVPointsConvexHullIn{
		vector<XVPoint2D> inPoints;//����㼯
	};
	struct XVPointsConvexHullOut{
		XVPath outHull;//���͹��
		float outHullArea;//���͹�����
		float outTime;//����㷨����ʱ��
	};
	//�������ƣ��㼯͹��
	__declspec(dllexport)int XVPointsConvexHull(XVPointsConvexHullIn &XVPointsConvexHull_In, XVPointsConvexHullOut &XVPointsConvexHull_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��


	struct XVRegionEqualIn{
		XVRegion inRegion1;//��������1����������ж������Ƿ�Ϊ��
		XVRegion inRegion2;//��������2����������ж������Ƿ�Ϊ��
	};
	struct XVRegionEqualOut{
		bool outIsEqual;//�����־
		float outTime;//ʱ��
	};
	//�������ƣ��������
	__declspec(dllexport)int XVRegionEqual(XVRegionEqualIn &XVRegionEqual_In, XVRegionEqualOut &XVRegionEqual_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��


	struct XVRegionToRegionDistanceIn{
		XVRegion inRegion1;//��������1����������ж������Ƿ�Ϊ��
		XVRegion inRegion2;//��������2����������ж������Ƿ�Ϊ��
	};
	struct XVRegionToRegionDistanceOut{
		float outDist;//�������
		XVSegment2D outSeg;//��̾�����
		float outTime;//ʱ��
	};
	//�������ƣ��������
	__declspec(dllexport)int XVRegionToRegionDistance(XVRegionToRegionDistanceIn &XVRegionToRegionDistance_In, XVRegionToRegionDistanceOut &XVRegionToRegionDistance_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��


	struct XVRegionConvexityIn{
		XVRegion inRegion;//��������
	};
	struct XVRegionConvexityOut{
		float outConvexity;//���͹��
		float outTime;//ʱ��
	};
	//�������ƣ�����͹��
	__declspec(dllexport)int XVRegionConvexity(XVRegionConvexityIn &XVRegionConvexity_In, XVRegionConvexityOut &XVRegionConvexity_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	struct XVPointsBoundingRectangleIn{
		vector<XVPoint2D> inPts;
	};
	struct XVPointsBoundingRectangleOut{
		XVRectangle2D outRect;
		float outTime;
	};
	//�������ƣ��㼯��Ӿ���
	__declspec(dllexport)int XVPointsBoundingRectangle(XVPointsBoundingRectangleIn &XVPointsBoundingRectangle_In, XVPointsBoundingRectangleOut &XVPointsBoundingRectangle_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	struct XVPointsBoundingCircleIn{
		vector<XVPoint2D>inPts;
	};
	struct XVPointsBoundingCircleOut{
		XVCircle2D outCircle;
		float outTime;
	};
	//�������ƣ��㼯���Բ
	__declspec(dllexport)int XVPointsBoundingCircle(XVPointsBoundingCircleIn &XVPointsBoundingCircle_In, XVPointsBoundingCircleOut &XVPointsBoundingCircle_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	struct XVPointsBoundingBoxIn{
		vector<XVPoint2D> inPts;
	};
	struct XVPointsBoundingBoxOut{
		XVRectangle2D outRect;
		float outTime;
	};
	//�������ƣ��㼯��ӿ�
	__declspec(dllexport)int XVPointsBoundingBox(XVPointsBoundingBoxIn &XVPointsBoundingBox_In, XVPointsBoundingBoxOut &XVPointsBoundingBox_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	enum XVMode {
		XM_All,//��������
		XM_External,//������
		XM_Internal//������
	};
	struct XVRegionContoursIn {
		XVRegion inRegion;//��������
		XVMode inMode;//����ģʽ��Ĭ����������(XM_All)
		int inConnectivity;//��ͨ�ԣ�������������˵�������ѡ��4��8��Ĭ��8
	};
	struct XVRegionContoursOut {
		vector<XVPath> outContours;//��������
		float outPerimeter;//�������ܳ�
		float outTime;//ʱ��
	};
	//�������ƣ����������ܳ�
	__declspec(dllexport)int XVRegionContours(XVRegionContoursIn& XVRegionContours_In, XVRegionContoursOut& XVRegionContour_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��

	struct XVGetMaximumAndMinimumRegionIntegrationIn{
		XVRegion inRegion;//��������������ж��Ƿ�Ϊ�գ���Ϊ�գ�����ʾ����
		int inNeighborhood;//��ͨ��,��������������˵���ֻ��4��8����ѡ�Ĭ��Ϊ8
		XVClassifyFeature inFeature;//������������������˵���Ĭ��ֵ:���(XVClassifyFeature::Area)
	};
	struct XVGetMaximumAndMinimumRegionIntegrationOut{
		XVRegion outMiniRegion;//��С����
		float outMiniValue;//��С��������ֵ
		XVRegion outMaxRegion;//�������
		float outMaxValue;//�����������ֵ
		float outTime;//ʱ��
	};
	//�������ƣ���ȡ��ֵ����(����)
	__declspec(dllexport)int XVGetMaximumAndMinimumRegionIntegration(XVGetMaximumAndMinimumRegionIntegrationIn &XVGetMaximumAndMinimumRegionIntegration_In, XVGetMaximumAndMinimumRegionIntegrationOut &XVGetMaximumAndMinimumRegionIntegration_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ�� 


	struct JudgeColorParam{
		float inFirstMin;  //��1ͨ����Сֵ,Ĭ��ֵ100.0
		float inFirstMax;  //��1ͨ�����ֵ,Ĭ��ֵ255.0
		float inSecondMin; //��2ͨ����Сֵ,Ĭ��ֵ0.0
		float inSecondMax; //��2ͨ�����ֵ,Ĭ��ֵ100.0
		float inThirdMin;  //��3ͨ����Сֵ,Ĭ��ֵ0.0
		float inThirdMax;  //��3ͨ�����ֵ,Ĭ��ֵ100.0
		string inColorType;//��ɫ���ƣ�Ĭ��ֵ"Red"
	};
	struct XVJudgeColorIn{
		XVImage *inImage; //����ͼ��
		XVRegion inRoi;   //����Ȥ������������ж��Ƿ�Ϊ��
		vector<JudgeColorParam> inColorParams;//��ɫ������������ж��Ƿ�Ϊ�գ���Ϊ�գ���ִ��
	};
	struct XVJudgeColorOut{
		string outColorType;//��ɫ����
		float outTime;//ʱ��
	};
	//�������ƣ���ɫʶ��(RGB)
	__declspec(dllexport)int XVJudgeColor(XVJudgeColorIn &XVJudgeColor_In, XVJudgeColorOut &XVJudgeColor_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(ͼ��Ϊ��)
	//����-2���㷨����ʧ��(ͼ��ǲ�ɫ)
	//����-3���㷨����ʧ��(��ɫ�����б�Ϊ��)

	struct ArrayRegionsUnionIn{
		vector<XVRegion> inRegions;
	};
	struct ArrayRegionsUnionOut{
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ���������ϲ�
	__declspec(dllexport)int ArrayRegionsUnion(ArrayRegionsUnionIn &ArrayRegionsUnion_In, ArrayRegionsUnionOut &ArrayRegionsUnion_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(��������Ϊ��)
	//����-2���㷨����ʧ��(�쳣)

	struct XVPixel{
		float ch1;
		float ch2;
		float ch3;
		float ch4;
	};
	struct XVGetImagePixelIn{
		XVImage *inImage;//ͼ�񣬿���������ͨ��(1��2��3��4)������Ϊ��
		XVPoint2DInt inPoint;//λ�ã�����Ϊ��
	};
	struct XVGetImagePixelOut{
		float outValue;//ƽ������ֵ
		XVPixel outPixel;//������أ����磬����ͼ��Ϊ1ͨ������ch1Ϊ��Чֵ������ͼ��Ϊ3ͨ������ch1��ch2��ch3Ϊ��Чֵ
		float outTime;
	};
	//�������ƣ���ȡͼ������
	__declspec(dllexport)int XVGetImagePixel(XVGetImagePixelIn &XVGetImagePixel_In, XVGetImagePixelOut &XVGetImagePixel_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(ͼ��Ϊ��)
	//����-2���㷨����ʧ��(�����㳬��ͼ��Χ)
	//����-3���㷨����ʧ��(�쳣)

	struct XVImageAverageIn{
		XVImage *inImage;//ͼ�񣬿���������ͨ��(1��2��3��4)������Ϊ��
		XVRegion inRoi;//����Ȥ������������ж��Ƿ�Ϊ��
	};
	struct XVImageAverageOut{
		float outAverageValue;//ͼ��ƽ��ֵ
		XVPixel outAveragePixel;//ÿ��ͨ��ƽ��ֵ
		float outTime;
	};
	//�������ƣ�ͼ������ƽ��
	__declspec(dllexport)int XVImageAverage(XVImageAverageIn &XVImageAverage_In, XVImageAverageOut &XVImageAverage_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(ͼ��Ϊ��)
	//����-2���㷨����ʧ��(�쳣)

	struct XVImageSumIn{
		XVImage *inImage;//ͼ�񣬿���������ͨ��(1��2��3��4)������Ϊ��
		XVRegion inRoi;//����Ȥ������������ж��Ƿ�Ϊ��
	};
	struct XVImageSumOut{
		float outSumValue;//���غ;�ֵ
		XVPixel outSumPixel;//ÿ��ͨ�����غ�
		float outTime;
	};
	//�������ƣ�ͼ���������
	__declspec(dllexport)int XVImageSum(XVImageSumIn &XVImageSum_In, XVImageSumOut &XVImageSum_Out);
	//����0���㷨���гɹ�
	//����-1���㷨����ʧ��(ͼ��Ϊ��)
	//����-2���㷨����ʧ��(�쳣)


	enum XVImageComputationType {//ͼ����������
		XVC_Add,//�ӣ�Ĭ��ֵ
		XVC_Subtract,//��
		XVC_Difference,//���
		XVC_And,//��
		XVC_Or,//��
		XVC_Xor,//���
		XVC_Min,//��Сֵ
		XVC_Max,//���ֵ
		XVC_Average//ƽ��ֵ
	};
	struct XVImageComputationIn {
		XVImage* inImage1;
		XVImage* inImage2;
		XVImageComputationType inType;
	};
	struct XVImageComputationOut {
		XVImage outImage;
		float outTime;
	};
	//�������ƣ�ͼ������
	__declspec(dllexport)int XVImageComputation(XVImageComputationIn& XVImageComputation_In, XVImageComputationOut& XVImageComputation_Out);
	//����0���㷨���гɹ�
	//����-1������ͼ��Ϊ��
	//����-2������ͼ�����Ͳ�һ��
	//����-3������ͼ��ߴ粻һ��
	//����-4���㷨�׳��쳣

	struct XVCreateColorModelIn {
		XVImage* inImage;//����ͼ��
		XVRegion inRoi;//ѧϰ����Ĭ��ȫͼ
		std::string inColorName;//ģ����ɫ����
	};
	struct XVCreateColorModelOut {
		int outHistogramHue[360];//ģ��ɫ��ֱ��ͼ
		int outHistogramSaturation[256];//ģ�履�Ͷ�ֱ��ͼ
		std::string outColorName;//ģ����ɫ����
		float outTime;//ʱ��
	};
	//�������ƣ�������ɫģ��
	__declspec(dllexport)int XVCreateColorModel(XVCreateColorModelIn& XVCreateColorModel_In, XVCreateColorModelOut& XVCreateColorModel_Out);
	//����0���㷨���гɹ�
	//����-1��ͼ��Ϊ��
	//����-2��ģ��ͼ������ǲ�ɫͼ��

	enum XVDistanceMeasuring {
		XVD_Euclidean,//ŷ�Ͼ���
		XVD_Manhattan//�����پ���
	};
	struct XVColorIdentificationIn {
		XVImage* inImage;//��ʶ��ͼ��
		XVRegion inRoi;//����Ȥ����Ĭ�Ͽ�����(ȫͼ)
		vector<XVCreateColorModelOut> inModels;//��ɫģ��
		XVDistanceMeasuring inMeasuring;//���������ʽ
	};
	struct XVResultInfo {
		std::string name;//��ɫ����
		float score;//��������ʾ��ǰͼ���ж�Ϊ����ɫ�ĸ���
	};
	struct XVColorIdentificationOut {
		vector<XVResultInfo> outResults;//ʶ������Ϣ���Ѱ��÷ֽ�������
		int outCurrentHistogramHue[360];//ɫ��ֱ��ͼ
		int outCurrentHistogramSaturation[255];//���Ͷ�ֱ��ͼ
		float outTime;//ʱ��
	};
	//�������ƣ���ɫʶ��(ģ��)
	__declspec(dllexport)int XVColorIdentification(XVColorIdentificationIn& XVColorIdentification_In, XVColorIdentificationOut& XVColorIdentification_Out);
	//����0���㷨���гɹ�
	//����-1��ͼ��Ϊ��
	//����-2�����ǲ�ɫͼ��
	//����-3����ɫģ��Ϊ��

	struct XVThresholdDynamicIn {
		XVImage* inImage;//����ͼ�񣬲�ɫ/�Ҷ�ͼ�����
		XVRegion inRoi;//�������Ȥ���򣬿���Ϊ��
		int inRadiusX;//����������һ�룬���������Ĭ��ֵ3����Χ[0,50]
		int inRadiusY;//��������ߵ�һ�룬���������Ĭ��ֵ3����Χ[0��50]
		int inMinThre;//��С��ֵ�����������Ĭ��ֵ-5����Χ[-255,255]
		int inMaxThre;//�����ֵ�����������Ĭ��ֵ5����Χ[-255,255]
	};
	struct XVThresholdDynamicOut {
		XVRegion outRegion;//�������
		float outTime;//ʱ��
	};
	//�������ƣ���̬��ֵ��
	__declspec(dllexport)int XVThresholdDynamic(XVThresholdDynamicIn& XVThresholdDynamic_In, XVThresholdDynamicOut& XVThresholdDynamic_Out);
	//����0���㷨���гɹ�
	//����-1��ͼ��Ϊ��

	enum XVTransformationType {//ͼ�񼸺α任����
		Mirror,//����
		Shift,//ƽ��
		Scale,//����
		Rotate,//��ת
		Affine//����
	};
	enum XVInterpolationMethod {//��ֵ��
		NearestNeighbor,//�����
		Bilinear//˫����
	};
	enum XVMirrorType {//��������
		VerticalMirror,//��ֱ����
		HorizonalMirror,//ˮƽ����
		RotateMirror//��ת����
	};
	struct XVGeometricTransformationIn {
		XVImage* inImage;//����ͼ�񣬻ҶȻ��ɫͼ��
		XVRectangle2D inRoi;//����Ȥ����
		XVTransformationType inTransformationType;//�任���ͣ�Ĭ��ƽ��ģʽ(Shift)
		XVInterpolationMethod inInterpolation;//��ֵ����Ĭ�������(NearestNeighbor)

		//������ģʽ�¿���
		XVMirrorType inMirrorType;//�������ͣ�Ĭ�ϴ�ֱ����(VerticalMirror)

		//�����䡢ƽ��ģʽ�¿���
		int inShiftX;//x����ƽ�ƾ��룬Ĭ��0
		int inShiftY;//y����ƽ�ƾ��룬Ĭ��0

		//�����䡢����ģʽ�¿���
		float inScale;//���ű�����Ĭ��1.0����Χ[0.1,10.0]

		//�����䡢��תģʽ�¿���
		float inAngle;//��ת�Ƕȣ�Ĭ��0.0
	};
	struct XVGeometricTransformationOut {
		XVImage outImage;//���ͼ��
		float outTime;//ʱ��
	};
	//�������ƣ�ͼ�񼸺α任
	__declspec(dllexport)int XVGeometricTransformation(XVGeometricTransformationIn& XVGeometricTransformation_In, XVGeometricTransformationOut& XVGeometricTransformation_Out);
	//����0���㷨���гɹ�
	//����-1��ͼ��Ϊ��
	//����-2�����ͼ��̫�󣬵����ڴ����ʧ��

	//��һ������ö��
	enum XVImageNormalizationType {
		HistogramEqualization,//ֱ��ͼ���⻯
		HistogramNormalization,//ֱ��ͼ��һ��
		AveStandardDeviationNormalization//��ֵ��׼���һ��
	};
	struct XVImageNormalizationIn {
		XVImage* inImage;//����ͼ�񣬱����ǻҶ�ͼ��
		XVImageNormalizationType  inType;//��һ�����ͣ�����Ĭ��ֵ��ֱ��ͼ���⻯(HistogramEqualization)

		/*����ѡ��"ֱ��ͼ��һ��"����ʱ��ʾ*/
		//���뱣֤���Ҷ˱���֮�Ͳ�����1.0��������˱���Ϊ0.6,�Ҷ˱���Ϊ0.7����Ȼ������Եķ�Χ���������Ǳ���֮��Ϊ1.3������1.0����ʱ��λ��Ӧ���Ҷ˱���ǿ���޸�Ϊ1-0.6=0.4
		float inLeftProportion;//������غ��Ա���,Ĭ��0.0����Χ[0.0,1.0]
		float inRightProportion;//�Ҷ����غ��Ա���,Ĭ��0.0,��Χ[0.0,1.0]
		int inTargetMinValue;//Ŀ����С�Ҷ�ֵ��Ĭ��0����Χ[0,255]
		int inTargetMaxValue;//Ŀ�����Ҷ�ֵ��Ĭ��255����Χ[0,255]
		/*����ѡ��"ֱ��ͼ��һ��"����ʱ��ʾ*/

		/*����ѡ��"��ֵ��׼���һ��"����ʱ��ʾ*/
		float inTargetAverage;//Ŀ���ֵ��Ĭ��125.0����Χ[0.0��255.0]
		float inTargetStandardDeviation;//Ŀ���׼�Ĭ��20.0����Χ[0.0��255.0]
		/*����ѡ��"��ֵ��׼���һ��"����ʱ��ʾ*/
	};
	struct XVImageNormalizationOut {
		XVImage outImage;//��һ�����ͼ��
		float outTime;//ʱ��
	};
	//�������ƣ�ͼ���һ��
	__declspec(dllexport)int XVImageNormalization(XVImageNormalizationIn& XVImageNormalization_In, XVImageNormalizationOut& XVImageNormalization_Out);
	//����0���㷨���гɹ�
	//����-1������ͼ��Ϊ��
	//����-2������ͼ������ǻҶ�ͼ��

	struct XVMergingImagesIn {
		XVImage* inImage;//����ͼ��
		int inRows;//������Ĭ��2����Χ[1,10]
		int inCols;//������Ĭ��2����Χ[1,10]
		int inIndex;//������Ĭ��0����Χ[0,inRows*inCols)
	};
	struct XVMergingImagesOut {
		XVImage outImage;//
		float outTime;//ʱ��
	};
	//�������ƣ�
	__declspec(dllexport)int XVMergingImages(XVMergingImagesIn& XVMergingImages_In, XVMergingImagesOut& XVMergingImages_Out);
	//����0���㷨���гɹ�
	//����-1������ͼ��Ϊ��

	struct XVRegionInnerBoxIn {
		XVRegion inRegion;//��������
		int inMinWidth;//�ڽӿ���С��ȣ�Ĭ��ֵ��1
		int inMaxWidth;//�ڽӿ�����ȣ�Ĭ��ֵ��999999
		int inMinHeight;//�ڽӿ���С�߶ȣ�Ĭ��ֵ��1
		int inMaxHeight;//�ڽӿ����߶ȣ�Ĭ��ֵ��999999
	};
	struct XVRegionInnerBoxOut {
		XVBox outBox;//����ڽӿ�
		float outTime;//�㷨����ʱ��,��λms
	};
	//�������ƣ������ڽӿ�
	__declspec(dllexport)int XVRegionInnerBox(XVRegionInnerBoxIn& XVRegionInnerBox_In, XVRegionInnerBoxOut& XVRegionInnerBox_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��

	struct XVResizeRegionIn {
		XVRegion inRegion;
		int inNewWidth;
		int inNewHeight;
	};
	struct XVResizeRegionOut {
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ���������
	__declspec(dllexport)int XVResizeRegion(XVResizeRegionIn& XVResizeRegion_In, XVResizeRegionOut& XVResizeRegion_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��


	struct XVDilateIn {
		XVRegion inRegion;
		int inRadiusX;
		int inRadiusY;
		XVMorphShape inKernel;
	};
	struct XVDilateOut {
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ���������
	__declspec(dllexport)int XVRegionDilate(XVDilateIn& XVDilate_In, XVDilateOut& XVDilate_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��

	struct XVErodeIn {
		XVRegion inRegion;
		int inRadiusX;
		int inRadiusY;
		XVMorphShape inKernel;
	};
	struct XVErodeOut {
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ�����ʴ
	__declspec(dllexport)int XVRegionErode(XVErodeIn& XVErode_In, XVErodeOut& XVErode_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��

	struct XVDilateOfCloseIn {
		XVRegion inRegion;
		int inRadiusX;
		int inRadiusY;
		XVMorphShape inKernel;
	};
	struct XVDilateOfCloseOut {
		XVRegion outRegion;
		float outTime;
	};
	//�������ƣ���������(��)
	__declspec(dllexport)int XVRegionDilateOfClose(XVDilateOfCloseIn& XVDilate_In, XVDilateOfCloseOut& XVDilate_Out);
	//����0���㷨���гɹ�
	//����-1����������Ϊ��
	
	struct XVCompose3In {
		XVImage* inImage1;
		XVImage* inImage2;
		XVImage* inImage3;
	};
	struct XVCompose3Out {
		XVImage outImage;
		float outTime;
	};
	//�������ƣ�������ͨ��ͼ��
	__declspec(dllexport)int XVCompose3(XVCompose3In& XVCompose3_In, XVCompose3Out& XVCompose3_Out);
	//����0���㷨���гɹ�
	//����-1�����ͼ��̫���ڴ����ʧ��
	//����-2������ͼ������ǻҶ�ͼ��
	//����-3������ͼ�����ߴ���ͬ
	//����-4������ͼ����Ϊ��

	struct XVSetImagePixelsIn {
		XVImage* inImage;
		XVRegion inRoi;
		XVPixel inPixel;//�Ҷ�ͼ���������inPixel.ch1
	};
	struct XVSetImagePixelsOut {
		XVImage outImage;
		float outTime;
	};
	//�������ƣ���������ֵ
	__declspec(dllexport)int XVSetImagePixels(XVSetImagePixelsIn& XVSetImagePixels_In, XVSetImagePixelsOut& XVSetImagePixels_Out);
	//����0���㷨���гɹ�
	//����-2������ͼ��Ϊ��

	struct XVTileImageOffsetIn {
		vector<XVImage> inImgs;
	};
	struct XVTileImageOffsetOut {
		XVImage outImage;
		float outTime;
	};
	//�������ƣ�ͼ��ƴ��
	__declspec(dllexport)int XVTileImageOffset(XVTileImageOffsetIn& XVTileImageOffset_In, XVTileImageOffsetOut& XVTileImageOffset_Out);
	//����0���㷨���гɹ�
}
#endif