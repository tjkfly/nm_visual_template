#include "thread_process.h"

#define DEBUG_SHOW
#define KEYBOARD_TEST

/***************************************************************
*  @Brief:
*  @param:
*  @return:
*  @Author:     tjk
*  @Date:       2020-12-15
****************************************************************/
void VisualProc::consumer_video1()
{
    cv::VideoCapture cap;
    cap.open(0);
    while(true)
    {
        cv::Mat frame;
        cap >>frame;
        while(frame.empty())
        {
            cap >>frame;
        }
        //算法处理部分
        m_mutex1.lock();
        imageProcess(frame,m_resultImg);
        m_mutex1.unlock();
    }
}
/***************************************************************
*  @Brief:
*  @param:
*  @return:
*  @Author:     tjk
*  @Date:       2020-12-17
****************************************************************/
void VisualProc::consumer_video2()
{
    cv::VideoCapture cap; //没找到普通摄像头,就用视频测试了
    //获取摄像头这部分，可以用度申的SDK替换掉
    cap.open("F:\\rm_dataset\\NM_Template\\template_v1\\build-detect-Desktop_Qt_5_12_6_MinGW_64_bit-Debug\\lane4.mp4");
    double totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);
    double currentFrames = 0;
    while(true)
    {
        cv::Mat frame;

        cap >>frame;
        while(frame.empty())
        {
            cap >>frame;
        }
        /***********************************/
        //视频测试用的实际摄像头不需要
        if (currentFrames == totalFrames - 1)
        {
            currentFrames = 0;
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
        }
        currentFrames++;
        /***********************************/
        //算法处理部分
        m_mutex.lock();
        imageProcess(frame,m_resultImg1);
        m_mutex.unlock();
    }
}
void VisualProc::debugShow()
{
    while(true)
    {
        if(m_resultImg.empty() ||m_resultImg1.empty() )
            continue;
        cv::imshow("1",m_resultImg);
        cv::imshow("2",m_resultImg1);
        if(cv::waitKey(1) == 'q')
           break;
    }
}
/***************************************************************
*  @Brief:
*  @param:
*  @return:
*  @Author:     tjk
*  @Date:       2020-12-15
****************************************************************/
void VisualProc::serialResive()
{
    int temp_data = 1;
    while(true)
    {
#ifdef KEYBOARD_TEST
        std::cout<<"input mode"<<std::endl;
        std::cin >> temp_data;
        if(temp_data == 1)
        {
            m_enemyType = BLUE;
            m_fightType = AUTO_SHOOT;
        }
        if(temp_data == 2)
        {
            m_enemyType = RED;
            m_fightType = AUTO_SHOOT;
        }
#endif
        if(temp_data == 10000) //没啥用，主要是不想看到qt的警告。
            break;
    }
}
/***************************************************************
*  @Brief:
*  @param:
*  @return:
*  @Author:     tjk
*  @Date:       2020-12-15
****************************************************************/
void VisualProc::imageProcess(const cv::Mat &image,cv::Mat &resultMat)
{
    if(m_enemyType == BLUE)
    {
        cv::cvtColor(image,resultMat,cv::COLOR_BGR2HSV);
    }
    else
    {
        cv::cvtColor(image,resultMat,cv::COLOR_BGR2GRAY);
    }
}

