#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_component.h"
#endif
#include "split_pane.h"


namespace user
{


   split_pane::split_pane()
   {

      m_pplaceholder = nullptr;

      m_rectangle.Null();

      m_rectangleClient.Null();

      m_sizeFixed = ::size_i32(0, 0);

   }


} // namespace user



