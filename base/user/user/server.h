#pragma once


#include "acme/user/user/e_window_flag.h"
#include "apex/message/channel.h"


namespace user
{


   class CLASS_DECL_BASE server :
      virtual public channel
   {
   public:


      server();
      ~server() override;

      virtual ::user::document * open_data(::data::data * pdata, bool bMakeVisible = true, ::user::interaction * puiParent = nullptr, e_window_flag eflag = e_window_flag(), ::atom atom = ::atom());

      virtual ::user::document* open_new_document(::platform::application * pappOnBehalfOf, bool bMakeVisible = true, ::user::interaction* puiParent = nullptr, e_window_flag eflag = e_window_flag(), ::atom atom = ::atom());

      virtual void on_request(::request * prequest) override;

      virtual ::user::document* open_document_file(::platform::application * pappOnBehalfOf, ::payload payloadFile, bool bMakeVisible = true, ::user::interaction* puiParent = nullptr, e_window_flag eflag = e_window_flag(), ::atom atom = ::atom());

      virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata, ::data::data * pdata);


   };


} // namespace user



