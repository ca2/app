#pragma once



#include "acme/primitive/mathematics/scalar.h"
////#include "acme/primitive/primitive/object.h"


namespace progress
{


   class CLASS_DECL_APEX real :
      virtual public scalar_source,
      virtual public object
   {
   public:


      string                  m_strStatus;
      ::raw::index                 m_iStep;
      ::raw::count                 m_iStepCount;
      string                  m_strTitle;


      real();
      ~real() override;
       

      bool on_set_scalar(enum_scalar escalar, ::number number, int iFlags) override;
      ::number get_scalar_minimum(enum_scalar escalar)override;
      ::number get_scalar(enum_scalar escalar) override;
      ::number get_scalar_maximum(enum_scalar escalar)override;

      virtual void format_status(const char * pszFormat);

      virtual void redraw();
      virtual bool progress_real_step();

      virtual void close_progress();


   };


} // namespace progress



