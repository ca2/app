#pragma once

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
//class html_view;
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






namespace html
{


//   namespace impl
//   {
//
//      class table;
//
//   } // namespace impl


   class CLASS_DECL_CORE core_data :
      virtual public ::html_data
   {
   public:


      class CLASS_DECL_CORE image :
         virtual public ::object
      {
      public:






         index                   m_iIndex;
         string                  m_strPath;
         ::image_pointer                 m_pimage;


         image();


         virtual bool load_image();

      };





      class CLASS_DECL_CORE layout_state1
      {
      public:

         float_array       m_cxa;
         float_array       m_cxMax;
         float_array       m_cya;
         bool                          m_bHasChar;
         float                         m_cy;


         void reset();


      };


      class CLASS_DECL_CORE layout_state2
      {
      public:
         i32      m_iBody;
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


      class CLASS_DECL_CORE layout_state3
      {
      public:
         i32           m_iBody;
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
      __pointer(::draw2d::graphics) m_pgraphics;
      ::rectf                              m_box;
      string                           m_strTitle;
      layout_state1                    m_layoutstate1;
      layout_state2                    m_layoutstate2;
      layout_state3                    m_layoutstate3;

      address_array < impl::table* >   m_tableptra;

      //string_map < image_pointer >     m_imagemap;

      __pointer_array(font)                 m_fonta;

      ::user::interaction_ptra         m_focusptra;

      style_sheet_array                m_stylesheeta;
      ::file::path                     m_strPathName;
      ::user::interaction_ptra         m_uiptra;
      tag *                            m_ptag;
      ::html::element                  m_element;
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
      virtual ~core_data();


      virtual ::e_status initialize_html_data(html_data * pdata) override;


      virtual string process_url(const char * pszUrl);
      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;


      virtual bool open_document(const ::payload & varFile) override;


      virtual ::e_status     open_html(const ::string & str) override;


      virtual bool open_link(const char* pszPath) override;


      virtual ::user::form* get_form() override;
      virtual __pointer(::user::interaction) get_frame() override;


      //virtual bool is_locked();

      void load(const char*);
      void implement(::draw2d::graphics_pointer & pgraphics);
      void on_layout(::draw2d::graphics_pointer & pgraphics);
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void implement(::html_form * pform);
      void layout(::html_form * pform);
      void implement_and_layout(::html_form * pform);

      DECL_GEN_SIGNAL(_001OnKeyDown);

      image_pointer get_image(const char* pszUrl);
      void load_image_asynch(image* pimage);
      bool load_image(image* pimage);

      void on_image_loaded(image* pimage);


      ::html::element* get_element_by_name(id id);
      ::html::element* get_element_by_id(id id);

      void delete_contents();
      void destroy();
      void delete_implementation();

      virtual bool contains(__pointer(::user::interaction) pinteraction) override;

      virtual bool on_create_interaction(__pointer(::user::interaction) pinteraction) override;


      font* get_font(::html::element* pelemental);




      i32 create_font(::html::element* pelemental);

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


   };


} // namespace html




