﻿#pragma once


namespace userex
{


   class CLASS_DECL_CORE error_dialog :
      virtual public ::dialog
   {
   public:


      
      ::exception                m_exception;
      ::image_pointer                       m_pimage;


      error_dialog();

      void Initialize(const ::exception & e);


      virtual bool OnInitDialog();


   };


} // namespace userex



