#pragma once


namespace user
{


   class CLASS_DECL_BASE print_task :
      virtual public ::task
   {
   public:

      #pragma once


      i32      m_iPageStart;
      i32      m_iPageCount;
      i32      m_iPrintingPage;

      __pointer(::user::interaction)   m_pinteraction;


      __pointer(::draw2d::printer)     m_pprinter;


      print_task();
      virtual ~print_task();

      virtual ::estatus     initialize(::object * pobjectContext) override;

      virtual ::estatus     run() override;


   };


} // namespace user



