#include "framework.h"


namespace turboc
{


   document::document(::particle * pparticle) :
      ::object(pparticle),
      ::data::data_container_base(pparticle),
      ::aura::document(pparticle)
   {

   }


   document::~document()
   {

   }


   void document::assert_ok() const
   {

      ::aura::document::assert_ok();

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

      impact * pimpact = get_typed_impact < impact >();

/*      if(pimpact->m_pimageImage->load_image(payloadFile))
      {
         get_typed_impact < impact >()->m_strImage = payloadFile;
         get_typed_impact < impact >()->m_strHelloMultiverse = "image:"+ get_typed_impact < impact >()->m_strImage + ":" + get_typed_impact < impact >()->m_strHelloMultiverse;
      }
      else if(get_typed_impact < edit_impact >() != NULL)
      {

         string str = file()->as_string(payloadFile);

         str = str.left(84);

         get_typed_impact < edit_impact >()->set_text(str,::e_source_user);

      }
      else if(get_typed_impact < pane_impact >() != NULL)
      {

         get_typed_impact < pane_impact >()->set_current_tab_by_id(MAIN_IMPACT);
      }

      return true;

   }


   long long document::increment_reference_count()
   {

      return  ::aura::document::increment_reference_count();

   }

   long long document::decrement_reference_count()
   {

      return  ::aura::document::decrement_reference_count();

   }



} // namespace turboc

















