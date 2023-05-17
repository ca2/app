#pragma once


#include "dialog.h"
////#include "acme/exception/exception.h"


namespace userex
{


   class CLASS_DECL_CORE failure_dialog :
      virtual public ::dialog
   {
   public:


      
      ::pointer < ::exception >              m_pexception;
      ::image_pointer                        m_pimage;


      failure_dialog();
      ~failure_dialog() override;


      void initialize(::exception * pexception);


      virtual bool OnInitDialog();


   };


} // namespace userex



