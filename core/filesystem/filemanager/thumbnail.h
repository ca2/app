#pragma once


#include "impact_base.h"


namespace filemanager
{


   class CLASS_DECL_CORE thumbnail :
      virtual public ::filemanager_show < ::user::impact >
   {
   public:

      

      string         m_strPath;
      //string_array_base        m_straPath;
      //string_array_base        m_straTitle;
      //long_long_array_base    m_iaSize;
      int        m_iCurFile;

      thumbnail();
      virtual ~thumbnail();

      void install_message_routing(::channel * pchannel) override;
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace filemanager



