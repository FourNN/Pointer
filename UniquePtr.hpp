#pragma once
#include <cstdio>
#include <utility>
#include <vector>

template<typename T>
struct DefaultDeleter
{
    void operator()(T* p)const
    {
        delete p;
    }
};

template<typename T>
struct DefaultDeleter<T[]>
{
    void operator()(T* p)const
    {
        delete[] p;
    }
};


template <typename T,typename Deleter=DefaultDeleter<T>>
class UniquePtr
{
public:
    UniquePtr(){m_p=nullptr;}
    explicit UniquePtr(T*p){m_p=p;}
    UniquePtr(const UniquePtr& that)=delete;
    UniquePtr& operator=(const UniquePtr& that)=delete;
    UniquePtr(const UniquePtr&& that)noexcept{m_p=std::exchange(that.m_p,nullptr);}
    UniquePtr& operator=(UniquePtr&& that)noexcept
    {
        if (this!=&that)
        {
            if (m_p)
            {
                Deleter{}(m_p);
                m_p=std::exchange(that.m_p,nullptr);
            }
        }
        return *this;
    }
    T* get() const{return m_p;}
    T* operator->() const{return m_p;}
    ~UniquePtr()
    {
        if(m_p)Deleter{}(m_p);
    }
    
    
private:
    T *m_p;
};


template <typename T,typename Deleter>
class UniquePtr<T[],Deleter>:UniquePtr<T,Deleter>{};

template <typename T,typename ... Args>
UniquePtr<T> makeUnique(Args...args)
{
    return UniquePtr<T>(new T(args...));
}