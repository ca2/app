#pragma once


#include "aura/user/user/interaction_array.h"
#include "axis/html/graphics/style_sheet_array.h"


//
//#include "core/html/graphics/_.h"
//#include "core/html/html/_.h"
//
//
//
//class html_document;
//
//
//class html_data;
//
//
//class html_impact;
//
//
//class html_form;
//
//
//
//
//#include "core/html/matter/elemental_elemental.h"
//
//
//
//
//

//
//
//CLASS_DECL_CORE void trim001(string& str);
//
//
//#include "axis/html/html_lite/_.h"
//
//
//
//
//#include "core/html/graphics/graphics.h"
//
//
//#include "core/html/user/form.h"
//
//
//

#include "data.h"


namespace html
{


//   namespace impl
//   {
//
//      class table;
//
//   } // namespace impl


   class CLASS_DECL_AXIS core_data :
      virtual public ::html_data
   {
   public:


      class CLASS_DECL_AXIS image :
         virtual public ::object
      {
      public:






         ::collection::index                   m_iIndex;
         string                  m_strPath;
         ::image::image_pointer                 m_pimage;


         image();


         virtual bool load_image();

      };


      class CLASS_DECL_AXIS layout_state1
      {
      public:

         float_array       m_cxa;
         float_array       m_cxMax;
         float_array       m_cya;
         bool                          m_bHasChar;
         float                         m_cy;


         void reset();


      };


      class CLASS_DECL_AXIS layout_state2
      {
      public:
         int      m_iBody;
         float    m_y;
         float    m_cy;
         float    m_x;
         float    m_cx;
         //         bool     m_bLastBlockX;
         //         bool     m_bLastCellX;
         bool     m_bLastBlock;
         bool     m_bLastCell;
         //bool     m_bHasChar;


         //ref_array < impl::table > m_tableptraStack;
         //ref_array < impl::table_row > m_tablerowptraStack;


         void reset();


      };


      class CLASS_DECL_AXIS layout_state3
      {
      public:
         int           m_iBody;
         float_array       m_yParent;
         float             m_y;
         //         float_array       m_cyStack;
         float_array       m_xParent;
         float_array       m_cya;
         //       int                           m_iy;
         float             m_x;
         float             m_cx;
         //         bool     m_bLastBlockX;
         //         bool     m_bLastCellX;
         bool              m_bLastBlock;
         bool              m_bLastCell;
         //bool     m_bHasChar;


         //ref_array < impl::table > m_tableptraStack;
         //ref_array < impl::table_row > m_tablerowptraStack;


         void reset();


      };

      ::user::form_callback* m_pcallback;
      ::user::interaction* m_puserinteraction;
      ::pointer<::draw2d::graphics>m_pgraphics;
      ::float_rectangle                              m_box;
      string                           m_strTitle;
      layout_state1                    m_layoutstate1;
      layout_state2                    m_layoutstate2;
      layout_state3                    m_layoutstate3;

      address_array < impl::table* >   m_tableptra;

      //string_map < ::image::image_pointer >     m_imagemap;

      pointer_array < font >                 m_fonta;

      ::user::interaction_ptra         m_focusptra;

      style_sheet_array                m_stylesheeta;
      ::file::path                     m_strPathName;
      ::user::interaction_ptra         m_uiptra;
      tag *                            m_ptag;
      ::pointer<::html::element>      m_pelement;
      bool                             m_bImplemented;


      bool                             m_bImplement;
      bool                             m_bLaidout;


      http::cookies* m_pcookies;
      //::account::user *            m_puser;
      //string                        m_strUser;
      //string                        m_strPassword;
      //string                        m_strLicense;

      //property_set                  m_propertyset;
      //property_set                  m_propset;
      string                        m_strSource;

      ::html_form *                 m_pform;
      bool                          m_bEdit;
      ::html::element *             m_pElementalSelStart;
      ::html::element *             m_pElementalSelEnd;

      bool                          m_bHasChar;

      bool                          m_bDrawFirstBody;


      core_data();
      ~core_data() override;


      void initialize_html_data(html_data * pdata) override;


      virtual string process_url(const ::string & pszUrl);
      //virtual long long increment_reference_count() override;
      //virtual long long decrement_reference_count() override;


      bool open_document(const ::payload & payloadFile) override;


      bool open_html(const ::string & str) override;


      bool open_link(const ::string & pszPath) override;


      ::user::form* get_form() override;
      ::pointer<::user::interaction>get_frame() override;


      //virtual bool is_locked();

      void load(const ::string &);
      void implement(::draw2d::graphics_pointer & pgraphics);
      void on_layout(::draw2d::graphics_pointer & pgraphics);
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void implement(::html_form * pform);
      void layout(::html_form * pform);
      void implement_and_layout(::html_form * pform);

      DECLARE_MESSAGE_HANDLER(on_message_key_down);

      ::image::image_pointer get_image(const ::string & pszUrl);
      void load_image_asynch(image* pimage);
      bool load_image(image* pimage);

      void on_image_loaded(image* pimage);


      ::html::element* get_element_by_name(atom atom);
      ::html::element* get_element_by_id(atom atom);

      void delete_contents();
      void destroy() override;
      void delete_implementation();

      virtual bool contains(::pointer<::user::interaction>pinteraction) override;

      virtual bool on_create_interaction(::pointer<::user::interaction>pinteraction) override;


      font* get_font(::html::element* pelemental);




      int create_font(::html::element* pelemental);

      void handle(::topic * ptopic, ::handler_context * pcontext) override;


   };


} // namespace html




