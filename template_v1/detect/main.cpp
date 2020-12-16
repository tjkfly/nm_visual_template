#include <iostream>
#include "thread_process.h"
using namespace std;
int main()
{
    VisualProc visual_proc;
    std::thread ImgProduce(&VisualProc::produce,&visual_proc);
    std::thread ImgConsume(&VisualProc::consumer,&visual_proc);
    std::thread ImgResive(&VisualProc::serialResive,&visual_proc);
    ImgProduce.join();
    ImgConsume.join();
    ImgResive.join();
    return 0;
}
