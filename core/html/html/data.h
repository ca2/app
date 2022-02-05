#pragma once


class CLASS_DECL_CORE html_data :
   virtual public ::form_data
{
public:


   __pointer(::html_data)              m_pimplHtml;
   __pointer(::html_document)          m_pdocument;
   ::html::core_data *                 m_pcoredata;
   __composite(::html::core_data)      m_pcompositeCoreData;


   html_data();
   ~html_data() override;


   virtual void initialize_html_data(::html_data * phtmldata);


   i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


   virtual bool open_document(const ::payload & payloadFile);
   virtual bool open_html(const ::string & str);


   virtual bool open_link(const ::string & pszPath);


   virtual ::user::form * get_form();
   virtual __pointer(::user::interaction) get_frame();


   //virtual bool is_locked();

   void load(const ::string &);
   void implement(::draw2d::graphics_pointer & pgraphics);
   void on_layout(::draw2d::graphics_pointer & pgraphics);
   void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   void implement(::html_form * pform);
   void layout(::html_form * pform);
   void implement_and_layout(::html_form * pform);

   DECLARE_MESSAGE_HANDLER(on_message_key_down);

   image_pointer get_image(const ::string & pszUrl);
   //void load_image_asynch(::html::image::image * pimage);
   //bool load_image(::html::image::image * pimage);

   //void on_image_loaded(::html::image::image * pimage);


   ::html::element* get_element_by_name(atom atom);
   ::html::element* get_element_by_id(atom atom);

   void delete_contents();
   void destroy() override;
   void delete_implementation();

   virtual bool contains(__pointer(::user::interaction) pinteraction);

   virtual bool on_create_interaction(__pointer(::user::interaction) pinteraction);


   ::html::font * get_font(::html::element * pelemental);




protected:


   i32 create_font(::html::element* pelemental);




};


