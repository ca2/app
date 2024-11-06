#pragma once


#include "acme/parallelization/task.h"


namespace user
{


   class CLASS_DECL_BASE print_task :
      virtual public ::task
   {
   public:

      #pragma once


      int      m_iPageStart;
      int      m_iPageCount;
      int      m_iPrintingPage;

      ::pointer<::user::interaction>  m_pinteraction;


      ::pointer<::draw2d::printer>    m_pprinter;


      print_task();
      virtual ~print_task();

      virtual void     initialize(::particle * pparticle) override;

      virtual void     run() override;


   };


} // namespace user



