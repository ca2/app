#pragma once


namespace userex
{


   class CLASS_DECL_CORE error_dialog :
      virtual public ::dialog
   {
   public:


      
      ::exception_pointer                m_pexception;
      ::image_pointer                       m_pimage;


      error_dialog();

      void Initialize(::exception_pointer e);


      virtual bool OnInitDialog();


   };


} // namespace userex



