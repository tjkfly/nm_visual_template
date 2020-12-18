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
        //�㷨������
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
    cv::VideoCapture cap; //û�ҵ���ͨ����ͷ,������Ƶ������
    //��ȡ����ͷ�ⲿ�֣������ö����SDK�滻��
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
        //��Ƶ�����õ�ʵ������ͷ����Ҫ
        if (currentFrames == totalFrames - 1)
        {
            currentFrames = 0;
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
        }
        currentFrames++;
        /***********************************/
        //�㷨������
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
        if(temp_data == 10000) //ûɶ�ã���Ҫ�ǲ��뿴��qt�ľ��档
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

