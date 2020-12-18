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
void VisualProc::produce()
{
    cv::VideoCapture cap;
    //cv::VideoCapture cap1;
    cap.open(0);
    //cap1.open("F:\\rm_dataset\\NM_Template\\template_v1\\build-detect-Desktop_Qt_5_12_6_MinGW_64_bit-Debug\\lane4.mp4");
    cv::Mat src;
    cv::Mat src1;
    while(true)
    {
        if(m_mat_num < 5)
        {
            cap >> src;
            //cap1 >> src1;
            std::unique_lock<std::mutex> locker(m_mutex);
            m_MatQueue.push_front(src);
            //m_MatQueue1.push_front(src1);
            m_threadCond.notify_one(); // 通知显示 notify_all() /notify_one()
            //std::cout<<"pic"<<std::endl;
            ++m_mat_num;
           // ++m_mat_num1;
        }
        if(m_mat_num == 10000)  //没啥用，主要是不想看到qt的警告。
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
void VisualProc::consumer()
{
    while(true)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        while(m_MatQueue.empty())
            m_threadCond.wait(locker);
        cv::Mat frame = m_MatQueue.back();
        m_MatQueue.pop_back();
        //算法处理部分
        imageProcess(frame,m_resultImg);
#ifdef DEBUG_SHOW
        //cv::imshow("1",frame);
        cv::imshow("2",m_resultImg);
        if(cv::waitKey(1) == 'q')
            break;
#endif
        --m_mat_num;
    }
}
/***************************************************************
*  @Brief:
*  @param:
*  @return:
*  @Author:     tjk
*  @Date:       2020-12-17
****************************************************************/
void VisualProc::consumer_1()
{
    cv::VideoCapture cap;
    cap.open("F:\\rm_dataset\\NM_Template\\template_v1\\build-detect-Desktop_Qt_5_12_6_MinGW_64_bit-Debug\\lane4.mp4");
    while(true)
    {
        cv::Mat frame;
        while(frame.empty())
            cap >>frame;
        //算法处理部分
        //imageProcess(frame,m_resultImg);
#ifdef DEBUG_SHOW
        cv::imshow("3",frame);
        //cv::imshow("4",m_resultImg);
        if(cv::waitKey(1) == 'q')
            break;
#endif
        //--m_mat_num1;
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

