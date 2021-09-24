//2021-5-18 sethome

#define __LED_ANIMA_UTILITY_H__
#ifdef  __LED_ANIMA_UTILITY_H__

//比较大小的宏定义（色域转换函数用）
#define THREE_MAX(a, b, c) (a > b ? (a > c ? a : c) : (b > c ? b : c)) //输出三个数中最大数
#define THREE_MIN(a, b, c) (a > b ? (b > c ? c : b) : (a > c ? c : a)) //输出三个数中最小数

namespace LED_anima
{
  namespace utility
  {
    //释放内存
    template <typename MemoryPoint>
    bool freeMemory(MemoryPoint p)
    {
      if (p != NULL)
      {
        delete p;
        p = NULL;
        return true;
      }
      return false;
    }
  }
}
#endif

//end of file
