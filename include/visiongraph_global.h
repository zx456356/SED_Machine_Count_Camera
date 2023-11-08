#ifndef VISIONGRAPH_GLOBAL_H
#define VISIONGRAPH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VISIONGRAPH_LIBRARY)
#  define VISIONGRAPHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define VISIONGRAPHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VISIONGRAPH_GLOBAL_H


//ERROR CODE
//使用VisionGraph出现报错，unindexedItems.isEmpty()，是由于在绘制数据的时候，出现设置数据的同步操作。加锁会存在一定的概率丢失数据的，使用队列即可避免
