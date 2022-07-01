#pragma once


namespace user
{


   class CLASS_DECL_CORE list_subitem :
      virtual public mesh_subitem
   {
   public:


      list_subitem();


      void initialize_list_subitem(list_item * plistitem);


   };


   class CLASS_DECL_CORE draw_list_subitem :
      virtual public draw_mesh_subitem,
      virtual public list_subitem
   {
   public:


      draw_list_subitem();


      void initialize_draw_list_subitem(list_item * plistitem);


      ::image_list * get_image_list();
      void draw_image(::draw2d::graphics_pointer & pgraphics);
      void draw_group_image(::draw2d::graphics_pointer & pgraphics);
      void update_color(::draw2d::graphics_pointer & pgraphics);
      void set_text_color(::draw2d::graphics_pointer & pgraphics);
      void draw_text(::draw2d::graphics_pointer & pgraphics);

      ::color::color calculate_text_color(::draw2d::graphics_pointer & pgraphics, ::user::enum_state estate);

   };




   class CLASS_DECL_CORE list_item :
      virtual public mesh_item
   {
   public:


      list_item();

      void initialize_list_item(list * plist);


   };


   class CLASS_DECL_CORE draw_list_item :
      virtual public draw_mesh_item,
      virtual public list_item
   {
   public:


      index_map < __pointer(draw_list_subitem) >      m_mapSubItem;


      draw_list_item();


      void initialize_draw_list_item(list * plist);


      void update_item_color(::draw2d::graphics_pointer & pgraphics);


      

   };


   class CLASS_DECL_CORE list_group :
      virtual public mesh_group
   {
   public:


      list_group();

      void initialize_list_group(list * plist);


   };


   class CLASS_DECL_CORE draw_list_group :
      virtual public draw_mesh_group,
      virtual public list_group
   {
   public:


      //index_map < __pointer(draw_list_subitem) >      m_mapSubItem;


      draw_list_group();


      void initialize_draw_list_group(list * plist);


      //__pointer(::image_list) get_image_list();
      //void draw_image();
      void draw_group_image(::draw2d::graphics_pointer & pgraphics);
      void update_item_color(::draw2d::graphics_pointer & pgraphics);
      //void set_text_color();
      //void draw_text();




   };




} // namespace user



