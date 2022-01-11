#pragma once


namespace progress
{


   class CLASS_DECL_APEX real :
      virtual public double_scalar_source,
      virtual public object
   {
   public:


      string                  m_strStatus;
      ::index                 m_iStep;
      ::count                 m_iStepCount;
      string                  m_strTitle;


      real();
      ~real() override;
       

      void on_set_scalar(e_scalar escalar, double d, int iFlags) override;
      void get_scalar_minimum(e_scalar escalar, double & d) override;
      void get_scalar(e_scalar escalar, double & d) override;
      void get_scalar_maximum(e_scalar escalar, double & d) override;

      virtual void format_status(const char * pszFormat);

      virtual void redraw();
      void step() override;

      virtual void close_progress();


   };


} // namespace progress



