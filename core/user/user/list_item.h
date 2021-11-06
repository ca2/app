#pragma once


namespace user
{



   class CLASS_DECL_CORE list_item :
      virtual public mesh_item
   {
   public:

      list * m_plist;
      list_column * m_pcolumn;


      list_item(list * plist);

   };

   class CLASS_DECL_CORE draw_list_item :
      virtual public draw_mesh_item,
      virtual public list_item
   {
   public:



      //list_column *        m_pcolumnWidth;

      //list_column *        m_pcolumnSubItemRect;


      draw_list_item(list * plist);


      __pointer(::image_list) get_image_list();
      bool draw_image();
      bool draw_group_image();
      void update_item_color();
      void set_text_color();
      void draw_text();

   };


} // namespace user



