// Recreated by camilo on 2023-06-28 14:41 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "control.h"
#include "style.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/platform/context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/context_image.h"
#include "aura/windowing/windowing.h"
#include "aura/user/appearance/appearance.h"
#include "aura/message/user.h"


namespace user
{


   control::control()
   {

      user_control_construct();

   }

   control::~control()
   {

   }


   void control::user_control_construct()
   {

      m_bClickDefaultMouseHandling = true;

      m_econtroltype = e_control_type_none;

      m_bMouseHoverOnCapture = true;

      m_bClickDefaultMouseHandling = true;

   }


   void control::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


} // namespace user



