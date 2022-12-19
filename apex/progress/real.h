#pragma once


#include "acme/primitive/string/string.h"
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
      ::index                 m_iStep;
      ::count                 m_iStepCount;
      string                  m_strTitle;


      real();
      ~real() override;
       

      bool on_set_scalar(enum_scalar escalar, ::number number, int iFlags) override;
      ::number get_scalar_minimum(enum_scalar escalar)override;
      ::number get_scalar(enum_scalar escalar) override;
      ::number get_scalar_maximum(enum_scalar escalar)override;

      virtual void format_status(const scoped_string & strFormat);

      virtual void redraw();
      bool step() override;

      virtual void close_progress();


   };


} // namespace progress



