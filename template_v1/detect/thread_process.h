#ifndef THREAD_PROCESS_H
#define THREAD_PROCESS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <deque>
#include <condition_variable>

enum EnemyType
{
    NO_GET = 0,
    BLUE,
    RED
};

enum FightType
{
    AUTO_SHOOT = 0,
    BIG_BUFFER_SHOOT,
    SMALL_BUFFER_SHOOT
};

class VisualProc
{
public:
    VisualProc()
    {
        m_mat_num = 0;
        m_enemyType = BLUE;
        std::cout<<"我们上!"<<std::endl;
    }
    void produce();
    void consumer();
    void consumer_1();
    void serialResive();
private:
    void imageProcess(const cv::Mat &image,cv::Mat &resultMat);
public:
    std::deque<cv::Mat> m_MatQueue;
    std::deque<cv::Mat> m_MatQueue1;
    int m_mat_num;
    int m_mat_num1;
    //线程相关
    std::mutex m_mutex;
    std::mutex m_mutex1;
    std::condition_variable m_threadCond;
    std::condition_variable m_threadCond1;
    //结果图
    cv::Mat m_resultImg;
private:
    EnemyType m_enemyType;
    FightType m_fightType;
};
#endif // THREAD_PROCESS_H
