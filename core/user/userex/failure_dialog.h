#pragma once


#include "dialog.h"
////#include "acme/exception/exception.h"


namespace userex
{


   class CLASS_DECL_CORE failure_dialog :
      virtual public ::dialog
   {
   public:


      
      ::exception                            m_exception;
      ::image_pointer                        m_pimage;


      failure_dialog();

      void Initialize(const ::exception & e);


      virtual bool OnInitDialog();


   };


} // namespace userex



