#include "framework.h"


namespace turboc
{


   document::document(::object * pobject) :
      ::object(pobject),
      ::data::data_container_base(pobject),
      ::aura::document(pobject)
   {

   }


   document::~document()
   {

   }


   void document::assert_valid() const
   {

      ::aura::document::assert_valid();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::aura::document::dump(dumpcontext);

   }


   bool document::on_new_document()
   {

      return ::aura::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      impact * pview = get_typed_view < impact >();

/*      if(pview->m_pimageImage->load_image(payloadFile))
      {
         get_typed_view < impact >()->m_strImage = payloadFile;
         get_typed_view < impact >()->m_strHelloMultiverse = "image:"+ get_typed_view < impact >()->m_strImage + ":" + get_typed_view < impact >()->m_strHelloMultiverse;
      }
      else if(get_typed_view < edit_view >() != NULL)
      {

         string str = pcontext->m_papexcontext->file().as_string(payloadFile);

         str = str.Left(84);

         get_typed_view < edit_view >()->_001SetText(str,::e_source_user);

      }
      else if(get_typed_view < pane_view >() != NULL)
      {

         get_typed_view < pane_view >()->set_current_tab_by_id(MAIN_IMPACT);
      }

      return true;

   }


   i64 document::increment_reference_count()
   {

      return  ::aura::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 document::decrement_reference_count()
   {

      return  ::aura::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }



} // namespace turboc

















