#ifndef VISIONCAMERA_H
#define VISIONCAMERA_H

#include "visioncamerapub.h"
#include <QCoreApplication>
#include <QLibrary>
#include <mutex>
#include <QMutexLocker>
#include <Windows.h>
#include <QDebug>

#define CAMERA_LOCK lock_guard<mutex> lock(m_mutex);

/********************************************
 1. 关于释放对象
使用完VisionCamera后，在主程序的析构中要释放VisionCamera对象（delete camera）。
若是用相机管理CameraMgr处理的，则要从相机配置的节点cameraObj中取出VisionCamera指针，再释放。
注：释放相机对象，以避免有的相机不释放的话会阻碍主程序关闭。

2. 关于调用顺序
（1）连接相机：connectCamera();
（2）设置相机参数；如设置曝光，增益，触发模式，相机图像格式...
（3）有需要可以注册相机图像的回调函数：attachGetFrame();
（4）相机开流：startGrabbing();
（5）获取相机图像：
    方式1： getImage();  （若需要图像进队则调用：getImageQueue()）。
    方式2：若注册图像回调函数，则可以通过回调函数获取FrameInfo；
    方式3：关联相机图像的信号：signal_getFrame，以获取FrameInfo；

********************************************/


class VisionCamera : public QObject
{
    Q_OBJECT

signals:
//    void signal_getFrame(FrameInfo);
    void signal_disconnected(QString);     //传递的参数为该相机的ID
//    void signal_connected(QString);

public:

    VisionCamera() {}
    virtual ~VisionCamera(){}

    //****************************************************************************
    //虚函数
    //****************************************************************************

    /**
    * @brief       获取检测到的相机列表 (现在是序列号)
    * @return    QList<QString>
    * @note       在没有获取到VisionCamera相机指针是也可以获取到当前的检测到的GigE类型的相机IP
    */
    virtual QList<QString> findCameras(VInt &ret) = 0;

    /**
    * @brief       获取所加载相机的信息，包括供应商、型号、序列号、IP地址等信息
    * @return    CameraDeviceInfo结构体
    * @note       必须在加载相机之后 (load) 才能获取到有效信息
    */
    virtual CameraDeviceInfo getCameraInfo(VInt &ret) = 0;

    /**
    * @brief       设置相机userID  （camera1;camera2... 用于简单标识哪一个相机）
    * @return
    */
    virtual void setCameraUserID(string cameraUserID) = 0;

    /**
    * @brief       获取相机userID  （camera1;camera2）
    * @return
    */
    virtual string getCameraUserID() = 0;

    /**
    * @brief       获取相机的类别 (加载相机后才能够获取到)
    * @return
    */
    virtual CameraType getCameraLibType() = 0;

    /**
    * @brief       获取相机ID (连接相机后才能够获取到)
    * @return
    */
    virtual string getCameraID() = 0;

    /**
    * @brief       连接相机
    * @param    id(string类型), 目前大华: 相机IP; dalsa: 自定义ID; Basler: 序列号
    * @note       对于LH智能相机，相机ID是UINT类型，需要进行类型转换
    * @return    VInt
    */
    virtual VInt connectCamera(string cameraID) = 0;

    /**
    * @brief       断开连接相机
    * @return    VInt
    */
    virtual VInt disConnectCamera() = 0;

    /**
    * @brief       判断相机是否已经连接
    * @return		bool类型
    */
    virtual bool isConnected() = 0;

    /**
    * @brief       设置相机工作模式
    * @param    (1) 工作方式：CameraWork的枚举类型，默认WorkFreeAcquire；
    * @param    (2) 线路源：CameraLine类型，只有硬触发才可以选择（dalsa可选Line1和Line2，大华和basler只有Line1），默认值为Line1
    * @return    VInt错误码
    */
    virtual VInt setWorkPattern(CameraWork work = WorkFreeAcquire, CameraLine line = CameraLine::Line1) = 0;

    /**
    * @brief       获取相机工作模式
    * @param    VInt
    * @return    CameraWork的枚举类型
    */
    virtual CameraWork getWorkPattern(VInt &ret) = 0;

    /**
    * @brief       设置线触发模式（对应于其他的模式——帧触发）
    * @param    (1) triggerMode: true--On；false--Off；
    * @param    (2) source: 相机的触发源
    * @param    (3) activation: 边沿触发方式
    * @return    VInt错误码
    */
    virtual VInt setLineAcquisitionMode(bool triggerMode, CameraTriggerSource source, CameraTriggerActivation activation = RisingEdge){
        triggerMode = true;
        source = FrequencyConverter;
        activation = RisingEdge;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       设置上升沿触发还是下降沿触发
    * @param    activation: 默认值为上升沿触发
    * @return    VInt
    */
    virtual VInt setTriggerActivation(CameraTriggerActivation activation = RisingEdge) = 0;

    /**
    * @brief       设置触发延时（执行触发指令后经过延时时间之后相机才会触发拍照）
    * @param    (1): delayTime（us） 大华&basler：0-1000000； dalsa：0-2000000,dalsa要先设置mode为on
    * @return    VInt
    */
    virtual VInt setTriggerDelay(int delayTime) = 0;

    /**
    * @brief       获取当前触发延时时间
    * @param    VInt
    * @return    当前触发延时时间（us）
    */
    virtual int getTriggerDelay(VInt &ret) = 0;

    /**
    * @brief       设置IO输入（大华相机的初始电平设置目前有问题）
    * @param    (1) 线路：CameraLine枚举（注：大华和Basler相机只能选择Line1；dalsa相机可选Line1/Line2）根据具体相机而定
    * @param    (2) 输入线路的震荡周期: int，0-255(dalsa); 0-20000(us)(basler); 0-1000000(us)(大华)
    * @note       lineDebouncingPeriod: 该参数用于过滤掉外界给相机的触发信号中低于该时长的部分，用于过滤感染信号。
    * @note       需要分别对各个线路作设置
    * @return    VInt；
    */
    virtual VInt setIoInput(CameraLine line, UINT32 lineDebouncingPeriod = 10) = 0;

    /**
    * @brief       设置IO输出
    * @param    (1) 线路：CameraLine枚举（注：大华相机可选Line0/Line2, Basler相机可选Line2/Line3；dalsa相机可选Line3/Line4）
    * @param    (2) 输出线路源source：常用曝光完成时输出，或者用户输出（用线路输出打IO）；
    * @param    (3) 输出线路的滤波时间: int（dalsa：1-16777215，大华和Basler相机目前不能设置）单位us；
    * @note       需要分别对各个线路作设置
    * @return    VInt；
    */
    virtual VInt setIoOutput(CameraLine line, CameraOutputLineSource source, int linePulseDuration = 5000) = 0;

    /**
    * @brief       设置IO线路状态反转
    * @param    (1) 线路：line
    * @param    (2) lineInverter. false：即保持当前线路状态不变；true: 即反转当前线路状态. 默认为false；
    * @note       对IO线路的状态进行反转。即：true->false, false->true.
    * @note       需要分别对各个线路作设置
    * @return    VInt；
    */
    virtual VInt setIoLineInverter(CameraLine line, bool lineInverter = false) = 0;

    /**
    * @brief       设置IO自定义输出线路值（目前适用于大华相机）
    * @param     value：用户输出寄存器的值
    * @note        比如输出Line1和Line2。分别(1)false/false对应0 0，即0；(1)true/false对应1 0，即1；(1)false/true对应0 1，即2；(1)true/true对应1 1，即3；
    * @note        要设置上升沿，例如：先设置为1，延时t1作为电平持续时间，然后再设置为0.
    * @return    VInt；
    */
    virtual VInt setUserOutputValueAll(int value) {
        value = 0;
        return ErrSetUserOutputValueAll;
    }

    /**
    * @brief        设置相机增益(目前,大华相机和Basler相机不需要设置增益选择器，而dalsa相机需要设置)
    * @param		(1) 增益大小: UINT32, 范围:大华相机:[1,32], 也有[1,6];  basler相机: [100,1023]； dalsa相机如下：
    * @param     (2) 增益选择器: CameraGainSelector类型;
    * @note        SensorAnalog: gain范围[1,11]; SensorDigital: gain范围[100,3199]; DigitalAll: gain范围[0,384].
    * @note		注：同一品牌的不同相机，其参数范围也可能会不同
    * @return		VInt；
    */
    virtual VInt setGain(UINT32 gain, CameraGainSelector gainSelector = SensorAnalog) = 0;

    /**
    * @brief       获取相机增益信息(目前适用于dalsa相机，可获取当前增益选择器和其增益值)
    * @param	   错误码
    * @return    CameraGainInfo结构体
    */
    virtual CameraGainInfo getGainInfo(VInt &ret) = 0;

    /**
    * @brief        获取相机增益(目前适用于大华相机、basler相机, 而对于dalsa相机只能获取目前增益选择器的增益值)
    * @param		错误码
    * @return     double
    */
    virtual UINT32 getGain(VInt &ret) = 0;

    /**
    * @brief       设置相机自动增益（针对智能相机）
    * @param		isAuto: true-自动增益；false-非自动增益
    * @return     VInt
    */
    virtual VInt setGainAuto(bool isAuto = true){
        isAuto = false;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       获取相机是否自动增益（针对智能相机）
    * @param		ret: 函数执行结果的返回值
    * @return     bool （true-自动增益；false-非自动增益）
    */
    virtual bool getGainAuto(VInt &ret){
        ret = VInt::ErrValidAPI;
        return false;
    }

    /**
    * @brief       设置相机曝光模式 (dalsa相机)
    * @param		曝光等级: CameraExposureLevel类型，默认为FixedExposure
    * @return    VInt
    */
    virtual VInt setExposureLevel(CameraExposureLevel exposureLevel = FixedExposure){
        exposureLevel = FixedExposure;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       获取相机曝光模式 (dalsa相机)
    * @param    VInt
    * @return	   CameraExposureLevel枚举类型
    */
    virtual CameraExposureLevel getExposureLevel(VInt &ret){
        ret = VInt::ErrValidAPI;
        return CameraExposureLevel::FixedExposure;
    }

    /**
    * @brief       获取相机曝光时间（适用于固定曝光模式）
    * @param    VInt
    * @return    double
    */
    virtual double getExposureTime(VInt &ret) = 0;

    /**
    * @brief       获取相机的曝光时间（dalsa相机）
    * @param    VInt
    * @return    QList<double>
    */
    virtual QList<double> getExposureTimeList(VInt &ret){
        ret = VInt::ErrValidAPI;
        return {};
    }

    /**
    * @brief       设置相机曝光时间（适用于固定曝光模式，可实时修改）
    * @param		曝光时间: double (basler: [4,1000000]；大华: [16,1000000])
    * @return     VInt
    */
    virtual VInt setExposureTime(double exposureTime) = 0;

    /**
    * @brief       设置相机的曝光时间（适用于多段曝光模式，不能实时修改）
    * @param    曝光时间的QList: double；
    * @note       对于设置的曝光时间列表，能够生效几个还要取决于当前的曝光模式。
    * @note       若当前为二级曝光，设置两个曝光时间，则相机按这两个曝光时间依次显示；若设置一个曝光时间，则第二个默认为0；若设置三个，则只生效前两个。
    * @return	    VInt
    */
    virtual VInt setExposureTime(QList<double> exposureTimeList){
        exposureTimeList = {};
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       设置相机自动曝光（针对智能相机）
    * @param		isAuto: true-自动曝光；false-非自动曝光
    * @return     VInt
    */
    virtual VInt setExposureTimeAuto(bool isAuto = true){
        isAuto = false;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       获取相机是否自动曝光（针对智能相机）
    * @param		ret: 函数执行结果的返回值
    * @return     bool （true-自动曝光；false-非自动曝光）
    */
    virtual bool getExposureTimeAuto(VInt &ret){
        ret = VInt::ErrValidAPI;
        return false;
    }

    /**
    * @brief       设置相机采图帧率
    * @param    frameRate
    * @note       如果设置的帧率超过当前模式下的相机能达到的最大帧率值时，则实际设置成最大帧率值。
    * @return    VInt
    */
    virtual VInt setFrameRate(float frameRate) = 0;

    /**
    * @brief       获取当前相机采图帧率
    * @param    ret
    * @return    float
    */
    virtual float getFrameRate(VInt &ret) = 0;

    /**
    * @brief       设置相机图像宽度
    * @param    UINT32
    * @note       设置相机图像的宽度的时候需要停止拉流，否则设置不成功。
    * @note       对于basler相机：Inc=1； 对于dalsa和大华相机：Inc通常为8或16（即为8或16的倍数，否则设置失败）
    * @return    VInt
    */
    virtual VInt setImageWidth(UINT32 width) = 0;

    /**
    * @brief       获取相机图像宽度
    * @param    VInt
    * @return    当前的相机图像宽度
    */
    virtual UINT32 getImageWidth(VInt &ret) = 0;

    /**
    * @brief       获取相机图像宽度最大值
    * @param    VInt
    * @return    图像宽度最大值
    */
    virtual UINT32 getImageWidthMax(VInt &ret) = 0;

    /**
    * @brief       获取相机图像宽度最小值
    * @param    VInt
    * @return    图像宽度最小值
    */
    virtual UINT32 getImageWidthMin(VInt &ret) = 0;

    /**
    * @brief       设置相机图像高度
    * @param    UINT32
    * @note       设置相机图像的高度的时候需要停止拉流，否则设置不成功。
    * @note       Inc通常为12.
    * @return    VInt
    */
    virtual VInt setImageHeight(UINT32 height) = 0;

    /**
    * @brief       获取相机图像高度
    * @param    VInt
    * @return    当前的相机图像高度
    */
    virtual UINT32 getImageHeight(VInt &ret) = 0;

    /**
    * @brief       获取相机图像高度最大值
    * @param    VInt
    * @return    图像高度最大值
    */
    virtual UINT32 getImageHeightMax(VInt &ret) = 0;

    /**
    * @brief       获取相机图像高度最小值
    * @param    VInt
    * @return    图像高度最小值
    */
    virtual UINT32 getImageHeightMin(VInt &ret) = 0;

    /**
    * @brief       设置相机图像水平偏移值
    * @param    offsetX
    * @note       从传感器顶部到兴趣区的垂直偏移（以像素为单位）
    * @note       设置时候需要停止拉流，否则设置不成功。
    * @note       水平偏移量 + 图像宽度 <=  图像传感器宽度最大像素值。
    * @note       比如，相机最大像素宽度为1080，当前宽度为960，则水平偏移值设置范围为：0 - 120（间隔一般为8）
    * @return    VInt
    */
    virtual VInt setImageOffsetX(UINT32 offsetX) = 0;

    /**
    * @brief       获取相机图像水平偏移量
    * @param    VInt
    * @return    图像水平偏移量
    */
    virtual UINT32 getImageOffsetX(VInt &ret) = 0;

    /**
    * @brief       设置相机图像垂直偏移值
    * @param    offsetY
    * @note       从传感器顶部到兴趣区的垂直偏移（以像素为单位）
    * @note       设置时候需要停止拉流，否则设置不成功。
    * @note       垂直偏移量 + 图像高度 <=  图像传感器高度最大像素值
    * @note       比如，相机最大像素高度为960，当前高度为840，则垂直偏移值设置范围为：0 - 120（间隔一般为12）
    * @return    VInt
    */
    virtual VInt setImageOffsetY(UINT32 offsetY) = 0;

    /**
    * @brief       获取相机图像垂直偏移量
    * @param    VInt
    * @return    图像垂直偏移量
    */
    virtual UINT32 getImageOffsetY(VInt &ret) = 0;

    /**
    * @brief       设置相机白平衡 (目前只有大华相机有)
    * @param    mode
    * @return    VInt
    */
    virtual VInt setBalanceWhiteAuto(BalanceWhiteAuto mode = BalanceWhite_Continuous){
        mode = UnknownMode;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       获取相机白平衡模式 (目前只有大华相机有)
    * @param    VInt
    * @return    BalanceWhiteAuto
    */
    virtual BalanceWhiteAuto getBalanceWhiteAuto(VInt &ret){
        ret = ErrValidAPI;
        return UnknownMode;
    }

    /**
    * @brief       设置相机采集线速率 (目前针对basler的线阵相机)
    * @param    mode
    * @return    VInt
    */
    virtual VInt setAcquisitionLineRate(float rate){
        rate = 0;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       获取相机采集线速率 (目前针对basler的线阵相机)
    * @param    VInt
    * @return    相机采集线速率
    */
    virtual float getAcquisitionLineRate(VInt &ret){
        ret = ErrValidAPI;
        return 0;
    }

    /**
    * @brief       设置相机图像格式
    * @param    PixelFormat
    * @note       对于LH相机，只有mono，RGB24和RGB32三种。
    * @return    VInt
    */
    virtual VInt setPixelFormat(PixelFormat format) = 0;

    /**
    * @brief       获取相机图像格式
    * @param    VInt
    * @return    PixelFormat
    */
    virtual PixelFormat getPixelFormat(VInt &ret) = 0;

    /**
    * @brief       启动帧流
    * @return    VInt
    */
    virtual VInt startGrabbing() = 0;

    /**
    * @brief       停止帧流
    * @return    VInt
    */
    virtual VInt stopGrabbing() = 0;

    /**
    * @brief       是否在拉流
    * @return    bool
    */
    virtual bool isGrabbing() = 0;

    /**
    * @brief       打开某一张图片（仅用于本地相机）
    * @param    imageName: 在本地目录中的图片名称
    * @note       使用方法：先调用该函数，然后调用getImage()或者用信号槽/注册回调传出图像信息
    * @note       调用该命令然后获取的图像，会进队列(最多50张)
    */
    virtual VInt openImage(string imageName){
        imageName = "";
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       打开某一张图片（仅用于本地相机）
    * @param    imageName: 在本地目录中的序列索引
    * @note       使用方法：先调用该函数，然后调用getImage()或者用信号槽/注册回调传出图像信息
    * @note       调用该命令然后获取的图像，会进队列(最多50张)
    */
    virtual VInt openImage(UINT32 imageIndex){
        imageIndex = 0;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       获取下/上一张图片（仅用于本地相机）
    * @param    (1) isNext: true则显示下一张，false则显示上一张
    * @param    (2) isLooped: true则循环播放，false则只播放一个循环
    * @note       使用方法：先调用该函数，然后调用getImage()或者用信号槽/注册回调传出图像信息
    * @note       调用该命令然后获取的图像，会进队列(最多50张)
    */
    virtual VInt nextImage(bool isNext = true, bool isLooped = true){
        isNext = isLooped = true;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       设置播放参数（顺序还是逆序播放；是否循环播放）（仅用于本地相机）
    * @param    (1) isInOrder: true则顺序播放，false则逆序播放
    * @param    (2) isLooped: true则循环播放，false则只播放一个循环
    * @note       使用方法：先调用该函数，然后选择工作模式，开流，再调用getImage()或者用信号槽/注册回调传出图像信息
    */
    virtual VInt setPlayConfig(bool isInOrder = true, bool isLooped = true){
        isInOrder = isLooped = true;
        return VInt::ErrValidAPI;
    }

    /**
    * @brief       同步获得相机图像
    * @param    (1) VInt
    * @param    (2) outTime超时时间: 默认50ms (从个数为1的图像队列中取图，若没有图片时，等待outTime，期间一直尝试取图。若outTime之后还是没图，则返回ErrValidFrame)
    * @note       用于外界显示实时图像，当前版本调用完需要free（例：FrameInfo info; ... ; if(info.data != nullptr) free(info.data);）
    * @note       调用该函数，如果处于软(硬)触发模式，不能第一时间知道相机被触发
    * @return    FrameInfo类型
    */
    virtual FrameInfo getImage(VInt &ret, int outTime = 50) = 0;

    /**
    * @brief        相机图像队列的出队数据
    * @param     (1) VInt；
    * @param     (2) outTime超时时间: 默认500ms(即若队列中没有数据，则会等待500ms还是没数据则出一帧初始数据); 否则便按照设置的超时时间等待，超时VInt则为ErrCameraDequeue
    * @note        (1)给算法调用, 外界在获取图像信息时一定要先判断VInt. 当前版本调用完需要free（例：FrameInfo info; ... ; if(info.data != nullptr) free(info.data);）
    * @note        (2)队列长度设置为50，即一直保存最新的50张图像。
    * @note        (3)执行startGrabbing函数会清空队列信息。
    * @return     FrameInfo. 若出队成功，则返回一个有效的FrameInfo信息；若出队失败，则返回一个初始的FrameInfo, 其isValid = 3
    */
    virtual FrameInfo getImageQueue(VInt &ret, int outTime = 500) = 0;

    /**
    * @brief       设置线阵相机的拼接 (不对一般的工业相机进行实现)
    * @param    jointNum: 拼接帧数
    * @note       图像拼接是将相机的高度进行拼接，拼接后图像的高度为：jointNum * Height。（Height为相机AOI中的分辨率h）
    * @note       当前版本调用完需要free（例：FrameInfo info; ... ; if(info.data != nullptr) free(info.data);）
    * @return    VInt
    */
    virtual VInt setFrameJoint(bool enable, UINT32 jointNum = 1) = 0;

    /**
    * @brief       获取拼接图象 （不对一般的工业相机进行实现）
    * @param    (1) VInt
    * @param    (2) outTime超时时间: 默认50ms (从个数为1的图像队列中取图，若没有图片时，等待outTime，期间一直尝试取图。若outTime之后还是没图，则返回ErrValidFrame)
    * @note       (1) 图像拼接是将相机的高度进行拼接。线阵相机按行扫描，达到设定的图像高度相机SDK即可输出。
    * @note       (2) 而调用该函数则将相机SDK输出的图像再次拼接，以达到需要的图像高度。
    * @note       (3) 需要先调用setFrameJointNum()函数。
    * @return    FrameInfo类型
    */
    virtual FrameInfo getImageJoint(VInt &ret, int outTime = 50) = 0;

    /**
    * @brief       设置读取帧图像信息的回调函数
    * @note       异步获取相机图像
    * @param    函数指针（void类型）; void *ptr
    * @return    VInt
    */
    virtual VInt attachGetFrame(OnImageAcquired func, void *ptr) = 0;

    /**
    * @brief       注销读取帧图像信息的回调函数
    * @note       异步获取相机图像
    * @return    VInt
    */
    virtual VInt detachGetFrame() = 0;

    /**
    * @brief       执行一次软触发
    * @note       只有相机处于软触发模式下，再执行该函数才有效果，可查看返回值VInt。
    * @return    VInt
    */
    virtual VInt softExecute() = 0;

    /**
    * @brief       设置图像队列大小
    * @param    队列长度：UINT32. 默认为0
    * @note       长度为0：图像数据不进队列；其他长度size则进队列
    * @note       设置之前需要先停流
    * @return    VInt
    */
    virtual VInt setQueueSize(UINT32 queueSize = 0) = 0;

    /**
    * @brief        相机队列校验
    * @param     (1) 是否开启检验：bool；
    * @param     (2) 设置时间戳间隔(ms)，即外界触发时间间隔：UINT32类型，默认值50
    * @note        间隔时间在正负5ms以内认为是有效数据（isValid为0）。
    * @note        间隔时间过短，则认为误触发，该帧数据不进队列；间隔时间过长，则在将该帧数据替换为假数据（isValid为1)，然后进队列。
    * @note        注：若两帧的间隔时间为设置的间隔时间的n倍加减5ms之内，则最后一帧视为有效数据，并且中间会添加n-1个假数据(最多添100个假数据)。
    * @note              若两帧的间隔时间为设置的间隔时间的n倍加5ms之外，则会添加n个假数据(最多添100个假数据)。
    * @note        若连续超过5帧假数据，则会再向队列中添一帧假数据（isValid为2)（或者GetImageQueue函数的错误码不为0)，此时可认为相机采图出现异常.
    * @return     VInt
    */
    virtual VInt setQueueVertify(bool isVertify = true, UINT32 timeInterval = 50) = 0;

    /**
    * @brief       清空相机图像队列
    * @note       执行该操作使相机的图像队列清空，并释放内存
    * @return    VInt
    */
    virtual VInt clearImageQueue(UINT32 outTime) = 0;

    /**
    * @brief       获取相机图像队列的当前大小（估计值）
    * @note       该估计值只有当队列在被调用之前完全稳定时才会准确
    * @return    UINT32
    */
    virtual UINT32 getImageQueueSize() = 0;

    /**
    * @brief       将第一帧时间戳置位
    * @note       本函数将第一帧数据置位有效。（开流后，第一帧时间戳的差值由于没有时间戳作差或者时间相差很远，而导致该帧时间戳差值很大，该函数则可以解决该问题）
    * @return    UINT32
    */
    virtual void setonTimeStamp() = 0;

    /**
    * @brief       设置用户自定义的相机ID
    * @param    相机ID: string
    * @note       对于LH智能相机，相机ID是UINT类型，需要进行类型转换
    * @return    VInt
    */
    virtual VInt setUserDefinedID(string definedID) = 0;

    /**
    * @brief       获取用户自定义的相机ID
    * @param    VInt
    * @note       对于LH智能相机，相机ID是UINT类型，需要进行类型转换
    * @return    相机ID: string
    */
    virtual string getUserDefinedID(VInt &ret) = 0;

    /**
    * @brief       设置相机静态IP
    * @param    设置的静态IP: string
    * @note       目前dalsa相机只能将相机设置成静态IP模式，但是设置具体静态IP失败
    * @return    VInt
    */
    virtual VInt setCameraStaticIP(string staticIP) = 0;

    /**
    * @brief       获取相机静态IP
    * @param    VInt
    * @return    当前的相机静态IP值: string
    */
    virtual string getCameraStaticIP(VInt &ret) = 0;

    /**
    * @brief       设置相机动态IP
    * @return
    */
    virtual VInt setCameraDynamicIP() = 0;         //有问题



protected:

    /**
    * @brief       获取外界用户传入的待比较的相机名
    * @return
    */
    string getComparedCameraName() {
        return comparedCameraName;
    }

    /**
    * @brief       设置外界用户传入的待比较的相机名
    * @return
    */
    void setComparedCameraName(string id) {
        comparedCameraName = id;
    }

    /**
    * @brief       相机的初始化工作
    * @return    VInt错误码
    */
    virtual VInt initCamera() = 0;

    /**
    * @brief       定义一个函数指针，用来free掉队列中多余元素的内存
    */
    static void FreeCameraMemory(void */*var*/) {
//        FrameInfo *tmp = (FrameInfo*)var;
//        if(tmp->data != nullptr)
//        {
//            free(tmp->data);
//            tmp->data = nullptr;
//        }
    }

private:
    string mUserId;         //用户自定义的编码值, 留着备用
    mutex m_mutex;
    string comparedCameraName = "";    //当前相机从外界传入的ID

};

#endif // VISIONCAMERA_H
