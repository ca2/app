// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/mathematics/scalar.h"


namespace progress
{


   class CLASS_DECL_APEX integer :
      virtual public scalar_source::listener
   {
   public:


      double                     m_dProgressStart;
      double                     m_dProgressEnd;
      scalar                     m_scalar;
      ::progress::listener *     m_plistener;


      integer();
      ~integer() override;

      virtual void trace_progress();

      virtual void trace_progress(long long iStep);

      virtual void progress_step();

      virtual bool on_set_scalar(scalar_source * psource, enum_scalar escalar, number number, int iFlags) override;

      //scalar & get_scalar() { return m_scalar; }


   };


} // namespace progress



