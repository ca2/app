#pragma once


#include "base/user/user/server.h"


namespace user
{


   class CLASS_DECL_BASE impact_system :
      virtual public server
   {
   public:


      enum DocStringIndex
      {

         windowTitle,        // default interaction_impl title
         docName,            // ::account::user visible name for default ::user::document
         fileNewName,        // ::account::user visible name for FileNew
         // for file based documents:
         filterName,         // ::account::user visible name for FileOpen
         filterExt,          // ::account::user visible extension for FileOpen
         // for file based documents with Shell open support:
         regFileTypeId,      // REGEDIT visible registered file type identifier
         regFileTypeName    // Shell visible registered file type name

      };


      enum Confidence
      {

         noAttempt,
         maybeAttemptForeign,
         maybeAttemptNative,
         yesAttemptForeign,
         yesAttemptNative,
         yesAlreadyOpen

      };


      ::atom                           m_atomImpactSystem;
      //::atom                             m_atomToolbar;
      bool                             m_bHiddenOnNotifyIcon;

      ::user::interaction *            m_puserinteractionOwner;
      // back pointer to OLE or other server (nullptr if none or disabled)
      object *                         m_pAttachedFactory;

      // menu & accelerator resources for in-place container
      //HMENU                 m_hMenuInPlace;
      //HACCEL                m_hAccelInPlace;

      // menu & accelerator resource for server editing embedding
      //HMENU                 m_hMenuEmbedding;
      //HACCEL                m_hAccelEmbedding;

      // menu & accelerator resource for server editing in-place
      //HMENU                 m_hMenuInPlaceServer;
      //HACCEL                m_hAccelInPlaceServer;

      //::file::path                  m_strMatter;                 // IDR_ for frame/menu/accel as well
      //string                m_strServerMatter;           // IDR_ for OLE inplace frame/menu/accel
      //unsigned int                  m_nIDEmbeddingResource;        // IDR_ for OLE open frame/menu/accel
      //unsigned int                  m_nIDContainerResource;        // IDR_ for container frame/menu/accel

      ::type_atom          m_typeatomDocument;         // class for creating ___new documents
      ::type_atom          m_typeatomFrame;       // class for creating ___new frames
      ::type_atom          m_typeatomImpact;        // class for creating ___new impacts
      ::type_atom          m_typeatomData;        // class for creating ___new data
      //::type       m_pOleFrameClass;    // class for creating in-place frame
      //::type       m_pOleImpactClass;     // class for creating in-place ::user::impact

      string                  m_strDocStrings;    // '\n' separated names
      // The ::user::document names sub-strings are represented as _one_ string:
      // windowTitle\ndocName\n ... (see DocStringIndex enum)

      impact_system(const ::atom & atom, const ::type_atom & typeatomDocument, const ::type_atom & typeatomFrame, const ::type_atom & typeatomImpact, const ::type_atom & typeatomData);
      ~impact_system() override;


      //void dump(dump_context &) const override;
      // void assert_ok() const override;


      virtual void load_impact_system();

      virtual ::collection::count get_document_count() const = 0;
      virtual ::user::document * get_document(::collection::index index = 0) const = 0;

      virtual void add_document(::user::document * pDoc);      // must override
      virtual void erase_document(::user::document * pDoc);   // must override



      virtual bool GetDocString(string & rString, enum DocStringIndex index) const; // get one of the info strings
      //::pointer<::user::frame_window>CreateOleFrame(::windowing::window * puiParent, ::user::document * pDoc,
      //   bool bCreateImpact);

      virtual void update_all_impacts(::user::impact * pimpact, const ::atom & atom);
      virtual void update_all_impacts(::topic * ptopic);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual Confidence MatchDocType(const ::file::path & pathName,::user::document *& rpDocMatch);

      virtual ::pointer<::user::document>create_new_document(::request * prequest);
      virtual ::pointer<::user::frame_window>create_new_frame(::user::document * pDoc, ::pointer<::user::frame_window>Other, ::request * prequest);
      virtual void prepare_frame(::user::frame_window * pframe, ::user::document * pdocument, bool bMakeVisible = true);
      virtual bool save_all_modified();     // for all documents
      virtual void pre_close_all_documents();
      virtual void close_all_documents(bool bEndSession);
      virtual void on_request(::request * prequest) override = 0;
      virtual void on_request_continuation(::user::document * pdocument, ::user::frame_window * pframewindow, ::request * prequest);
      // open named file
      // if pszPathName == nullptr => create ___new file with this type

      virtual void set_default_title(::user::document * pdocument) = 0;



      virtual void on_idle();             // for all documents
      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;


      bool on_open_document(::user::document * pdocument, ::request * prequest);

      bool do_open_document(::user::document * pdocument, ::request * prequest);

      virtual void reload_template();

   };


} // namespace user










