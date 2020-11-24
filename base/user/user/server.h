#pragma once


namespace user
{


   class CLASS_DECL_BASE server :
      virtual public channel
   {
   public:


      server();
      virtual ~server();


      virtual ::user::document* open_new_document(::apex::application* pappOnBehalfOf, bool bMakeVisible = true, ::user::interaction* puiParent = nullptr, ewindowflag eflag = ewindowflag(), ::id id = ::id());


      virtual void on_request(::create* pcreate) override;

      virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, payload varFile, bool bMakeVisible = true, ::user::interaction* puiParent = nullptr, ewindowflag eflag = ewindowflag(), ::id id = ::id());

      virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);

   };


} // namespace user



