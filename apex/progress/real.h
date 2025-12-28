#pragma once



#include "acme/prototype/mathematics/scalar.h"
////#include "acme/prototype/prototype/object.h"


namespace progress
{


   class CLASS_DECL_APEX real :
      virtual public ::number::scalar_source,
      virtual public object
   {
   public:


      string                  m_strStatus;
      ::collection::index                 m_iStep;
      ::collection::count                 m_iStepCount;
      string                  m_strTitle;


      real();
      ~real() override;
       

      bool on_set_scalar(enum_scalar escalar, ::number::number number, int iFlags) override;
      ::number::number get_scalar_minimum(enum_scalar escalar)override;
      ::number::number get_scalar(enum_scalar escalar) override;
      ::number::number get_scalar_maximum(enum_scalar escalar)override;

      virtual void format_status(const_char_pointer pszFormat);

      virtual void redraw();
      virtual bool progress_real_step();

      virtual void close_progress();


   };


} // namespace progress



