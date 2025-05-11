/*
 Copyright (ca) 2001
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 25.12.2001 14:47:20
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 wrapper class for _set_se_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/

#pragma once

#ifdef WINDOWS
#include <eh.h>
#endif


#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)
#define EXCEPTION_TRANSLATOR_USE_SIGNAL
#endif


////#include "acme/prototype/prototype/matter.h"


//extern CLASS_DECL_ACME bool g_bExiting;

//
//namespace exception
//{


   class CLASS_DECL_ACME exception_translator :
      virtual public matter
   {
   protected:

      bool    m_bSet;

   public:

//#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL
//
//      void *      m_psig;
//
//#endif

      exception_translator();
      ~exception_translator() override;

//#ifdef WINDOWS
//      virtual void filter(unsigned int uiCode, _EXCEPTION_POINTERS * int_point);
//      //static void __cdecl filter2(unsigned int uiCode, _EXCEPTION_POINTERS * int_point);
//      //void filter( _EXCEPTION_POINTERS * int_point);
//#endif



      virtual bool attach();
      virtual bool detach();


#ifdef WINDOWS


      virtual string _get_standard_exception_name(unsigned int uiCode);
      virtual string _get_standard_exception_description(unsigned int uiCode);


#endif

   };

//
//} // namespace exception
//
//
