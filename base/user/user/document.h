#pragma once


namespace user
{


   class CLASS_DECL_BASE document :
      virtual public ::user::controller,
      virtual public ::data::data_container_base
   {
   public:



      bool                                m_bAutoDelete;     // true => delete document when no more views
      bool                                m_bEmbedded;       // true => document is being created by OLE

      __pointer(::create)                 m_pcreate;
      string                              m_strTitle;
      ::file::path                        m_path;
      bool                                m_bModified;
      bool                                m_bNew;
      bool                                m_bCustomOpen;

      __pointer(::user::impact_system)       m_pimpactsystem;
      __pointer_array(::user::impact)        m_viewa;
      ::user::impact *                          m_pviewTopic;

      bool                                m_bAutoSaveModified;

      string                              m_strSaveFileExtension;
      id_map < ::routine_array >          m_mapRoutine;



      document();
      ~document() override;


      void dump(dump_context &) const override;
      void assert_valid() const override;


      inline ::base::application* get_application() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      ::user::interaction* impact_at(::index iImpact) const override;
      ::count impact_count() const override;

      ::user::interaction_array get_top_level_windows();

      void destroy_composites() override;

      virtual bool contains(::user::interaction* pinteraction) const;

      void on_request(::create* pcreate) override;


      virtual ::id get_topic_view_id();
      virtual bool set_topic_view_by_id(::id id);

      virtual void update_title();

      virtual void on_create(::create * pcreate);

      const string & get_title() const;
      virtual void set_title(const ::string & pszTitle);

      virtual string get_save_file_extension();

      const ::file::path & get_file_path() const;
      virtual void set_path_name(::payload payloadFile, bool bAddToMRU = true);

      ::user::impact_system * get_document_template() const;
      virtual bool is_modified();
      virtual void set_modified_flag(bool bModified = true);
      virtual void set_new(bool bNew = true);

      virtual bool is_new_document();

      // Operations
      void add_view(::user::impact * pview);
      void erase_view(::user::impact * pview);
      virtual ::count get_view_count() const;
      virtual __pointer(::user::impact) get_view(index index = 0) const;



      template < class T >
      ::count get_typed_view_count() const
      {
         synchronous_lock synchronouslock(((document *)this)->mutex());
         ::count count = 0;
         for (index index = 0; index < m_viewa.get_count(); index++)
         {
            if (m_viewa[index].is_null())
            {
               continue;
            }
            __pointer(T) point = m_viewa[index].cast < T > ();
            if (point.is_set())
               count++;
         }
         return count;
      }

      template < class T >
      __pointer(T) get_typed_view(index indexFind = 0) const
      {

         synchronous_lock synchronouslock(((document *)this)->mutex());

         if (indexFind < 0 || indexFind >= m_viewa.get_count())
         {

            return nullptr;

         }

         ::count count = 0;

         for (index index = 0; index < m_viewa.get_count(); index++)
         {

            if(m_viewa[index].is_null())
            {

               continue;

            }

            __pointer(T) point = m_viewa[index].cast < T > ();

            if (point.is_set())
            {

               if (indexFind == count)
               {

                  return point;

               }
               else
               {

                  count++;

               }

            }

         }

         return nullptr;

      }


      template < class T >
      __pointer(T) get_typed_view_with_id(id id) const
      {

         synchronous_lock synchronouslock(((document *)this)->mutex());

         ::count count = 0;

         for(index index = 0; index < m_viewa.get_count(); index++)
         {

            if(m_viewa[index].is_null())
            {
               continue;
            }

            __pointer(T) point = m_viewa[index].cast < T >();

            if(point.is_set())
            {

               if(id == point->m_id)
                  return point;
               else
                  count++;

            }

         }

         return nullptr;

      }

      //bool                             m_bAutoDelete;     // true => delete document when no more views
      //bool                             m_bEmbedded;       // true => document is being created by OLE


      //controller();
      //virtual ~controller();


      //      virtual ::stream & write(::stream & stream) const override;
      //virtual ::stream & read(::stream & stream) override;

      template < typename DATA >
      __transport(DATA) __create_data()
      {

         auto pdata = __create_new<DATA>();

         if (!pdata)
         {

            return pdata;

         }

         auto estatus = pdata->initialize_data(this);

         if (!estatus)
         {

            return estatus;

         }

         return pdata;


      }



      virtual __pointer(::user::impact) get_typed_view(::type info, index indexFind = 0);

      virtual __pointer(::user::impact) get_typed_view_with_id(::type info,id id);

      virtual void show_all_frames(const ::edisplay & edisplay = e_display_normal);


      //class update
      //{
      //public:
      //   __pointer(::user::impact)         m_pSender;
      //   LPARAM         m_lHint;
      //   ::object *  m_pHint;
      //};

      // Update Views (simple update - DAG only)
      void id_update_all_views(const ::id & id);
      void update_all_views(impact * pimpact, const ::id & id);
      virtual void update_all_views(::subject * psubject);


      virtual void handle(::subject * psubject, ::context * pcontext) override;

      //void send_update(__pointer(::user::impact) pSender, LPARAM lHint = 0L,
      //                 ::object* pHint = nullptr);

      // Overridables
      // Special notifications
      virtual void on_changed_view_list(); // after add or erase ::user::impact
      virtual void delete_contents(); // delete doc items etc

      virtual bool new_document();
      virtual bool open_document(::create * pcreate);
      virtual bool open_document(const ::payload & payloadFile);
      virtual bool save_document();
      virtual bool defer_save_document();

      // File helpers
      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile);
      virtual bool on_open_document(::file::file * pfile);
      virtual bool on_save_document(const ::payload & payloadFile);
      virtual bool on_save_document(::file::file * pfile);
      virtual void on_close_document();
      virtual void pre_close_document();
      virtual void close_document();
      virtual void report_load_exception(const ::payload & payloadFile, ::file_pointer presult, const ::string & pszDefault);
      virtual void report_save_exception(const ::payload & payloadFile, ::file_pointer presult, const ::string & pszDefault);
      virtual void report_save_load_exception(const ::payload & payloadFile, ::file_pointer presult, bool bSave, const ::string & pszDefault);


      // advanced overridables, closing down frame/doc, etc.
      virtual bool can_close_frame(::user::frame_window * pframe);
      virtual bool save_modified(); // return true if ok to continue
      virtual void pre_close_frame(::user::frame_window * pframe);




      // implementation helpers
      virtual bool on_filemanager_open(::filemanager::document * pfilemanagerdocument, ::payload payloadFile);
      virtual bool on_filemanager_save(::filemanager::document * pfilemanagerdocument, ::payload payloadFile, bool bReplace = true);
      virtual bool do_save(::payload payloadFile, bool bReplace = true);
      virtual bool do_file_save();
      virtual void update_frame_counts();
      virtual void disconnect_views();
      virtual void call_initial_update();


//#ifdef WINDOWS_DESKTOP
//      // overridables for implementation
//      virtual HMENU GetDefaultMenu(); // get menu depending on state
//      virtual HACCEL GetDefaultAccelerator();
//#endif
      virtual void on_idle();
      virtual void on_final_release();

      //void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      friend class impact_system;


      void on_file_close();
      void on_file_save();
      void on_file_save_as();
      void on_file_send_mail();
      void on_update_file_send_mail(::message::command* pCmdUI);

      //virtual void on_request(::create * pcreate) override;

      template < class DOCUMENT >
      DOCUMENT * get_typed_document()
      {
         ASSERT(::is_set(this));
         return dynamic_cast < DOCUMENT * >(this);
      }

      template < class DATA >
      __pointer(DATA) get_typed_data()
      {

         for (auto & pair : m_datamap)
         {

            auto pdata = pair.element2().cast < DATA >();

            if (pdata)
            {

               return pdata;

            }

         }

         return nullptr;

      }

      template < class DOCUMENT >
      ::data::data * get_typed_document_data()
      {
         ASSERT(::is_set(this));
         return get_data(get_typed_document < DOCUMENT > ());
      }

      template < class DOCUMENT >
      ::data::data * get_data(DOCUMENT * pthis)
      {
         ASSERT(this == pthis);
         if (this != pthis)
            return nullptr;
         return m_datamap[pthis];
      }

      template < class DOCUMENT >
      void set_typed_document_data(::data::data * pdata)
      {
         ASSERT(::is_set(this));
         set_data(get_typed_document < DOCUMENT >(), pdata);
      }




      virtual void form_document_set_property_set(const property_set & set);
      virtual property_set * form_document_get_property_set();
      virtual property_set & form_document_property_set();

      virtual ::id get_toolbar_id();

      virtual __transport(toolbar) get_toolbar(::user::frame_window * pframe, bool bCreate = true);


   };


   CLASS_DECL_BASE __pointer(::user::document) __document(::create * pcreate);

} // namespace user




