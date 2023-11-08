#ifndef VISIONCAMERAPUB_H
#define VISIONCAMERAPUB_H

#include <QMetaType>
#include "blockingconcurrentqueue.h"
#include <functional>
#include <QString>
#include <vector>
#include <QDebug>
#include <atomic>
using namespace std;

typedef signed short        INT16;
typedef signed int          INT32;
typedef signed __int64      INT64;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned __int64    UINT64;


typedef enum VInt
{
    Success = 0,
    OriginalValue =10,                            //初始值
    ErrValidAPI =20,                               //无效的接口
    ErrGerneralParaConfig = 25,             //常规参数设置出错
    ErrInitCamera = 30,                         //初始化相机时出错
    ErrNoExsitCameraPath = 40,           //本地相机目录不存在
    ErrNoExsitPic = 50,                         //本地相机目录下不存在bmp格式图像
    ErrFindImageInput,                         //未找到输入的图像
    ErrOutofImageRange,                      //超出本地图像序列范围
    ErrNullCamera = 60,                       //不存在相机对象
    ErrNullStreamSource = 70,             //不存在StreamSourcePtr对象
    ErrNullAcquisitionControl = 80,      //不存在AcquisitionControlPtr对象
    ErrNullDigitalIOControl,                 //不存在DigitalIOCtrlPtr对象
    ErrNullAnalogControl,                    //不存在AnalogControlPtr对象
    ErrNullTransportLayerControl,        //不存在TransportLayerControlPtr对象
    ErrNullImageFormatControl,            //不存在ImageFormatControl对象
    ErrNullBuffers = 90,                        //不存在Buffers对象
    ErrNullXfer = 100,                           //不存在传输对象
    ErrFindCamera = 110,                     //搜索相机时出错
    ErrGetCameraInfo = 111,                 //获取相机信息出错
    ErrConnectCamera = 120,               //连接相机时出错
    ErrCameraDisconnected,                 //相机未连接
    ErrDisConnectCamera = 130,          //断开连接相机时出错
    ErrStartGrabbing = 140,                  //启动相机帧流时出错
    ErrStopGrabbing = 150,                  //停止相机帧流时出错
    ErrValidFrame = 160,                      //采图无效
    ErrAttachGetFrame = 170,               //注册回调函数出错
    ErrDetachGetFrame = 180,              //注销回调函数出错
    ErrSoftExecute = 190,                     //软触发执行出错
    ErrSetExposureLevel = 200,             //设置曝光等级出错
    ErrSetAutoExposureMode,             //设置自动曝光出错
    ErrGetAutoExposureMode,             //获取自动曝光出错
    ErrSetExpectedLightness,               //设置期望亮度出错
    ErrGetExpectedLightness,               //获取期望亮度出错
    ErrSetExposureTime = 210,             //设置曝光时间出错
    ErrSetExposureTimeAuto = 211,       //设置自动曝光时间出错
    ErrGetExposureTime = 220,             //获取曝光时间出错
    ErrGetExposureTimeAuto = 221,       //获取自动曝光时间出错
    ErrSetCameraStaticIP = 230,           //设置相机静态IP出错
    ErrSetCameraDynamicIP = 230,      //设置相机动态IP出错
    ErrGetCameraStaticIP ,                    //获取相机静态IP出错
    ErrCreateBuffer = 240,                    //创建相机缓存区对象出错
    ErrCreateXfer = 250,                       //创建相机传输对象出错
    ErrSetTriggerMode = 260,               //设置触发模式出错
    ErrGetTriggerMode,                         //获取触发模式出错
    ErrSetLineAcquisitionMode,             //设置线触发模式出错
    ErrSetUserDefinedID = 270,            //设置相机ID出错
    ErrGetUserDefinedID,                      //获取相机ID出错
    ErrCameraDequeue = 280,              //图片出队失败
    ErrSelectLine = 290,                        //选择线路出错
    ErrSelectLineSource,                       //选择线路输出源出错
    ErrSetLine = 300,                            //设置线路出错
    ErrSetQueueVertify = 310,              //设置队列检验出错
    ErrSetGain = 320,                           //设置增益出错
    ErrSetGainAuto = 321,                   //设置自动增益出错
    ErrGetGain = 325,                           //获取增益出错
    ErrGetGainAuto = 326,                    //获取自动增益出错
    ErrSelectGainSelector,                    //选择增益选择器出错
    ErrSetIoInput = 330,                       //设置IO输入出错
    ErrSetIoLineInverter,                       //设置IO线路反转出错
    ErrSetIoOutput = 340,                    //设置IO输出出错
    ErrSetUserOutputValueAll = 343,   //设置用户IO输出值出错
    ErrSetIOFilterTime = 345,               //设置IO滤波时间出错
    ErrGetIOFilterTime = 346,               //获取IO滤波时间出错
    ErrSetIOTrigInMode = 347,              //设置IO触发模式出错
    ErrGetIOTrigInMode = 348,              //获取IO触发模式出错
    ErrLoadXmlFile = 350,                    //载入xml文档出错
    ErrFindXmlNode = 360,                  //搜索xml节点出错
    ErrSetXmlParameter = 370,            //xml参数内容有误
    ErrSetImageWidth = 380,                //设置相机图像宽度出错
    ErrGetImageWidth = 381,                //获取相机图像宽度出错
    ErrSetImageHeight = 382,                //设置相机图像高度出错
    ErrGetImageHeight = 383,                //获取相机图像高度出错
    ErrSetImageOffsetX = 384,               //设置相机图像水平偏移出错
    ErrGetImageOffsetX = 385,               //获取相机图像水平偏移出错
    ErrSetImageOffsetY= 386,                //设置相机图像垂直偏移出错
    ErrGetImageOffsetY = 387,               //获取相机图像垂直偏移出错
    ErrGetImageSize = 385,                   //获取相机图像大小出错
    ErrSetPixelFormat = 390,                //获取相机图像格式出错
    ErrGetPixelFormat = 391,                //获取相机图像格式出错
    ErrSetTriggerDelay = 400,                //设置触发延时出错
    ErrGetTriggerDelay = 401,               //获取触发延时出错
    ErrSetTriggerActivation = 405,         //设置触发边沿激活出错
    ErrGetTriggerActivation = 406,         //获取触发边沿激活出错
    ErrSetResolution = 410,                 //设置图像分辨率出错
    ErrGetResolution = 411,                 //获取图像分辨率出错
    ErrSetFrameRate = 420,                 //设置图像帧率出错
    ErrGetFrameRate = 421,                 //获取图像帧率出错
    ErrSetBalanceWhiteAuto = 430,       //设置图像帧率出错
    ErrGetBalanceWhiteAuto = 431,       //获取图像帧率出错
    ErrSetAcquisitionLineRate = 440,     //设置采集线速率出错
    ErrGetAcquisitionLineRate = 441,     //获取采集线速率出错
}ErrCode;

/**
 * @brief       相机的设备信息
 */
struct CameraDeviceInfo
{
    QString vendorName = "";
    QString modelName = "";
    QString serialNumber = "";
    QString ipAddress = "";
    QString macAddress = "";
};

/**
 * @brief       相机工作模式
 */
enum CameraWork
{
    WorkFreeAcquire = 0,         //自由采集
    WorkSoftTrigger,                 //软触发
    WorkLineTrigger,                //硬触发
    WorkSoftOrLineTrigger,     //软触发或者硬触发模式，即需要触发模式，相对于自由采集(仅用于返回值通知)
    UnknownWork,                  //出错
};

/**
 * @brief       相机边沿激活触发项
 */
enum CameraTriggerActivation
{
    RisingEdge = 0,                    //上升沿触发
    FallingEdge,                         //下降沿触发
    AnyEdge,                             //任何边沿都触发 (少部分相机支持)
    UnknownTriggerActivation,   //出错
};

/**
 * @brief       相机种类
 */
enum CameraType
{
    Local =0,//本地相机
    DaHua,
    Basler,
    Dalsa,
    Lucid,
    LH,
   UnKnownType,
};

/**
 * @brief       相机 IO 线路
 * @note       dahua: 输入: Line1; 输出: Line0
 * @note       dalsa: 输入: Line1, Line2;  输出: Line3, Line4
 * @note       basler: 输入: Line1...CC4; 输出: Out1...Out4
 * @note       LH智能相机: 输入: Line1...Line4; 输出: Out1...Out4
 */
enum CameraLine
{
    Line0,
    Line1,
    Line2,
    Line3,
    Line4,
    CC1,
    CC2,
    CC3,
    CC4,
    Out1,
    Out2,
    Out3,
    Out4,
    UnkownLine
};

/**
 * @brief       相机触发源
 */
enum CameraTriggerSource
{
    Software,                             //软触发
    Line1_source,                       //线路1
    Line2_source,                       //线路2
    Line3_source,                       //线路3
    ShaftEncoderModuleOut,      //编码器输出
    FrequencyConverter,             //频率转换器
    Action1,
    Action2,
};

// 相机线路输出源(dalsa)
enum CameraOutputLineSource
{
    //dalsa相机
    OutputOff,                             //关闭
    SoftwareControlled,               //软件控制触发
    PulseOnEndofExposure,       //曝光完成触发
    PulseOnStartofExposure,      //曝光开始触发

    //大华相机&basler相机
    ExposureActive,                    //曝光触发
    FrameTriggerWait,                //帧触发等待
    AcquisitionTriggerWait,         //采集触发等待
    UserOutput0,                        //用户输出0
    UserOutput1,

    //大华相机
    Timer0Active,                        //定时器0触发
    LightTrigger,                          //光触发

    //basler相机
    TimerActive,
    UserOutput,
    UserOutput2,
    TriggerReady,
    AcquisitionTriggerReady,
    FlashWindow1,

    UnknownOutputLineSource,  //错误的输出源
};


/**
 * @brief       相机曝光级别
 */
enum CameraExposureLevel
{
    FixedExposure,              //固定曝光  （注意： DALSA相机固定曝光有上限 33246）
    TwoExposure,                //二段曝光
    ThreeExposure,              //三段曝光
    FourExposure,               //四段曝光
    UnknownExposureLevel
};

/**
 * @brief       相机白平衡模式
 */
enum BalanceWhiteAuto
{
    BalanceWhite_Off,
    BalanceWhite_Once,
    BalanceWhite_Continuous,
    UnknownMode,
};

/**
 * @brief       相机中获取图像的方式
 */
enum ImageQueueMode
{
    QueueFirstInFirstOut,     //先进先出
    QueueLasterImage,          //只获取最新图像
};

/**
 * @brief       相机的图像格式
 */
enum PixelFormat
{
    format_Mono8,               //8位灰度图
    format_RGB,                  //一般彩色格式
    format_BayerBG8,
    format_BayerRG8,
    format_YUV422Packed,

    //WP智能相机
    WP_FORMAT_YUV420SP ,
    WP_FORMAT_YUV422SP,
    WP_FORMAT_BGR24,
    WP_FORMAT_MONO,
    WP_FORMAT_BAYER,

    UnknownFormat,
};

//智能相机滤波对象ID
enum WPCameraFilterTimeID
{
    WP_IOIuput_0,               //输入1接口
    WP_IOIuput_1,
    WP_IOIuput_2,
    WP_IOIuput_3,
    WP_IOIuput_4,
    WP_IOIuput_5,
    WP_IOIuput_6,
    WP_IOIuput_7,
    WP_IOIuput_Trigger,       //触发接口
    WP_IOIuput_All,              //所有输入接口
};

//相机IO触发模式
enum CameraIOTrigInMode
{
    IOTrigInMode_close,         //关闭
    IOTrigInMode_Rising,       //上升沿触发
    IOTrigInMode_Falling,      //下降沿触发
    IOTrigInMode_Both,         //双边沿触发
    UnknownTrigInMode,
};

/**
 * @brief       相机增益选择器
 */
enum CameraGainSelector
{
    SensorAnalog,     //模拟传感器
    SensorDigital,     //数字传感器
    DigitalAll,           //所有数字传感器
    UknownGainSelector,
};

/**
 * @brief       相机增益信息
 */
struct CameraGainInfo
{
    CameraGainSelector gainSelector = SensorAnalog;
    UINT32 gain = 1;
};


//moodycamel::BlockingConcurrentQueue<T>类型的队列出队
template<typename T>
static void dequeue_until(moodycamel::BlockingConcurrentQueue<T> & queue,
                          int maxsize,	std::function<void(void*)> fn = nullptr)
{
    int c = queue.size_approx() - maxsize;
    while (c>0)
    {
        c--;
        T val;
        queue.wait_dequeue(val);
        if (fn)
            fn(&val);
    }
}

static vector<string> splitPart(string str, string pattern)
{
    int pos;
    vector<string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i<size; i++)
    {
        pos = str.find(pattern, i);
        if (pos<size)
        {
            string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

struct XYZ
{
    int x;
    int y;
    int z;
};

typedef struct FrameInfoData{
public:
    ~FrameInfoData(){
        if (data != nullptr){
            free(data);
            data = nullptr;
        }
    }
    int isValid = 3;                        //0: 有效；1: 无效数据a(补的空数据)；2：无效数据b(连续5次无效数据a后再补一帧数据，提示相机采图异常); 3: 初始值
    int pixelDigit = 0;
    int color = 0;
    int width = 0;
    int height = 0;
    int index = 0;                           //表示：当前图像所在的位置索引(仅在本地相机中有意义)
    char* data = nullptr;
    std::string name = "";               //表示：xml中配置的"camera1", "camera2"
    std::string cameraID = "";         //表示：相机的连接ID号
    QAtomicInt refCount;               //引用计数
}FrameInfoData;

struct FrameInfo
{
public:
    FrameInfo(){}
    FrameInfo(char *data, int width, int height, int color = 1, int isValid = 0, string cameraID = "", string name = "", int index = 0){
        d = new FrameInfoData();
        d->data = data;
        d->width = width;
        d->height = height;
        d->color = color;
        d->isValid = isValid;
        d->index = index;
        d->name = name;
        d->cameraID = cameraID;
        d->refCount.ref();
    }
    //执行拷贝构造时执行（进队列时也执行）
    FrameInfo(const FrameInfo &info){
        d = info.d;
        if (d)
            d->refCount.ref();
    }
    //赋值操作时执行（出队列时也执行）
    FrameInfo& operator =(const FrameInfo &info){
        if (info.d)
            info.d->refCount.ref();
        if (d && !d->refCount.deref()){
            delete d;
            d = nullptr;
        }
        d = info.d;
        return *this;
    }
    ~FrameInfo(){
        if (d && !d->refCount.deref()){
            delete d;
            d = nullptr;
        }
    }
    int isValid() const { return d ? d->isValid : 3; }
    int width() const { return d ? d->width : 0; }
    int height() const { return d ? d->height : 0; }
    int color() const { return d ? d->color : 0; }
    int index() const { return d ? d->index : 0; }
    string name() const { return d ? d->name : 0; }
    string cameraID() const { return d ? d->cameraID : 0; }
    char *data() const { return d ? d->data : 0; }
    int refCount() const { return d ? d->refCount : 0; }

private:
    FrameInfoData *d = nullptr;
};


//struct FrameInfo
//{
//public:
//    short isValid = 3;                      //0: 有效；1: 无效数据a(补的空数据)；2：无效数据b(连续5次无效数据a后再补一帧数据，提示相机采图异常); 3: 初始值
//    unsigned long long blockid = 0;
//    short pixelDigit = 0;
//    short color = 0;
//    short width = 0;
//    short height = 0;
//    int index = 0;                           //表示：当前图像所在的位置索引(仅在本地相机中有意义)
//    char* data = nullptr;
//    std::string name = "";               //表示：xml中配置的"camera1", "camera2"
//    std::string cameraID = "";         //表示：相机的连接ID号
//};

Q_DECLARE_METATYPE(FrameInfo)

typedef void (*OnImageAcquired)(FrameInfo &info,void *ptr);     //定义：获取帧信息的回调函数

#endif // VISIONCAMERAPUB_H
