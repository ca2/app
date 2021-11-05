#include "framework.h"
#include "base/user/user/_user.h"
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



