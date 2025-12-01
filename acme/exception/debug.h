// Created by camilo on 2022-10-27 21:50 <3ThomasBorregaardSorensen!!
#pragma once


// returns true if it should continue...
CLASS_DECL_ACME bool __assert_failed_line(const_char_pointer pszFileName, int iLineNumber);

CLASS_DECL_ACME int is_debugger_attached(void);

CLASS_DECL_ACME void debug_print(const_char_pointer pszFormat, ...);

CLASS_DECL_ACME void throw_todo();

CLASS_DECL_ACME int throw_assert_exception(const_char_pointer pszFileName, int iLineNumber);

//CLASS_DECL_ACME void throw_what_exclamation_exclamation(const ::scoped_string & scopedstr);

#define __pass_array(A) A, sizeof(A)

#ifndef __cplusplus


#define ASSERT assert


#else


#ifdef _DEBUG




#define ASSERT(f)                                              \
{                                                              \
                                                               \
   if(!(f))                                                    \
   {                                                           \
                                                               \
     if(is_debugger_attached())                                \
     {                                                         \
                                                               \
        if(!__assert_failed_line(__FILE__, __LINE__))          \
        {                                                      \
                                                               \
            debug_break();                                     \
                                                               \
        }                                                      \
                                                               \
     }                                                         \
     else                                                      \
     {                                                         \
                                                               \
         throw_assert_exception(__FILE__, __LINE__);           \
                                                               \
     }                                                         \
                                                               \
   }                                                           \
                                                               \
}


template < prototype_container CONTAINER >
inline void __assert_container_ok(const CONTAINER * pcontainer, const_char_pointer pszFileName, int nLine);


CLASS_DECL_ACME void __assert_particle_ok(const ::particle * pparticle, const_char_pointer pszFileName, int nLine);


template <prototype_container CONTAINER>
inline void __assert_ok(const CONTAINER * p, const char * pszFile, int iLine)
{

   __assert_container_ok(p, pszFile, iLine);

}


inline void __assert_ok(const ::particle * p, const char * pszFile, int iLine)
{

   __assert_particle_ok(p, pszFile, iLine);

}




#define _ASSUME(cond)      do { bool _gen__condVal=!!(cond); ASSERT(_gen__condVal); __analysis_assume(_gen__condVal); } while(0)
#define ASSERT_OK(p)  ::__assert_ok(p, __FILE__, __LINE__)


#else


#define ASSERT(f)
#define _ASSUME(cond)
#if defined(__ANDROID__)
#define ASSERT_OK(cond)
#elif defined(__APPLE__)
#define ASSERT_OK(cond)
#elif defined(LINUX) || defined(__BSD__)
#define ASSERT_OK(cond)
#else
#define ASSERT_OK(cond) __noop;
#endif
#endif


#endif







