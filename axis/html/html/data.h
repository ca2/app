#pragma once


#include "axis/user/form/data.h"


class CLASS_DECL_AXIS html_data :
   virtual public ::form_data
{
public:


   ::pointer<::html_data>             m_pimplHtml;
   ::pointer<::html_document>         m_pdocument;
   ::html::core_data *                 m_pcoredata;
   ::pointer<::html::core_data>     m_pcompositeCoreData;


   html_data();
   ~html_data() override;


   virtual void initialize_html_data(::html_data * phtmldata);


   long long increment_reference_count() override;
   long long decrement_reference_count() override;


   virtual bool open_document(const ::payload & payloadFile);
   virtual bool open_html(const ::scoped_string & scopedstr);


   virtual bool open_link(const ::scoped_string & scopedstrPath);


   virtual ::user::form * get_form();
   virtual ::pointer<::user::interaction>get_frame();


   //virtual bool is_locked();

   void load(const ::scoped_string & scopedstr);
   void implement(::draw2d::graphics_pointer & pgraphics);
   void on_layout(::draw2d::graphics_pointer & pgraphics);
   void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   void implement(::html_form * pform);
   void layout(::html_form * pform);
   void implement_and_layout(::html_form * pform);

   DECLARE_MESSAGE_HANDLER(on_message_key_down);

   ::image::image_pointer get_image(const ::scoped_string & scopedstrUrl);
   //void load_image_asynch(::html::image::image *pimage);
   //bool load_image(::html::image::image *pimage);

   //void on_image_loaded(::html::image::image *pimage);


   ::html::element* get_element_by_name(atom atom);
   ::html::element* get_element_by_id(atom atom);

   void delete_contents();
   void destroy() override;
   void delete_implementation();

   virtual bool contains(::pointer<::user::interaction>pinteraction);

   virtual bool on_create_interaction(::pointer<::user::interaction>pinteraction);


   ::html::font * get_font(::html::element * pelemental);




protected:


   int create_font(::html::element* pelemental);




};


