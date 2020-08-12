#include "framework.h"


namespace user
{


   form_callback::form_callback()
   {
      
      m_pformpropertyset = nullptr;
      
   }
   
   
   //void form_callback::form_callback_as_property_set()
   //{
   // 
   //   m_pformpropertyset = this;
   //   
   //}


   form_callback::~form_callback()
   {

      //auto * ppair = m_pmapform->get_start();

      //while(ppair != nullptr)
      //{

      //   ppair->element2()->DestroyWindow();

      //   ppair = m_pmapform->get_next(ppair);

      //}

      //::aura::del(m_pmapform);

   }



   void form_callback::_001OnInitializeForm()
   {


   }

   
   void form_callback::_001OnInitializeControl(__pointer(control) pcontrol)
   {


   }


   //void form_callback::update(::user::form * pform, ::update & update)
   //{
   //   UNREFERENCED_PARAMETER(pform);
   //   UNREFERENCED_PARAMETER(pupdate);
   //}


   void form_callback::on_control_event(::user::control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

   }


   void form_callback::OnUser123(WPARAM wparam,LPARAM lparam)

   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);

   }


   //void form_callback::on_before_navigate(::form_data * pdata,var & varFile,u32 nFlags,const char * pszTargetFrameName,byte_array& baPostedData,const char * pszHeaders,bool* pbCancel)
   //{

   //   UNREFERENCED_PARAMETER(pdata);
   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(nFlags);
   //   UNREFERENCED_PARAMETER(pszTargetFrameName);

   //   UNREFERENCED_PARAMETER(baPostedData);
   //   UNREFERENCED_PARAMETER(pszHeaders);

   //   UNREFERENCED_PARAMETER(pbCancel);
   //}

   void form_callback::_001InitializeFormPreData(::user::form * pform)
   {
      UNREFERENCED_PARAMETER(pform);
   }


   //form_control * form_callback::get_form_control(const string & strId)
   //{

   //   return m_pmapform->operator[](strId);

   //}

   //::user::document * form_callback::get_form_document(const string & strId)
   //{

   //   auto passoc = m_pmapform->plookup(strId);

   //   if(passoc == nullptr)
   //      return nullptr;

   //   __pointer(::user::impact) pview = passoc->element2();

   //   if(pview.is_null())
   //      return nullptr;

   //   return pview->get_document();

   //}


   /*void form_callback::call_update(::user::form * pform, ::update & update)
    {
    
    if (!update.handled_by(this))
    {
    
    update.set_handled_by(this);
    
    this->update(pform, update);
    
    
    }
    
    }
    
    
    */

   
   //
   //::form_property_set * form_callback::get_form_property_set()
   //{
   //   
   //   if(::is_set(m_pformpropertyset))
   //   {
   //      
   //      return m_pformpropertyset;
   //      
   //   }
   //   
   //   return nullptr;
   //   
   //}
   

} // namespace user

