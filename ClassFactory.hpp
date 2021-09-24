//2021-5-28 sethome

#pragma once

#define __CLASSFACTORY_H__
#ifdef __CLASSFACTORY_H__

#include "string"
#include "map"

#define REGISTER(className, factory)     \
  className* objectCreator_##className() \
  {                                      \
    return new className;                \
  }                                      \
  RegisterAction register_##className(#className, (createObjectPtr)objectCreator_##className, factory)

namespace Reflection
{
  typedef void *(*createObjectPtr)(void);

  //工厂类的定义
  class classFactory
  {
  private:
    std::map<std::string, createObjectPtr> m_classMap;

  public:
    classFactory(){};
    ~classFactory(){};

    //@brief:通过类名称字符串获取类的实例
    void *getClassByName(std::string className)
    {
      auto iter = m_classMap.find(className);
      if (iter == m_classMap.end())
        return NULL;
      else
        return iter->second();
    }

    //@brief:将给定的类名称字符串和对应的创建类对象的函数保存到map中
    void registClass(std::string name, createObjectPtr method)
    {
      m_classMap.insert(make_pair(name, method));
    }
  };

  //注册方法类，因为全局域不能直接调用函数，只能间接通过类来实现调用注册方法
  class RegisterAction
  {
  public:
    RegisterAction(std::string className, createObjectPtr createrFunction, classFactory &factory)
    {
      factory.registClass(className, createrFunction);
    }
    ~RegisterAction(){};
  };
}; //namespace Reflection

#endif
//end of file
