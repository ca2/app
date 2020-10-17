#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE preview :
      virtual public ::user::impact,
      virtual public impact
   {
   public:

      

      string         m_strPath;
      //string_array        m_straPath;
      //string_array        m_straTitle;
      //i64_array    m_iaSize;
      i32        m_iCurFile;

      preview();
      virtual ~preview();

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void on_apply(::action * paction) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   };


} // namespace filemanager



