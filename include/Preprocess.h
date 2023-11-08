#ifndef PREPROCESS_H
#define PREPROCESS_H

/*************************************************
*
*             2D算法库预处理函数头文件
*           Created on 2022.5.31 by wangxinping
*
*************************************************/

#include "XVBase.h"

namespace XVL
{
	//----------------------------------------------------------------------滤波算子----------------------------------------------------------------------

	typedef struct XVGaussianSmoothIn//高斯滤波平滑函数输入参数
	{
		XVImage* inImage;//输入图像
		XVRegion inRegion;//输入区域
		int inKernelWidth;//内核宽度，其内核的宽度必须为正数和奇数或者为0
		int inKernelHeight;//内核高度，其内核的高度都必须为正数和奇数或者为0
		float inStdDevX;//高斯核函数在X方向的标准偏差
		float inStdDevY;//高斯核函数在Y方向的标准偏差
	}XVGaussianSmoothIn;

	typedef struct XVGaussianSmoothOut//高斯滤波平滑函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outImage;//输出结果图像
		float outTime;//耗时
	}XVGaussianSmoothOut;

	typedef struct XVMedianSmoothIn//中值滤波平滑函数输入参数
	{
		XVImage* inImage;//输入图像
		XVRegion inRegion;//输入区域
		int inKernel;//孔径的线性尺寸，注意这个参数必须是大于1的奇数,默认值为3
	}XVMedianSmoothIn;

	typedef struct XVMedianSmoothOut//中值滤波平滑函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outImage;//输出结果图像
		float outTime;//耗时
	}XVMedianSmoothOut;

	typedef struct XVMeanSmoothIn//均值滤波平滑函数输入参数
	{
		XVImage* inImage;//输入图像
		XVRegion inRegion;//输入区域
		int inKernelWidth;//内核宽度，其内核的宽度必须为正数和奇数或者为0
		int inKernelHeight;//内核高度，其内核的高度都必须为正数和奇数或者为0
		XVPoint2DInt inAnchor;//表示锚点（即被平滑的那个点），注意它有默认值XVPoint2DIntPoint（-1，-1），如果这个点坐标是负值，就表示取核的中心为锚点，所以默认值XVPoint2DInt（-1，-1）表示这个锚点在核的中心
	}XVMeanSmoothIn;

	typedef struct  XVMeanSmoothOut//均值滤波平滑函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outImage;//输出结果图像
		float outTime;//耗时
	} XVMeanSmoothOut;

	//----------------------------------------------------------------------空间转换算子----------------------------------------------------------------------

	typedef struct XVRgbToGrayIn//Rgb转灰度函数输入参数
	{
		XVImage* inRgbImage;
	}XVRgbToGrayIn;

	typedef struct XVRgbToGrayOut//Rgb转灰度函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outGrayImage;//输出图像
		float outTime;//耗时
	}XVRgbToGrayOut;

	typedef struct XVRgbToHsvIn//Rgb转Hsv函数输入参数
	{
		XVImage* inRgbImage;
	}XVRgbToHsvIn;

	typedef struct XVRgbToHsvOut//Rgb转Hsv函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outHsvImage;//输出图像
		float outTime;//耗时
	}XVRgbToHsvOut;

	typedef struct XVHsvToRgbIn//Hsv转Rgb函数输入参数
	{
		XVImage* inHsvImage;
	}XVHsvToRgbIn;

	typedef struct XVHsvToRgbOut//Hsv转Rgb函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outRgbImage;//输出图像
		float outTime;//耗时
	}XVHsvToRgbOut;

	typedef struct XVRgbToYuvIn//Rgb转Yuv函数输入参数
	{
		XVImage* inRgbImage;
	}XVRgbToYuvIn;

	typedef struct XVRgbToYuvOut//Rgb转Yuv函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outYuvImage;//输出图像
		float outTime;//耗时
	}XVRgbToYuvOut;

	typedef struct XVYuvToRgbIn//Yuv转Rgb函数输入参数
	{
		XVImage* inYuvImage;
	}XVYuvToRgbIn;

	typedef struct XVYuvToRgbOut//Yuv转Rgb函数输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outRgbImage;//输出图像
		float outTime;//耗时
	}XVYuvToRgbOut;


	typedef struct XVRgbToHsiIn//Rgb转Hsi输入参数
	{
		XVImage inImage;//输入图像
	}XVRgbToHsiIn;

	typedef struct XVRgbToHsiOut//Rgb转Hsi输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage outImage;//输出图像
		float outTime;//函数执行耗时
	}XVRgbToHsiOut;

	typedef struct XVHsiToRgbIn//Hsi转Rgb输入参数
	{
		XVImage inImage;//输入图像
	}XVHsiToRgbIn;

	typedef struct XVHsiToRgbOut//Hsi转Rgb输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage outImage;//输出图像
		float outTime;//函数执行耗时
	}XVHsiToRgbOut;

	//----------------------------------------------------------------------旋转镜像----------------------------------------------------------------------

	enum MirrorDirection
	{
		Horizontal, //水平
		Vertical,  //垂直
		Both       //水平垂直
	};

	typedef struct XVMirrorImageIn//镜像图像输入参数
	{
		XVImage* inImage;//输入图像
		MirrorDirection inMirrorDirection;//镜像方向
	}XVMirrorImageIn;

	typedef struct XVMirrorImageOut//镜像图像输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outImage;//输出图像
		float outTime;//耗时
	}XVMirrorImageOut;

	enum RotateAngle
	{
		Ninety,//顺时针90度
		OneHundredAndEighty,//顺时针180度
		TwoHundredAndSeventy//顺时针270度
	};

	typedef struct XVRotateImageIn//旋转图像输入参数
	{
		XVImage* inImage;//输入图像
		RotateAngle inRotateAngle;//旋转角度
	}XVRotateImageIn;

	typedef struct XVRotateImageOut//旋转图像输出参数
	{
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage* outImage;//输出图像
		float outTime;//耗时
	}XVRotateImageOut;

	//----------------------------------------------------------------------其他预处理----------------------------------------------------------------------
	
	typedef struct XVBrightnessCorrectionIn//亮度校正输入参数
	{
		XVImage inImage;//输入图像
		int inGain;//增益，调节该系数会使得图像画面整体像素亮度提高，默认值为0，调节范围0-100
		int inCompensation;//补偿，调节该系数使得画面的像素整体加或者减该数值，默认值为0，调节范围-255到255
	}XVBrightnessCorrectionIn;

	
	typedef struct XVBrightnessCorrectionOut//亮度校正输出参数
	{
		int outResult;//执行结果，1代表函数执行成功，2代表函数执行失败
		XVImage outImage;//亮度校正后的结果图像
		float outTime;//函数执行耗时
	}XVBrightnessCorrectionOut;

	enum CopyAndFillType
	{
		Copy,//拷贝
		Fill//填充
	};
	
	typedef struct XVCopyAndFillIn//拷贝填充输入参数
	{
		XVImage inImage;//输入图像
		XVRegion inRoi;//感兴趣区域，若区域为空，则默认全图
		CopyAndFillType inCopyAndFillType;//拷贝填充处理类型，主要分拷贝和填充两种类型
		int inRegionInnerGrayValue;//区域内填充值，范围0-255
		int inRegionOuterGrayValue;//区域外填充值，范围0-255
		//bool isOpenAlignment;//是否启用局部坐标系
		XVCoordinateSystem2D alignment;//局部坐标系参数
	}XVCopyAndFillIn;

	typedef struct XVCopyAndFillOut//拷贝填充算子输出参数
	{
		int outResult;//执行结果，1代表函数执行成功，2代表函数执行失败
		XVRegion outRegion;//roi区域(若启用局部坐标系，则是roi变换后的区域)
		XVImage outImage;//输出图像
		float outTime;//函数执行耗时
	}XVCopyAndFillOut;

	typedef struct XVMultipleImageMeanIn//帧平均输入参数
	{
		std::vector<XVImage> inImages;//输入图像
		XVRectangle2D inRoi;//感兴趣区域
	}XVMultipleImageMeanIn;
	
	typedef struct XVMultipleImageMeanOut//帧平均输出参数
	{
		int outResult;//执行结果，1代表函数执行成功，2代表函数执行失败
		XVImage outImage;//输出图像
		float outTime;//函数执行耗时
	}XVMultipleImageMeanOut;

	typedef struct xvColorParam
	{
		float H_min;//H最小值
		float H_max;//H最大值
		float S_min;//S最小值
		float S_max;//S最大值
		float V_min;//V最小值
		float V_max;//V最大值
		std::string colorName;//颜色名称
	}xvColorParam;

	//颜色识别(HSV)输入参数
	typedef struct XVHsvColorDiscriminationIn
	{
		XVImage* inRgbImage;//输入彩色图像
		XVRegion inRoi;//感兴趣区域，关闭软件后感兴趣区域需保存下来
		vector<xvColorParam> inColorOption;//具体参数可参考EDU版本，有11种初始化颜色类型
	}XVHsvColorDiscriminationIn;

	//颜色识别(HSV)输出参数
	typedef struct XVHsvColorDiscriminationOut
	{
		float outTime;//函数耗时
		int outResult;//函数执行结果，1为OK，2为NG
		std::string outColorName;//输出颜色名称
	}XVHsvColorDiscriminationOut;

	//颜色通道分离输入参数
	typedef struct XVSplitChannelsIn
	{
		XVImage inImage;//输入三通道图像
	}XVSplitChannelsIn;

	//颜色通道分离输出参数
	typedef struct XVSplitChannelsOut
	{
		float outTime;//函数耗时
		int outResult;//函数执行结果，1为OK，2为NG
		XVImage outImage1;//第一通道图像
		XVImage outImage2;//第二通道图像
		XVImage outImage3;//第三通道图像
	}XVSplitChannelsOut;


	//彩色图像转灰度图像算子
	//Rgb转灰度图像
	_declspec(dllexport) void XVRgbToGray(XVRgbToGrayIn& rgbToGrayIn, XVRgbToGrayOut& rgbToGrayOut);
	//Rgb转Hsv图像
	_declspec(dllexport) void XVRgbToHsv(XVRgbToHsvIn& rgbToHsvIn, XVRgbToHsvOut& rgbToHsvOut);
	//Hsi转Rgb图像
	_declspec(dllexport) void XVHsvToRgb(XVHsvToRgbIn& hsvToRgbIn, XVHsvToRgbOut& hsvToRgbOut);
	//Rgb转Yuv图像
	_declspec(dllexport) void XVRgbToYuv(XVRgbToYuvIn& rgbToYuvIn, XVRgbToYuvOut& rgbToYuvOut);
	//Yuv转Rgb图像
	_declspec(dllexport) void XVYuvToRgb(XVYuvToRgbIn& yuvToRgbIn, XVYuvToRgbOut& yuvToRgbOut);
	//Rgb转Hsi图像
	_declspec(dllexport) void XVRgbToHsi(XVRgbToHsiIn& rgbToHsiIn, XVRgbToHsiOut& rgbToHsiOut);
	//Hsi转Rgb图像
	_declspec(dllexport) void XVHsiToRgb(XVHsiToRgbIn& hsiToRgbIn, XVHsiToRgbOut& hsiToRgbOut);

	//滤波算子
	//高斯滤波
	_declspec(dllexport) void XVGaussianSmooth(XVGaussianSmoothIn& gaussianSmoothIn, XVGaussianSmoothOut& gaussianSmoothOut);
	//中值滤波
	_declspec(dllexport) void XVMedianSmooth(XVMedianSmoothIn& medianSmoothIn, XVMedianSmoothOut& medianSmoothOut);
	//均值滤波
	_declspec(dllexport) void XVMeanSmooth(XVMeanSmoothIn& meanSmoothIn, XVMeanSmoothOut& meanSmoothOut);

	//图像镜像/旋转算子
	//图像镜像算子
	_declspec(dllexport) void XVMirrorImage(XVMirrorImageIn& mirrorImageIn, XVMirrorImageOut& mirrorImageOut);
	//图像旋转算子
	_declspec(dllexport) void XVRotateImage(XVRotateImageIn& rotateImageIn, XVRotateImageOut& rotateImageOut);

	//其他预处理算子
	//亮度校正(outGrayValue=(1+inGain*0.1)*inGrayValue+inCompsation)
	_declspec(dllexport) void XVBrightnessCorrection(XVBrightnessCorrectionIn& brightnessCorrectionIn, XVBrightnessCorrectionOut& brightnessCorrectionOut);

	//拷贝填充算子(不限制灰度图像还是彩色图像，功能类似于抠图)
	_declspec(dllexport) void XVCopyAndFill(XVCopyAndFillIn& copyAndFillIn, XVCopyAndFillOut& copyAndFillOut);

	//帧平均算子
	_declspec(dllexport) void XVMultipleImageMean(XVMultipleImageMeanIn& multipleImageMeanIn, XVMultipleImageMeanOut& multipleImageMeanOut);

	//颜色识别(HSV)算子
	_declspec(dllexport) void XVHsvColorDiscrimination(XVHsvColorDiscriminationIn& hsvColorDiscriminationIn, XVHsvColorDiscriminationOut& hsvColorDiscriminationOut);

	//颜色通道分离算子
	_declspec(dllexport) void XVSplitChannels(XVSplitChannelsIn& splitChannelsIn, XVSplitChannelsOut& splitChannelsOut);
}

#endif // !PREPROCESS_H
