/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       main.cpp
 * @brief      多摄像头使用模板
 *
 * @author     xxx<xxx@xxx.com>
 * @date       2020/12/18
 * @history
 *****************************************************************************/
#include <iostream>
#include "thread_process.h"
using namespace std;
int main()
{
    VisualProc visual_proc;
    std::thread ImgConsume(&VisualProc::consumer_video1,&visual_proc);
    std::thread ImgConsume1(&VisualProc::consumer_video2,&visual_proc);
    std::thread ImgShow(&VisualProc::debugShow,&visual_proc);
    std::thread ImgResive(&VisualProc::serialResive,&visual_proc);
    ImgConsume.join();
    ImgConsume1.join();
    ImgShow.join();
    ImgResive.join();
    return 0;
}
