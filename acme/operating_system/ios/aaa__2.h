#pragma once


#include "parallelization.h"


#include "base_internal.h"

::u32 m_sleep(::u32 seconds);




////#define CLASS_DECL_ACME



/*#ifdef cplusplus

template < class T >
class thread_pointer
{
public:
    
    
    const_char_pointer pszName;
    
    thread_pointer(const ::scoped_string & scopedstrName)
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
    
    const_char_pointer pszName;
    
    thread_var(const ::scoped_string & scopedstrName)
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


