#pragma once


class CLASS_DECL_CORE html_data :
   virtual public ::form_data
{
public:


   __pointer(::html_data)              m_pimplHtml;
   ::html::core_data *                 m_pcoredata;
   ::html_document *                   m_pdocument;



   html_data();
   virtual ~html_data();


   virtual ::e_status initialize_html_data(::html_data * phtmldata);


   virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);


   virtual bool open_document(const payload & varFile);
   virtual ::e_status     open_html(const ::string & str);


   virtual bool open_link(const char * pszPath);


   virtual ::user::form * get_form();
   virtual __pointer(::user::interaction) get_frame();


   //virtual bool is_locked();

   void load(const char *);
   void implement(::draw2d::graphics_pointer & pgraphics);
   void on_layout(::draw2d::graphics_pointer & pgraphics);
   void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   void implement(::html_form * pform);
   void layout(::html_form * pform);
   void implement_and_layout(::html_form * pform);

   DECL_GEN_SIGNAL(_001OnKeyDown);

   image_pointer get_image(const char * pszUrl);
   //void load_image_asynch(::html::image::image * pimage);
   //bool load_image(::html::image::image * pimage);

   //void on_image_loaded(::html::image::image * pimage);


   ::html::element* get_element_by_name(id id);
   ::html::element* get_element_by_id(id id);

   void delete_contents();
   void destroy();
   void delete_implementation();

   virtual bool contains(__pointer(::user::interaction) pinteraction);

   virtual bool on_create_interaction(__pointer(::user::interaction) pinteraction);


   ::html::font * get_font(::html::element * pelemental);




protected:


   i32 create_font(::html::element* pelemental);




};


