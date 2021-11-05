#pragma once


#include "parallelization.h"


#include "base_internal.h"

unsigned int m_sleep(unsigned int seconds);




////#define CLASS_DECL_AURA



/*#ifdef cplusplus

template < class T >
class thread_pointer
{
public:
    
    
    const char * name;
    
    thread_pointer(const ::string & pszName)
    {
        name = pszName;
    }
    
    
    operator T *()
    {
        
        return (T *) get_thread_ptr(name);
        
    }
    
    T * operator ->()
    {
        return operator T *();
    }
    
    thread_pointer & operator = (T * pt)
    {
        
        set_thread_ptr(name, point);
        
        return *this;
        
    }
    
};


template < class T >
class thread_var
{
public:
    
    const char * name;
    
    thread_var(const ::string & pszName)
    {
        name = pszName;
    }
    
    
    operator T ()
    {
        
        return (T) get_thread_int(name);
        
    }
    
    thread_var & operator = (T t)
    {
        
        set_thread_int(name, t);
        
        return *this;
        
    }
    
    
};


#endif



*/


#ifdef __OBJC__

#import "_m.h"

#else

struct UIWindow;

#endif





#include "windowing.h"


