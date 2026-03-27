#pragma once


#include "application.h"
#include "apex/platform/app_consumer.h"
#include "berg/user/user/document.h"


namespace coding
{


   class CLASS_DECL_CODING document :
      virtual public ::app_consumer < application, ::user::document >
   {
   public:




      ::coding::impact* m_pintegrationimpact;


      ::pointer < ::coding::integration > m_pintegration;



      document();
      ~document() override;


      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;
      virtual bool on_save_document(::file::file * pwriter) override;

#ifdef _DEBUG
      
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;

#endif



   };


} // namespace coding



