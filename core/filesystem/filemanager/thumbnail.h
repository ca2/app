#pragma once


#include "impact_base.h"


namespace filemanager
{


   class CLASS_DECL_CORE thumbnail :
      virtual public ::filemanager_show < ::user::impact >
   {
   public:

      

      string         m_strPath;
      //string_array        m_straPath;
      //string_array        m_straTitle;
      //i64_array    m_iaSize;
      i32        m_iCurFile;

      thumbnail();
      virtual ~thumbnail();

      void install_message_routing(::channel * pchannel) override;
      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace filemanager



