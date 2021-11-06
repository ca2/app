#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE input_text :
         public element,
         virtual public ::user::plain_edit_view::callback
      {
      public:


         i32 m_iFont;
         string m_strUnit;
         string m_strType;
         __pointer(::user::plain_edit) m_pedit;


         input_text(const ::string & strType = "", const ::string & strUnit = "");
         virtual ~input_text();


         void _001OnDraw(html_data * pdocument);


         virtual void implement_phase1(html_data * pdocument, ::html::element* pelemental);
         virtual bool layout_phase1(html_data * pdocument);
         virtual void layout_phase3(html_data * pdocument);
         void on_change_layout(html_data * pdocument);

      };


   } // namespace impl


} // namespace html





