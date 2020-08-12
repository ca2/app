#pragma once


//#include "ios_ns_exception.h"


//#include "ios_multithreading.h"


/*#ifdef cplusplus

template < class T >
class thread_pointer
{
public:
    
    
    const char * name;
    
    thread_pointer(const char * pszName)
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
    
    thread_var(const char * pszName)
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

#ifndef __M

#include "aura/graphics/graphics_window_graphics.h"

#endif

#ifdef __OBJC__

#import "ios_m.h"

#endif

// #ifdef __cplusplus

// #ifdef __OBJC__

// typedef UIWindow * ui_window_ptr;
// typedef void * base_system_ptr;

// #else

// typedef void * ui_window_ptr;
// typedef ::base::system * base_system_ptr;

// #endif

// struct plane_system
// {
   
//    base_system_ptr    m_psystem;
   
//    plane_system(const char * pszId);
   
//    ui_window_ptr init_part_2ex(CGRect rect);
   
//    void begin();
   
// };

// #endif


