#pragma once


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


      string                           m_strToolbar;
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

      ::file::path                  m_strMatter;                 // IDR_ for frame/menu/accel as well
      //string                m_strServerMatter;           // IDR_ for OLE inplace frame/menu/accel
      //::u32                  m_nIDEmbeddingResource;        // IDR_ for OLE open frame/menu/accel
      //::u32                  m_nIDContainerResource;        // IDR_ for container frame/menu/accel

      ::type               m_typeDocument;         // class for creating new documents
      ::type               m_typeFrame;       // class for creating new frames
      ::type               m_typeView;        // class for creating new views
      //::type       m_pOleFrameClass;    // class for creating in-place frame
      //::type       m_pOleViewClass;     // class for creating in-place ::user::impact

      string                  m_strDocStrings;    // '\n' separated names
      // The ::user::document names sub-strings are represented as _one_ string:
      // windowTitle\ndocName\n ... (see DocStringIndex enum)

      impact_system(const ::string & pszMatter, ::type pDocClass, ::type pFrameClass, ::type pViewClass);
      virtual ~impact_system();


      virtual void dump(dump_context &) const override;
      virtual void assert_valid() const override;


      virtual void load_template();

      virtual ::count get_document_count() const = 0;
      virtual ::user::document * get_document(index index = 0) const = 0;

      virtual void add_document(::user::document * pDoc);      // must override
      virtual void erase_document(::user::document * pDoc);   // must override



      virtual bool GetDocString(string & rString, enum DocStringIndex index) const; // get one of the info strings
      //__pointer(::user::frame_window) CreateOleFrame(::user::interaction_impl * puiParent, ::user::document * pDoc,
      //   bool bCreateView);

      virtual void update_all_views(::user::impact * pimpact, const ::id & id);
      virtual void update_all_views(::subject * psubject);

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual Confidence MatchDocType(const ::file::path & pszPathName,::user::document *& rpDocMatch);

      virtual __pointer(::user::document) create_new_document(::create * pcreate);
      virtual __pointer(::user::frame_window) create_new_frame(::user::document * pDoc, __pointer(::user::frame_window) pOther, ::create * pcreate);
      virtual void InitialUpdateFrame(__pointer(::user::frame_window) pFrame, ::user::document * pDoc, bool bMakeVisible = true);
      virtual bool save_all_modified();     // for all documents
      virtual void pre_close_all_documents();
      virtual void close_all_documents(bool bEndSession);
      virtual void on_request(::create * pcreate) override = 0;
      // open named file
      // if pszPathName == nullptr => create new file with this type

      virtual void set_default_title(::user::document * pdocument) = 0;



      virtual void on_idle();             // for all documents
      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;


      bool on_open_document(::user::document * pdocument, ::create * pcreate);

      bool do_open_document(::user::document * pdocument, ::create * pcreate);

      virtual void reload_template();

   };


} // namespace user










