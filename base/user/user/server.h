#pragma once


namespace user
{


   class CLASS_DECL_BASE server :
      virtual public channel
   {
   public:


      server();
      ~server() override;


      virtual ::user::document* open_new_document(::app * pappOnBehalfOf, bool bMakeVisible = true, ::user::interaction* puiParent = nullptr, ewindowflag eflag = ewindowflag(), ::atom atom = ::atom());

      virtual void on_request(::create* pcreate) override;

      virtual ::user::document* open_document_file(::app * pappOnBehalfOf, ::payload payloadFile, bool bMakeVisible = true, ::user::interaction* puiParent = nullptr, ewindowflag eflag = ewindowflag(), ::atom atom = ::atom());

      virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   };


} // namespace user



