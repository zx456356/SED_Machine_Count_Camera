 //#pragma once
#ifndef BLOBANALYSIS_H
#define BLOBANALYSIS_H
#include "XVBase.h"
#include <string>
namespace XVL{
	//区域特征枚举
	enum XVClassifyFeature{
		XCF_Area,           //面积
		XCF_Circularity_boundingCircle,//似圆度_外接圆
		XCF_Circularity_radius,    //似圆度_半径
		XCF_Convexity,             //凸度
		XCF_Elogation,        //延伸率
		XCF_MassCenterX,     //质心x
		XCF_MassCenterY,     //质心y
		XCF_MajorAxis,       //长轴长
		XCF_MinorAxis,       //短轴长
		XCF_Orientation,     //方向
		XCF_Rectangularity,  //矩形度
		XCF_UpperLeftX,//左上角X
		XCF_UpperLeftY//左上角Y
	};

	struct XVBlobPreIn{
		XVImage *inImage;//输入图像
		XVRegion inRoi;//输入学习区域，不能为空
		//软件界面上设置亮、暗选项，若选择亮(默认)，则灰度最小值设为140，最大值设为255；若选择暗，则灰度最小值设为0，最大值设为130；
		float inMinThre;//灰度值最小值
		float inMaxThre;//灰度值最大值
	};
	struct XVBlobPreOut{
		vector<XVRegion> outRegions;//输出区域数组
		float outTime;//时间
	};
	//函数名称：斑点定位预处理
	__declspec(dllexport)int blobPre(XVBlobPreIn &XVBlobPre_In, XVBlobPreOut &XVBlobPre_Out);
	//返回0， 预处理成功
	//返回-1，预处理失败(输入图像为空)
	//返回-2，预处理失败(学习区域为空)
	//返回-3，预处理失败(阈值化执行失败)
	//返回-4, 预处理失败(连通性分割失败)
	//返回-5，预处理失败(抛出异常)

	struct XVBlobLearnIn{//斑点学习输入
		vector<XVRegion> inRegions;//输入区域数组
		vector<XVClassifyFeature> inFeatures;//学习特征信息，不能为空
		int inSelectedIndex;//选中区域的索引，默认0
	};
	struct XVBlobLearnOut{//斑点学习输出
		XVRegion outRegion;//学习得到的区域
		vector<XVClassifyFeature> outFeatures;//学习特征
		vector<float> outValues;//区域特征值
		XVPoint2D outCenter;//学习到的区域重心
		float outTime;//时间
	};
	//函数名称：斑点学习
	__declspec(dllexport)int blobPatternLearn(XVBlobLearnIn &XVBlobLearn_In, XVBlobLearnOut &XVBlobLearn_Out);
	//返回0， 模板学习成功
	//返回-1，模板学习失败(输入区域数组为空)
	//返回-2，模板学习失败(学习特征为空)
	//返回-3，模板学习失败(抛出异常)
	
	struct XVBlobMatchIn{//斑点定位输入
		XVImage *inImage;//输入图像
		XVRegion inSearchRoi;//搜索区域，默认全图
		XVBlobLearnOut inModel;//Blob模板
		//软件界面上设置亮、暗选项，若选择亮(默认)，则灰度最小值设为140，最大值设为255；若选择暗，则灰度最小值设为0，最大值设为130；
		float inThreMin;//灰度最小值
		float inThreMax;//灰度最大值
		float inSimilarity;//相似度阈值，软件中设置默认值0.8
		bool inMatchMulti;//是否输出多个，软件中设置下拉菜单，共两个选项true/false，默认false
	};
	struct XVBlobMatchOut{//斑点定位输出
		vector<XVRegion> outRegions;//匹配得到的区域
		vector<float> outScores;//得分
		vector<XVPoint2D> outCenters;//区域中心
		vector<vector<float>> outValues;//各个区域对应的特征值
		float outTime;//时间
	};
	//函数名称:斑点定位
	__declspec(dllexport)int blobPatternMatch(XVBlobMatchIn &XVBlobMatch_In, XVBlobMatchOut &XVBlobMatch_Out);
	//返回0，模板匹配成功
	//返回-1，模板匹配失败(图像为空)
	//返回-2，模板匹配失败(阈值化失败)
	//返回-3，模板匹配失败（未找到目标)
	//返回-4，模板匹配失败(抛出异常)
	//返回-5，模板匹配失败(连通性分割失败)
	//返回-6，模板匹配失败(模板为空)

	/*通用算法*/
	enum XVImageType{//图像类型
		RGB,
		HSI,
		HSL,
		HSV
	};



	struct XVInfoOfChannel{//通道信息
		float outMinimumValue;//最小像素值
		XVPoint2D outMinimumLocation;//最小像素值的位置
		float outMaximumValue;//最大像素值
		XVPoint2D outMaximumLocation;//最大像素值的位置
		float outAverageValue;//平均像素值
		float outSumValue;//像素值总和
		float outStdValue;//像素值标准差
	};



	struct XVThresholdImageToRegionMonoIn{
		XVImage *inImage; //输入图像
		XVRegion inRegion;//常见几何图形区域(圆、矩形等)、不规则区域、ROI擦除区域，软件无需检测是否为空
		XVCoordinateSystem2D inAlignment;//输入局部坐标系
		float inMin;    //灰度最小值，软件中设置默认值0
		float inMax;    //灰度最大值，软件中设置默认值255
	};
	struct XVThresholdImageToRegionMonoOut{
		XVRegion outRegion;//阈值化区域
		float outTime;//算法运行时间,单位ms
	};
	//函数名称：灰度阈值化
	__declspec(dllexport)int XVThresholdImageToRegionMono(XVThresholdImageToRegionMonoIn & XVThresholdImageToRegionMono_In, XVThresholdImageToRegionMonoOut & XVThresholdImageToRegionMono_Out);
	//返回0，算法运行成功
	//返回-1，图像输入为空
	//返回-2，必须输入灰度图像



	struct XVRegionAreaIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionAreaOut{
		int outArea;//输出面积
		float outTime;//算法运行时间,单位ms 
	};
	//函数名称：区域面积
	__declspec(dllexport)int XVRegionArea(XVRegionAreaIn & XVRegionArea_In, XVRegionAreaOut & XVRegionArea_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空



	struct XVRegionCenterIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionCenterOut{
		XVPoint2D outCenter;//输出质心
		float outTime;//算法运行时间,单位ms
	};
	//函数名称：区域重心
	__declspec(dllexport)int XVRegionCenter(XVRegionCenterIn & XVRegionCenter_In, XVRegionCenterOut & XVRegionCenter_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空



	struct XVRegionRectangularityIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionRectangularityOut{
		float outRectangularity;//输出矩形度
		float outTime;//算法运行时间,单位ms
	};
	//函数名称：区域矩形度
	__declspec(dllexport)int XVRegionRectangularity(XVRegionRectangularityIn & XVRegionRectangularity_In, XVRegionRectangularityOut & XVRegionRectangularity_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空



	struct XVRegionBoundingBoxIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionBoundingBoxOut{
		XVBox outBox;//输出外接框
		XVPoint2D outLeftTop;//输出外接框左上角
		XVPoint2D outRightDown;//输出外接框右下角
		float outTime;//算法运行时间,单位ms
	};
	//函数名称：区域外接框
	__declspec(dllexport)int XVRegionBoundingBox(XVRegionBoundingBoxIn & XVRegionBoundingBox_In, XVRegionBoundingBoxOut & XVRegionBoundingBox_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空



	struct XVSplitRegionToBlobsIn{
		XVRegion inRegion;//输入区域
		int inNeighborhood;//连通性。软件中设置下拉菜单，只有4和8两个选项，默认为8
	};
	struct XVSplitRegionToBlobsOut{
		vector<XVRegion> outRegions;//输出分割后的区域
		float outTime;//算法运行时间,单位ms
	};
	//函数名称：分割区域
	__declspec(dllexport)int XVSplitRegionToBlobs(XVSplitRegionToBlobsIn & XVSplitRegionToBlobs_In, XVSplitRegionToBlobsOut & XVSplitRegionToBlobs_Out);
	//返回0，算法运行成功
	//返回-1,区域输入为空



	struct XVClassifyRegionsIn{
		vector<XVRegion> inRegions;//输入区域
		XVClassifyFeature inFeature;//分类特征。软件中设置下拉菜单，有11个选项，默认面积
		float inMin;//特征最小值
		float inMax;//特征最大值
	};
	struct XVClassifyRegionsOut{
		vector<XVRegion> outAcceptedRegions; //满足条件的区域
		vector<XVRegion> outRejectedRegions; //不满足条件的区域
		vector<float> outAcceptedValues;    //接受区域的特征值
		vector<float> outRejectedValues;    //拒绝区域的特征值
		float outTime;//算法运行时间
	};
	//函数名称：区域分类
	__declspec(dllexport)int XVClassifyRegions(XVClassifyRegionsIn &XVClassifyRegions_In, XVClassifyRegionsOut &XVClassifyRegions_Out);
	//返回0，算法运行成功
	//返回-1,区域输入为空


	//圆形度=区域面积/圆面积，此圆与区域有一个相同的特征，如下:
	enum XVCircularityMeasure{
		radius,//半径
		boundingCircle,//外接圆
		perimeter//周长
	};
	struct XVRegionCircularityIn{
		XVRegion inRegion;//输入区域
		XVCircularityMeasure inMeasure;//测量方式，软件设置下拉菜单，只有3个选项，默认值radius
	};
	struct XVRegionCircularityOut{
		float outCircularity;//输出似圆度
		float outTime;//运行时间,ms
	};
	//函数名称：区域圆度
	__declspec(dllexport)int XVRegionCircularity(XVRegionCircularityIn & XVRegionCircularity_In, XVRegionCircularityOut & XVRegionCircularity_Out);
	//返回0，算法运行成功
	//返回-1,区域输入为空



	struct XVRegionConvexHullIn{
		XVRegion inRegion;//输入区域
		bool inFlag;//操作方向标识符。软件中设置下拉菜单，只有true和false两个选项，默认为false
	};
	struct XVRegionConvexHullOut{
		XVPath outHull;//输出凸包
		float outHullArea;//输出凸包面积
		float outTime;//输出算法运行时间
	};
	//函数名称：区域凸包
	__declspec(dllexport)int XVRegionConvexHull(XVRegionConvexHullIn & XVRegionConvexHull_In, XVRegionConvexHullOut & XVRegionConvexHull_Out);
	//返回0，算法运行成功
	//返回-1，输入区域为空



	struct XVRegionBoundingCircleIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionBoundingCircleOut{
		XVCircle2D outCircle;//输出最小外接圆
		float outTime;//输出算法运行时间
	};
	//函数名称：区域外接圆
	__declspec(dllexport)int XVRegionBoundingCircle(XVRegionBoundingCircleIn & XVRegionBoundingCircle_In, XVRegionBoundingCircleOut & XVRegionBoundingCircle_Out);
	//返回0，算法运行成功
	//返回-1，输入区域为空



	struct XVRegionSecondOrderMomentsIn{
		XVRegion inRegion;//输入区域
		bool inCentral;//是否中心化,软件中设置下拉菜单，仅true/false两个选项，默认false
		bool inNormalized;//是否归一化,软件中设置下拉菜单，仅true/false两个选项，默认false
	};
	struct XVRegionSecondOrderMomentsOut{
		float out_11;//二阶矩_11
		float out_02;//二阶矩_02
		float out_20;//二阶矩_20
		float outTime;//输出算法运行时间
	};
	//函数名称：区域二阶矩
	__declspec(dllexport)int XVRegionSecondOrderMoments(XVRegionSecondOrderMomentsIn & XVRegionSecondOrderMoments_In, XVRegionSecondOrderMomentsOut & XVRegionSecondOrderMoments_Out);                                 //计算二阶矩
	//返回0，运行成功
	//返回-1，输入区域为空



	struct XVRegionElogationIn {
		XVRegion inRegion;//输入区域
	};
	struct XVRegionElogationOut{
		float outElogation;//区域延伸率
		float outTime;//输出算法运行时间
	};
	//函数名称：区域延伸率
	__declspec(dllexport)int XVRegionElogation(XVRegionElogationIn & XVRegionElogation_In, XVRegionElogationOut & XVRegionElogation_out);                                                                             //计算延伸率
	//返回0，运行成功
	//返回-1，输入区域为空



	struct XVRegionEllipticAxisIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionEllipticAxisOut{
		float outMajorAxis;//区域等效椭圆长轴长
		float outMinorAxis;//区域等效椭圆短轴长
		float outTime;//输出算法运行时间
	};
	//函数名称：区域等效椭圆
	__declspec(dllexport)int XVRegionEllipticAxis(XVRegionEllipticAxisIn &XVRegionEllipticAxis_In, XVRegionEllipticAxisOut &XVRegionEllipticAxis_Out);                                 //计算椭圆的长短轴，该椭圆与给定区域有相同的一阶、二阶矩
	//返回0，运行成功
	//返回-1，输入区域为空



	struct XVRegionOrientationIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionOrientationOut{
		float outOrientation;//区域角度，单位：度(°)
		float outTime;//输出算法运行时间
	};
	//函数名称：区域角度
	__declspec(dllexport)int XVRegionOrientation(XVRegionOrientationIn & XVRegionOrientation_In, XVRegionOrientationOut & XVRegionOrientation_Out);                                                                    //计算区域方向角度
	//返回0，运行成功
	//返回-1，输入区域为空



	struct XVAlignPointIn{
		XVPoint2D inPoint;//输入点
		XVCoordinateSystem2D inAlignment;//输入局部坐标系，默认不使能(XVOptionalType::NUL)
		bool inInverse;//是否切换到逆变换，软件中设置默认值false
	};
	struct XVAlignPointOut{
		XVPoint2D outPoint;//输出坐标系跟随后的点
		float outTime;//输出时间
	};
	//函数名称：点变换
	__declspec(dllexport)int XVAlignPoint(XVAlignPointIn &XVAlignPoint_In, XVAlignPointOut &XVAlignPoint_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败



	struct XVAlignRegionIn{
		XVRegion inRegion;//输入区域
		XVCoordinateSystem2D inAlignment;//输入局部坐标系，默认不使能(XVOptionalType::NUL)
		bool inInverse;//是否切换到逆变换，软件中设置默认值false
		int inWidth;//区域帧宽(设为图像宽度)
		int inHeight;//区域帧高（设为图像高度)
	};
	struct XVAlignRegionOut{
		XVRegion outRegion;//输出坐标系跟随后的区域
		float outTime;//输出时间
	};
	//函数名称：区域变换
	__declspec(dllexport)int XVAlignRegion(XVAlignRegionIn &XVAlignRegion_In, XVAlignRegionOut &XVAlignRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(输入区域为空)



	struct XVRegionIntersectionIn{
		XVRegion inRegion1;//输入区域1，软件无需检测是否为空
		XVRegion inRegion2;//输入区域2，软件无需检测是否为空
	};
	struct XVRegionIntersectionOut{
		XVRegion outRegion;
		float outTime;
	};
	//函数名称：区域交集
	__declspec(dllexport)int XVRegionIntersection(XVRegionIntersectionIn &XVRegionIntersection_In, XVRegionIntersectionOut &XVRegionIntersection_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败



	struct XVRegionUnionIn{
		XVRegion inRegion1;//输入区域1，软件无需检测是否为空
		XVRegion inRegion2;//输入区域2，软件无需检测是否为空
	};
	struct XVRegionUnionOut{
		XVRegion outRegion;
		float outTime;
	};
	//函数名称：区域并集
	__declspec(dllexport)int XVRegionUnion(XVRegionUnionIn &XVRegionUnion_In, XVRegionUnionOut &XVRegionUnion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败



	struct XVRegionDifferenceIn{
		XVRegion inRegion1;//输入区域1，软件无需检测是否为空
		XVRegion inRegion2;//输入区域2，软件无需检测是否为空
	};
	struct XVRegionDifferenceOut{
		XVRegion outRegion;
		float outTime;
	};
	//函数名称：区域差集
	__declspec(dllexport)int XVRegionDifference(XVRegionDifferenceIn &XVRegionDifference_In, XVRegionDifferenceOut &XVRegionDifference_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败



	struct XVRegionComplementaryIn{
		XVRegion inRegion;//输入区域，软件无需检测是否为空
	};
	struct XVRegionComplementaryOut{
		XVRegion outRegion;
		float outTime;
	};
	//函数名称：区域补集
	__declspec(dllexport)int XVRegionComplementary(XVRegionComplementaryIn &XVRegionComplementary_In, XVRegionComplementaryOut &XVRegionComplementary_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败



	enum XVMorphType{//形态学运算类型
		Dilate,//膨胀
		Erode,//腐蚀
		Open,//开操作
		Close,//闭操作
	};
	enum XVMorphShape{//形态学核类型
		Rect,//矩形
		Cross,//交叉形
	};
	struct XVRegionMorphIn{
		XVRegion inRegion;//输入区域
		XVMorphType inMorphType;//形态学运算类型，软件中设置默认值Dilate
		XVMorphShape inKernel;//核类型，软件中设置默认值Rect
		int inRadiusX;//核宽一半，软件中设置默认值1，范围[0,999999]
		int inRadiusY;//核高一半，软件中设置默认值1，范围[0,999999]
	};
	struct XVRegionMorphOut{
		XVRegion outRegion;//输出区域
		float outTime;//时间
	};
	//函数名称：区域形态变换
	__declspec(dllexport)int XVRegionMorph(XVRegionMorphIn &XVRegionMorph_In, XVRegionMorphOut &XVRegionMorph_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(输入区域为空)



	struct XVSortRegionIn{
		vector<XVRegion> inRegions;
		XVClassifyFeature inFeature;//排序特征，软件中设置默认值XVClassifyFeature::Area(面积)
		bool inAscending;//升序或降序,软件中设置默认值true(升序)
	};
	struct XVSortRegionOut{
		vector<XVRegion> outSortedRegions;//排序后的区域
		vector<float> outValues;//排序后区域的对应特征值
		float outTime;//时间
	};
	//函数名称：区域排序
	__declspec(dllexport)int XVSortRegions(XVSortRegionIn &XVSortRegion_In, XVSortRegionOut &XVSortRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(输入区域为空)



	struct XVMonoImageStatisticsIn{
		XVImage *inImage;//输入图像
		XVRegion inRoi;//感兴趣区域，软件无需检测是否为空
	};
	struct XVMonoImageStatisticsOut{
		XVInfoOfChannel outInfo;//像素信息
		float outTime;//时间
	};
	//函数名称：灰度图像统计
	__declspec(dllexport)int XVMonoImageStatistics(XVMonoImageStatisticsIn & XVMonoImageStatistics_In, XVMonoImageStatisticsOut & XVMonoImageStatistics_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(图像输入为空)
	//返回-2，算法运行失败(不是灰度图像)

	enum XVRectangleOrientation {
		XVO_Horizonal,//水平
		XVO_Vertical//竖直
	};

	struct XVRegionBoundingRectIn{
		XVRegion inRegion;//输入区域
		XVRectangleOrientation inOrientation;//方向，默认水平
	};
	struct XVRegionBoundingRectOut{
		XVRectangle2D outRect;//输出最小外接矩形
		XVPoint2D outLeftUp;//最小外接矩形的左上顶点
		XVPoint2D outRightUp;//最小外接矩形的右上顶点
		XVPoint2D outRightDown;//最小外接矩形的右下顶点
		XVPoint2D outLeftDown;//最小外接矩形的左下顶点
		XVPoint2D outCenter;//最小外接矩形的中心点
		float outTime;
	};
	//函数名称：区域外接矩形
	__declspec(dllexport)int XVRegionBoundingRect(XVRegionBoundingRectIn &XVRegionBoundingRect_In, XVRegionBoundingRectOut &XVRegionBoundingRect_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败



	struct XVThresholdImageToRegionColorIn{
		XVImage *inImage;//输入图像
		XVRegion inRegion;//感兴趣区域，默认全图，绘制的区域必须能够保存，软件无需检测是否为空
		XVImageType inType;//图像类型，软件中默认RGB
		int inFirstMin;//第1通道最小值，软件中设置默认值0，范围0~255
		int inFirstMax;//第1通道最大值，软件中设置默认值255，范围0~255
		int inSecondMin;//第2通道最小值，软件中设置默认值0，范围0~255
		int inSecondMax;//第2通道最大值，软件中设置默认值255，范围0~255
		int inThirdMin;//第3通道最小值，软件中设置默认值0，范围0~255
		int inThirdMax;//第3通道最大值，软件中设置默认值255，范围0~255
	};
	struct XVThresholdImageToRegionColorOut{
		XVRegion outRegion;//输出区域
		float outTime;//时间
	};
	//函数名称：彩色阈值化
	__declspec(dllexport)int XVThresholdImageToRegionColor(XVThresholdImageToRegionColorIn & XVThresholdImageToRegionColor_In, XVThresholdImageToRegionColorOut & XVThresholdImageToRegionColor_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(图像为空)
	//返回-2，算法运行失败(必须输入彩色图像)



	struct XVRegionToImageIn{
		XVRegion inRegion;
	};
	struct XVRegionToImageOut{
		XVImage outImage;
		float outTime;
	};
	//函数名称：区域转图像
	__declspec(dllexport)int XVRegionToImage(XVRegionToImageIn &XVRegionToImage_In, XVRegionToImageOut &XVRegionToImage_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败



	struct XVColorImageStatisticsIn{
		XVImage *inImage;//输入彩色图像
		XVRegion inRoi;//感兴趣区域，关闭软件后感兴趣区域需保存下来，软件无需检测是否为空
		XVImageType inType;//图像类型，软件中设置下拉菜单，默认RGB
	};
	struct XVColorImageStatisticsOut{
		XVInfoOfChannel outFirstChannel;//第1通道
		XVInfoOfChannel outSecondChannel;//第2通道
		XVInfoOfChannel outThirdChannel;//第3通道
		float outTime;//时间
	};
	//函数名称：彩色图像统计
	__declspec(dllexport)int XVColorImageStatistics(XVColorImageStatisticsIn &XVColorImageStatistics_In, XVColorImageStatisticsOut &XVColorImageStatistics_Out);
	//返回0, 算法运行成功
	//返回-1,算法运行失败(图像输入为空)
	//返回-2,算法运行失败(输入图像不是彩色图像)



	struct XVRegionHolesIn{
		XVRegion inRegion; //输入区域
		int inNeighborhood;//连通性。软件中设置下拉菜单，只有4和8两个选项，默认为8
		int inMinHoleArea; //孔最小面积，默认值为1
		int inMaxHoleArea;//孔最大面积，默认值为999999
	};
	struct XVRegionHolesOut{
		vector<XVRegion> outHoles;//输出孔洞
		float outTime;//时间
	};
	//函数名称：区域孔洞
	__declspec(dllexport)int XVRegionHoles(XVRegionHolesIn &XVRegionHoles_In, XVRegionHolesOut &XVRegionHoles_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败


	struct XVFillRegionHolesIn{
		XVRegion inRegion; //输入区域
		int inNeighborhood;//连通性。软件中设置下拉菜单，只有4和8两个选项，默认为8
		int inMinHoleArea; //填充的孔的最小面积，默认值为1
		int inMaxHoleArea;//填充的孔的最大面积，默认值为99999999
	};
	struct XVFillRegionHolesOut{
		XVRegion outRegion;//填充后的区域
		float outTime;//时间
	};
	//函数名称：填充区域孔洞
	__declspec(dllexport)int XVFillRegionHoles(XVFillRegionHolesIn &XVFillRegionHoles_In, XVFillRegionHolesOut &XVFillRegionHoles_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败 


	struct XVGetMaximumAndMinimumRegionIn{
		vector<XVRegion> inRegions;//输入区域，软件需判断是否为空，若为空，则提示警告
		XVClassifyFeature inFeature;//特征，软件设置下拉菜单，默认值:面积(XVClassifyFeature::Area)
	};
	struct XVGetMaximumAndMinimumRegionOut{
		int outMiniIndex;//最小区域索引
		XVRegion outMiniRegion;//最小区域
		float outMiniValue;//最小区域特征值
		int ouMaxIndex;//最大区域索引
		XVRegion outMaxRegion;//最大区域
		float outMaxValue;//最大区域特征值
		float outTime;//时间
	};
	//函数名称：获取最值区域
	__declspec(dllexport)int XVGetMaximumAndMinimumRegion(XVGetMaximumAndMinimumRegionIn &XVGetMaximumAndMinimumRegion_In, XVGetMaximumAndMinimumRegionOut &XVGetMaximumAndMinimumRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败 
	/*通用算法*/


	struct XVRectangleRegionIn{
		XVRectangle2D inRectangle;//矩形，软件设置默认值(origin=(0,0),angle=0,width=200,height=120)
		XVCoordinateSystem2D inAlignment;//参考坐标系
		int inFrameWidth;//有效宽度，默认值1000，若在图像中绘制区域，则将其设为图像宽
		int inFrameHeight;//有效高度，默认值1000，若在图像中绘制区域，则将其设为图像高
	};
	struct XVRectangleRegionOut{ 
		XVRegion outRegion;//矩形区域
		float outTime;//时间
	};
	//函数名称：创建矩形区域
	__declspec(dllexport)int XVRectangleRegion(XVRectangleRegionIn &XVRectangleRegion_In, XVRectangleRegionOut &XVRectangleRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	struct XVCircleRegionIn{
		XVCircle2D inCircle;//圆形，软件设置默认值(center=(50,50),radius=50)
		XVCoordinateSystem2D inAlignment;//参考坐标系
		int inFrameWidth;//有效宽度，默认值1000，若在图像中绘制区域，则将其设为图像宽
		int inFrameHeight;//有效高度，默认值1000，若在图像中绘制区域，则将其设为图像高
	};
	struct XVCircleRegionOut{
		XVRegion outRegion;//圆形区域
		float outTime;//时间
	};
	//函数名称：创建圆形区域
	__declspec(dllexport)int XVCircleRegion(XVCircleRegionIn &XVCircleRegion_In, XVCircleRegionOut &XVCircleRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	struct XVRingRegionIn{
		XVCircleFittingField inRing;//输入区域，软件须确保inRing.axis.radius>=0且inRing.width>=0
		XVCoordinateSystem2D inAlignment;//参考坐标系
		int inFrameWidth;//有效宽度，默认值1000，若在图像中绘制区域，则将其设为图像宽
		int inFrameHeight;//有效高度，默认值1000，若在图像中绘制区域，则将其设为图像高
	};
	struct XVRingRegionOut{
		XVRegion outRegion;
		float outTime;
	};
	//函数名称：创建圆环区域
	__declspec(dllexport)int XVRingRegion(XVRingRegionIn& XVRingRegion_In, XVRingRegionOut& XVRingRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	struct XVRingSectionRegionIn {
		XVCircleFittingField inRing;//输入区域，软件须确保inRing.axis.radius>0且inRing.width>0
		XVCoordinateSystem2D inAlignment;//参考坐标系
		float inStartAngle;//起始角度
		float inDeltaAngle;//相对角度
		int inNum;//分段个数，默认值1，范围：>=1的整数
		int inFrameWidth;//有效宽度，默认值1000，若在图像中绘制区域，则将其设为图像宽
		int inFrameHeight;//有效高度，默认值1000，若在图像中绘制区域，则将其设为图像高
	};
	struct XVRingSectionRegionOut {
		XVRegion outRegion;//输出区域
		float outTime;
	};
	//函数名称：创建圆环段区域
	__declspec(dllexport)int XVRingSectionRegion(XVRingSectionRegionIn& XVRingSectionRegion_In, XVRingSectionRegionOut& XVRingSectionRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法抛出异常，请查看算法日志
	//返回-2，扫描宽度太大，导致内圆半径小于0，扫描宽度必须<=2*圆半径
	//返回-3，综合角度超出360度：分段个数太多或相对角度太大

	struct XVJudgePointInRegionIn{
		XVRegion inRegion;//输入区域，软件需判断是否为空，空不执行
		XVPoint2D inPt;//输入点，软件需判断是否为空，空不执行
	};
	struct XVJudgePointInRegionOut{
		bool outIsContained;//包含标志
		float outTime;//时间
	};
	//函数名称：点在区域内
	__declspec(dllexport)int XVJudgePointInRegion(XVJudgePointInRegionIn &XVJudgePointInRegion_In, XVJudgePointInRegionOut &XVJudgePointInRegion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败


	struct XVPointsConvexHullIn{
		vector<XVPoint2D> inPoints;//输入点集
	};
	struct XVPointsConvexHullOut{
		XVPath outHull;//输出凸包
		float outHullArea;//输出凸包面积
		float outTime;//输出算法运行时间
	};
	//函数名称：点集凸包
	__declspec(dllexport)int XVPointsConvexHull(XVPointsConvexHullIn &XVPointsConvexHull_In, XVPointsConvexHullOut &XVPointsConvexHull_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败


	struct XVRegionEqualIn{
		XVRegion inRegion1;//输入区域1，软件无需判断区域是否为空
		XVRegion inRegion2;//输入区域2，软件无需判断区域是否为空
	};
	struct XVRegionEqualOut{
		bool outIsEqual;//结果标志
		float outTime;//时间
	};
	//函数名称：区域相等
	__declspec(dllexport)int XVRegionEqual(XVRegionEqualIn &XVRegionEqual_In, XVRegionEqualOut &XVRegionEqual_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败


	struct XVRegionToRegionDistanceIn{
		XVRegion inRegion1;//输入区域1，软件必须判断区域是否为空
		XVRegion inRegion2;//输入区域2，软件必须判断区域是否为空
	};
	struct XVRegionToRegionDistanceOut{
		float outDist;//区域距离
		XVSegment2D outSeg;//最短距离点对
		float outTime;//时间
	};
	//函数名称：区域距离
	__declspec(dllexport)int XVRegionToRegionDistance(XVRegionToRegionDistanceIn &XVRegionToRegionDistance_In, XVRegionToRegionDistanceOut &XVRegionToRegionDistance_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败


	struct XVRegionConvexityIn{
		XVRegion inRegion;//输入区域
	};
	struct XVRegionConvexityOut{
		float outConvexity;//输出凸度
		float outTime;//时间
	};
	//函数名称：区域凸度
	__declspec(dllexport)int XVRegionConvexity(XVRegionConvexityIn &XVRegionConvexity_In, XVRegionConvexityOut &XVRegionConvexity_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	struct XVPointsBoundingRectangleIn{
		vector<XVPoint2D> inPts;
	};
	struct XVPointsBoundingRectangleOut{
		XVRectangle2D outRect;
		float outTime;
	};
	//函数名称：点集外接矩形
	__declspec(dllexport)int XVPointsBoundingRectangle(XVPointsBoundingRectangleIn &XVPointsBoundingRectangle_In, XVPointsBoundingRectangleOut &XVPointsBoundingRectangle_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	struct XVPointsBoundingCircleIn{
		vector<XVPoint2D>inPts;
	};
	struct XVPointsBoundingCircleOut{
		XVCircle2D outCircle;
		float outTime;
	};
	//函数名称：点集外接圆
	__declspec(dllexport)int XVPointsBoundingCircle(XVPointsBoundingCircleIn &XVPointsBoundingCircle_In, XVPointsBoundingCircleOut &XVPointsBoundingCircle_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	struct XVPointsBoundingBoxIn{
		vector<XVPoint2D> inPts;
	};
	struct XVPointsBoundingBoxOut{
		XVRectangle2D outRect;
		float outTime;
	};
	//函数名称：点集外接框
	__declspec(dllexport)int XVPointsBoundingBox(XVPointsBoundingBoxIn &XVPointsBoundingBox_In, XVPointsBoundingBoxOut &XVPointsBoundingBox_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	enum XVMode {
		XM_All,//所有轮廓
		XM_External,//外轮廓
		XM_Internal//内轮廓
	};
	struct XVRegionContoursIn {
		XVRegion inRegion;//输入区域
		XVMode inMode;//轮廓模式，默认所有轮廓(XM_All)
		int inConnectivity;//连通性，软件设置下拉菜单，包含选项4和8，默认8
	};
	struct XVRegionContoursOut {
		vector<XVPath> outContours;//轮廓集合
		float outPerimeter;//区域总周长
		float outTime;//时间
	};
	//函数名称：区域轮廓周长
	__declspec(dllexport)int XVRegionContours(XVRegionContoursIn& XVRegionContours_In, XVRegionContoursOut& XVRegionContour_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败

	struct XVGetMaximumAndMinimumRegionIntegrationIn{
		XVRegion inRegion;//输入区域，软件需判断是否为空，若为空，则提示警告
		int inNeighborhood;//连通性,软件中设置下拉菜单，只有4和8两个选项，默认为8
		XVClassifyFeature inFeature;//特征，软件设置下拉菜单，默认值:面积(XVClassifyFeature::Area)
	};
	struct XVGetMaximumAndMinimumRegionIntegrationOut{
		XVRegion outMiniRegion;//最小区域
		float outMiniValue;//最小区域特征值
		XVRegion outMaxRegion;//最大区域
		float outMaxValue;//最大区域特征值
		float outTime;//时间
	};
	//函数名称：获取最值区域(集成)
	__declspec(dllexport)int XVGetMaximumAndMinimumRegionIntegration(XVGetMaximumAndMinimumRegionIntegrationIn &XVGetMaximumAndMinimumRegionIntegration_In, XVGetMaximumAndMinimumRegionIntegrationOut &XVGetMaximumAndMinimumRegionIntegration_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败 


	struct JudgeColorParam{
		float inFirstMin;  //第1通道最小值,默认值100.0
		float inFirstMax;  //第1通道最大值,默认值255.0
		float inSecondMin; //第2通道最小值,默认值0.0
		float inSecondMax; //第2通道最大值,默认值100.0
		float inThirdMin;  //第3通道最小值,默认值0.0
		float inThirdMax;  //第3通道最大值,默认值100.0
		string inColorType;//颜色名称，默认值"Red"
	};
	struct XVJudgeColorIn{
		XVImage *inImage; //输入图像
		XVRegion inRoi;   //感兴趣区域，软件无需判断是否为空
		vector<JudgeColorParam> inColorParams;//颜色参数，软件需判断是否为空，若为空，则不执行
	};
	struct XVJudgeColorOut{
		string outColorType;//颜色类型
		float outTime;//时间
	};
	//函数名称：颜色识别(RGB)
	__declspec(dllexport)int XVJudgeColor(XVJudgeColorIn &XVJudgeColor_In, XVJudgeColorOut &XVJudgeColor_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(图像为空)
	//返回-2，算法运行失败(图像非彩色)
	//返回-3，算法运行失败(颜色参数列表为空)

	struct ArrayRegionsUnionIn{
		vector<XVRegion> inRegions;
	};
	struct ArrayRegionsUnionOut{
		XVRegion outRegion;
		float outTime;
	};
	//函数名称：区域数组合并
	__declspec(dllexport)int ArrayRegionsUnion(ArrayRegionsUnionIn &ArrayRegionsUnion_In, ArrayRegionsUnionOut &ArrayRegionsUnion_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(区域数组为空)
	//返回-2，算法运行失败(异常)

	struct XVPixel{
		float ch1;
		float ch2;
		float ch3;
		float ch4;
	};
	struct XVGetImagePixelIn{
		XVImage *inImage;//图像，可以是任意通道(1、2、3、4)，不能为空
		XVPoint2DInt inPoint;//位置，不能为空
	};
	struct XVGetImagePixelOut{
		float outValue;//平均像素值
		XVPixel outPixel;//输出像素，例如，输入图像为1通道，则ch1为有效值；输入图像为3通道，则ch1、ch2、ch3为有效值
		float outTime;
	};
	//函数名称：获取图像像素
	__declspec(dllexport)int XVGetImagePixel(XVGetImagePixelIn &XVGetImagePixel_In, XVGetImagePixelOut &XVGetImagePixel_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(图像为空)
	//返回-2，算法运行失败(采样点超出图像范围)
	//返回-3，算法运行失败(异常)

	struct XVImageAverageIn{
		XVImage *inImage;//图像，可以是任意通道(1、2、3、4)，不能为空
		XVRegion inRoi;//感兴趣区域，软件无需判断是否为空
	};
	struct XVImageAverageOut{
		float outAverageValue;//图像平均值
		XVPixel outAveragePixel;//每个通道平均值
		float outTime;
	};
	//函数名称：图像像素平均
	__declspec(dllexport)int XVImageAverage(XVImageAverageIn &XVImageAverage_In, XVImageAverageOut &XVImageAverage_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(图像为空)
	//返回-2，算法运行失败(异常)

	struct XVImageSumIn{
		XVImage *inImage;//图像，可以是任意通道(1、2、3、4)，不能为空
		XVRegion inRoi;//感兴趣区域，软件无需判断是否为空
	};
	struct XVImageSumOut{
		float outSumValue;//像素和均值
		XVPixel outSumPixel;//每个通道像素和
		float outTime;
	};
	//函数名称：图像像素求和
	__declspec(dllexport)int XVImageSum(XVImageSumIn &XVImageSum_In, XVImageSumOut &XVImageSum_Out);
	//返回0，算法运行成功
	//返回-1，算法运行失败(图像为空)
	//返回-2，算法运行失败(异常)


	enum XVImageComputationType {//图像运算类型
		XVC_Add,//加，默认值
		XVC_Subtract,//减
		XVC_Difference,//差分
		XVC_And,//与
		XVC_Or,//或
		XVC_Xor,//异或
		XVC_Min,//最小值
		XVC_Max,//最大值
		XVC_Average//平均值
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
	//函数名称：图像运算
	__declspec(dllexport)int XVImageComputation(XVImageComputationIn& XVImageComputation_In, XVImageComputationOut& XVImageComputation_Out);
	//返回0，算法运行成功
	//返回-1，输入图像为空
	//返回-2，输入图像类型不一致
	//返回-3，输入图像尺寸不一致
	//返回-4，算法抛出异常

	struct XVCreateColorModelIn {
		XVImage* inImage;//输入图像
		XVRegion inRoi;//学习区域，默认全图
		std::string inColorName;//模板颜色名称
	};
	struct XVCreateColorModelOut {
		int outHistogramHue[360];//模板色相直方图
		int outHistogramSaturation[256];//模板饱和度直方图
		std::string outColorName;//模板颜色名称
		float outTime;//时间
	};
	//函数名称：创建颜色模板
	__declspec(dllexport)int XVCreateColorModel(XVCreateColorModelIn& XVCreateColorModel_In, XVCreateColorModelOut& XVCreateColorModel_Out);
	//返回0，算法运行成功
	//返回-1，图像为空
	//返回-2，模板图像必须是彩色图像

	enum XVDistanceMeasuring {
		XVD_Euclidean,//欧氏距离
		XVD_Manhattan//曼哈顿距离
	};
	struct XVColorIdentificationIn {
		XVImage* inImage;//待识别图像
		XVRegion inRoi;//感兴趣区域，默认空区域(全图)
		vector<XVCreateColorModelOut> inModels;//颜色模板
		XVDistanceMeasuring inMeasuring;//距离测量方式
	};
	struct XVResultInfo {
		std::string name;//颜色名称
		float score;//分数，表示当前图像判定为该颜色的概率
	};
	struct XVColorIdentificationOut {
		vector<XVResultInfo> outResults;//识别结果信息，已按得分降序排列
		int outCurrentHistogramHue[360];//色相直方图
		int outCurrentHistogramSaturation[255];//饱和度直方图
		float outTime;//时间
	};
	//函数名称：颜色识别(模板)
	__declspec(dllexport)int XVColorIdentification(XVColorIdentificationIn& XVColorIdentification_In, XVColorIdentificationOut& XVColorIdentification_Out);
	//返回0，算法运行成功
	//返回-1，图像为空
	//返回-2，不是彩色图像
	//返回-3，颜色模型为空

	struct XVThresholdDynamicIn {
		XVImage* inImage;//输入图像，彩色/灰度图像均可
		XVRegion inRoi;//输入感兴趣区域，可以为空
		int inRadiusX;//矩形邻域宽的一半，软件中设置默认值3，范围[0,50]
		int inRadiusY;//矩形邻域高的一半，软件中设置默认值3，范围[0，50]
		int inMinThre;//最小阈值，软件中设置默认值-5，范围[-255,255]
		int inMaxThre;//最大阈值，软件中设置默认值5，范围[-255,255]
	};
	struct XVThresholdDynamicOut {
		XVRegion outRegion;//输出区域
		float outTime;//时间
	};
	//函数名称：动态阈值化
	__declspec(dllexport)int XVThresholdDynamic(XVThresholdDynamicIn& XVThresholdDynamic_In, XVThresholdDynamicOut& XVThresholdDynamic_Out);
	//返回0，算法运行成功
	//返回-1，图像为空

	enum XVTransformationType {//图像几何变换类型
		Mirror,//镜像
		Shift,//平移
		Scale,//缩放
		Rotate,//旋转
		Affine//仿射
	};
	enum XVInterpolationMethod {//插值法
		NearestNeighbor,//最近邻
		Bilinear//双线性
	};
	enum XVMirrorType {//镜像类型
		VerticalMirror,//垂直镜像
		HorizonalMirror,//水平镜像
		RotateMirror//旋转镜像
	};
	struct XVGeometricTransformationIn {
		XVImage* inImage;//输入图像，灰度或彩色图像
		XVRectangle2D inRoi;//感兴趣区域
		XVTransformationType inTransformationType;//变换类型，默认平移模式(Shift)
		XVInterpolationMethod inInterpolation;//插值法，默认最近邻(NearestNeighbor)

		//仅镜像模式下开放
		XVMirrorType inMirrorType;//镜像类型，默认垂直镜像(VerticalMirror)

		//仅仿射、平移模式下开放
		int inShiftX;//x方向平移距离，默认0
		int inShiftY;//y方向平移距离，默认0

		//仅仿射、缩放模式下开放
		float inScale;//缩放比例，默认1.0，范围[0.1,10.0]

		//仅仿射、旋转模式下开放
		float inAngle;//旋转角度，默认0.0
	};
	struct XVGeometricTransformationOut {
		XVImage outImage;//输出图像
		float outTime;//时间
	};
	//函数名称：图像几何变换
	__declspec(dllexport)int XVGeometricTransformation(XVGeometricTransformationIn& XVGeometricTransformation_In, XVGeometricTransformationOut& XVGeometricTransformation_Out);
	//返回0，算法运行成功
	//返回-1，图像为空
	//返回-2，输出图像太大，导致内存分配失败

	//归一化类型枚举
	enum XVImageNormalizationType {
		HistogramEqualization,//直方图均衡化
		HistogramNormalization,//直方图归一化
		AveStandardDeviationNormalization//均值标准差归一化
	};
	struct XVImageNormalizationIn {
		XVImage* inImage;//输入图像，必须是灰度图像
		XVImageNormalizationType  inType;//归一化类型，设置默认值：直方图均衡化(HistogramEqualization)

		/*仅在选择"直方图归一化"类型时显示*/
		//必须保证左右端比例之和不超过1.0，例如左端比例为0.6,右端比例为0.7，虽然满足各自的范围条件，但是比例之和为1.3超过了1.0，此时上位机应将右端比例强行修改为1-0.6=0.4
		float inLeftProportion;//左端像素忽略比例,默认0.0，范围[0.0,1.0]
		float inRightProportion;//右端像素忽略比例,默认0.0,范围[0.0,1.0]
		int inTargetMinValue;//目标最小灰度值，默认0，范围[0,255]
		int inTargetMaxValue;//目标最大灰度值，默认255，范围[0,255]
		/*仅在选择"直方图归一化"类型时显示*/

		/*仅在选择"均值标准差归一化"类型时显示*/
		float inTargetAverage;//目标均值，默认125.0，范围[0.0，255.0]
		float inTargetStandardDeviation;//目标标准差，默认20.0，范围[0.0，255.0]
		/*仅在选择"均值标准差归一化"类型时显示*/
	};
	struct XVImageNormalizationOut {
		XVImage outImage;//归一化后的图像
		float outTime;//时间
	};
	//函数名称：图像归一化
	__declspec(dllexport)int XVImageNormalization(XVImageNormalizationIn& XVImageNormalization_In, XVImageNormalizationOut& XVImageNormalization_Out);
	//返回0，算法运行成功
	//返回-1，输入图像为空
	//返回-2，输入图像必须是灰度图像

	struct XVMergingImagesIn {
		XVImage* inImage;//输入图像
		int inRows;//行数，默认2，范围[1,10]
		int inCols;//列数，默认2，范围[1,10]
		int inIndex;//索引，默认0，范围[0,inRows*inCols)
	};
	struct XVMergingImagesOut {
		XVImage outImage;//
		float outTime;//时间
	};
	//函数名称：
	__declspec(dllexport)int XVMergingImages(XVMergingImagesIn& XVMergingImages_In, XVMergingImagesOut& XVMergingImages_Out);
	//返回0，算法运行成功
	//返回-1，输入图像为空

	struct XVRegionInnerBoxIn {
		XVRegion inRegion;//输入区域
		int inMinWidth;//内接框最小宽度，默认值：1
		int inMaxWidth;//内接框最大宽度，默认值：999999
		int inMinHeight;//内接框最小高度，默认值：1
		int inMaxHeight;//内接框最大高度，默认值：999999
	};
	struct XVRegionInnerBoxOut {
		XVBox outBox;//输出内接框
		float outTime;//算法运行时间,单位ms
	};
	//函数名称：区域内接框
	__declspec(dllexport)int XVRegionInnerBox(XVRegionInnerBoxIn& XVRegionInnerBox_In, XVRegionInnerBoxOut& XVRegionInnerBox_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空

	struct XVResizeRegionIn {
		XVRegion inRegion;
		int inNewWidth;
		int inNewHeight;
	};
	struct XVResizeRegionOut {
		XVRegion outRegion;
		float outTime;
	};
	//函数名称：区域缩放
	__declspec(dllexport)int XVResizeRegion(XVResizeRegionIn& XVResizeRegion_In, XVResizeRegionOut& XVResizeRegion_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空


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
	//函数名称：区域膨胀
	__declspec(dllexport)int XVRegionDilate(XVDilateIn& XVDilate_In, XVDilateOut& XVDilate_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空

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
	//函数名称：区域腐蚀
	__declspec(dllexport)int XVRegionErode(XVErodeIn& XVErode_In, XVErodeOut& XVErode_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空

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
	//函数名称：区域膨胀(闭)
	__declspec(dllexport)int XVRegionDilateOfClose(XVDilateOfCloseIn& XVDilate_In, XVDilateOfCloseOut& XVDilate_Out);
	//返回0，算法运行成功
	//返回-1，区域输入为空
	
	struct XVCompose3In {
		XVImage* inImage1;
		XVImage* inImage2;
		XVImage* inImage3;
	};
	struct XVCompose3Out {
		XVImage outImage;
		float outTime;
	};
	//函数名称：创建三通道图像
	__declspec(dllexport)int XVCompose3(XVCompose3In& XVCompose3_In, XVCompose3Out& XVCompose3_Out);
	//返回0，算法运行成功
	//返回-1，输出图像太大，内存分配失败
	//返回-2，输入图像必须是灰度图像
	//返回-3，输入图像必须尺寸相同
	//返回-4，输入图像不能为空

	struct XVSetImagePixelsIn {
		XVImage* inImage;
		XVRegion inRoi;
		XVPixel inPixel;//灰度图像仅需设置inPixel.ch1
	};
	struct XVSetImagePixelsOut {
		XVImage outImage;
		float outTime;
	};
	//函数名称：设置像素值
	__declspec(dllexport)int XVSetImagePixels(XVSetImagePixelsIn& XVSetImagePixels_In, XVSetImagePixelsOut& XVSetImagePixels_Out);
	//返回0，算法运行成功
	//返回-2，输入图像为空

	struct XVTileImageOffsetIn {
		vector<XVImage> inImgs;
	};
	struct XVTileImageOffsetOut {
		XVImage outImage;
		float outTime;
	};
	//函数名称：图像拼接
	__declspec(dllexport)int XVTileImageOffset(XVTileImageOffsetIn& XVTileImageOffset_In, XVTileImageOffsetOut& XVTileImageOffset_Out);
	//返回0，算法运行成功
}
#endif