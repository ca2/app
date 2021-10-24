// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace progress
{


   class CLASS_DECL_APEX integer :
      virtual public int_scalar_listener
   {
   public:


      double                  m_dProgressStart;
      double                  m_dProgressEnd;
      int_scalar              m_scalar;
      ::progress::listener *  m_plistener;


      integer();
      ~integer() override;

      virtual void trace_progress();

      virtual void trace_progress(i64 iStep);

      virtual void progress_step();

      virtual void on_set_scalar(int_scalar_source * psource, e_scalar escalar, i64 iValue, int iFlags) override;

      int_scalar & get_scalar() { return m_scalar; }

   };


} // namespace progress



