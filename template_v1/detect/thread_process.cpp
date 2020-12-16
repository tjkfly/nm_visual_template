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
    cap.open(0);
    cv::Mat src;
    while(true)
    {
        if(m_mat_num < 5)
        {
            cap >> src;
            std::unique_lock<std::mutex> locker(m_mutex);
            m_MatQueue.push_front(src);
            m_threadCond.notify_one(); // 通知显示
            //std::cout<<"pic"<<std::endl;
            ++m_mat_num;
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
        cv::imshow("1",frame);
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

