#pragma once



#include "acme/prototype/data/container.h"
#include "acme/user/user/controller.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/handler/manager.h"
#include "apex/message/channel.h"


namespace user
{


   class CLASS_DECL_BASE document :
      virtual public ::user::controller,
      virtual public ::channel,
      virtual public ::manager,
      virtual public ::data::data_container_base
   {
   public:



      bool                                m_bAutoDelete;     // true => delete document when no more views
      bool                                m_bEmbedded;       // true => document is being created by OLE

      ::pointer<::request>                m_prequest;
      string                              m_strTitle;
      ::file::path                        m_path;
      bool                                m_bModified;
      bool                                m_bNew;
      bool                                m_bCustomOpen;

      ::pointer<::user::impact_system>    m_pimpactsystem;
      pointer_array < ::user::impact >    m_impacta;
      ::pointer < ::user::impact >        m_pimpactTopic;

      bool                                m_bAutoSaveModified;

      string                              m_strSaveFileExtension;
      atom_map < ::procedure_array >      m_mapRoutine;
      bool                                m_bToolbar;
      ::pointer < ::data::data >          m_pdataIncoming;


      document();
      ~document() override;


      void destroy() override;


      ::pointer < ::data::data > create_data(const ::atom & atom) override;


      // ::base::application * get_app();
      // ::base::session * get_session();
      // ::base::system * get_system();
      // ::base::user * user() override;


      ::user::interaction* impact_at(::collection::index iImpact) override;
      ::collection::count impact_count() override;

      ::user::interaction_array get_top_level_windows();

      void on_destroy() override;

      virtual bool contains(::user::interaction* pinteraction) const;

      void on_request(::request * prequest) override;


      virtual ::string get_topic_impact_id();
      virtual bool set_topic_impact_by_id(::atom atom);

      virtual void update_title();

      virtual void on_create(::request * prequest);

      const string & get_title() const;
      virtual void set_title(const ::scoped_string & scopedstrTitle);

      virtual string get_save_file_extension();

      virtual ::file::path get_file_path() const;
      virtual void set_path_name(::payload payloadFile, bool bAddToMRU = true);

      ::user::impact_system * get_document_template() const;
      virtual bool is_modified();
      virtual void set_modified_flag(bool bModified = true);
      virtual void set_new(bool bNew = true);

      virtual bool is_new_document();

      
      void add_impact(::user::impact * pimpact);
      void erase_impact(::user::impact * pimpact);
      virtual ::collection::count get_impact_count() const;
      virtual ::pointer<::user::impact>get_impact(::collection::index index = 0) const;



      template < class T >
      ::collection::count get_typed_impact_count() const
      {
         synchronous_lock synchronouslock(((document *) this)->synchronization());
         ::collection::count count = 0;
         for (::collection::index index = 0; index < m_impacta.get_count(); index++)
         {
            if (m_impacta[index].is_null())
            {
               continue;
            }
            auto p = m_impacta[index].cast < T > ();
            if (p)
               count++;
         }
         return count;
      }

      template < class T >
      pointer < T > get_typed_impact(::collection::index indexFind = 0) const
      {

         synchronous_lock synchronouslock(((document *) this)->synchronization());

         if (indexFind < 0 || indexFind >= m_impacta.get_count())
         {

            return nullptr;

         }

         ::collection::count count = 0;

         for (::collection::index index = 0; index < m_impacta.get_count(); index++)
         {

            if(m_impacta[index].is_null())
            {

               continue;

            }

            auto p = m_impacta[index].cast < T > ();

            if (p)
            {

               if (indexFind == count)
               {

                  return p;

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
      pointer < T > get_typed_impact_with_id(atom atom) const
      {

         synchronous_lock synchronouslock(((document *) this)->synchronization());

         ::collection::count count = 0;

         for(::collection::index index = 0; index < m_impacta.get_count(); index++)
         {

            if(m_impacta[index].is_null())
            {
               continue;
            }

            auto p = m_impacta[index].cast < T >();

            if(p)
            {

               if (atom == p->id())
               {

                  return p;

               }
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
      ::pointer<DATA>__create_data()
      {

         auto pdata = __create_new<DATA>();

         if (!pdata)
         {

            return pdata;

         }

         //auto estatus = 
         
         //pdata->initialize_data(this);

         pdata->initialize_data();

         //if (!estatus)
         //{

         //   return estatus;

         //}

         return pdata;


      }



      virtual ::pointer<::user::impact>get_typed_impact(const ::type_atom & typeatom, ::collection::index indexFind = 0);

      virtual ::pointer<::user::impact>get_typed_impact_with_id(const ::type_atom & typeatom,atom atom);

      virtual void show_all_frames(const ::e_display & edisplay = e_display_normal);


      //class update
      //{
      //public:
      //   ::pointer<::user::impact>        m_pSender;
      //   LPARAM         m_lHint;
      //   ::object *  m_pHint;
      //};

      // Update Impacts (simple update - DAG only)
      void id_update_all_impacts(const ::atom & atom) override;
      virtual void update_all_impacts(impact * pimpact, const ::atom & atom);
      virtual void update_all_impacts(::topic * ptopic) override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //void send_update(::pointer<::user::impact>pSender, LPARAM lHint = 0L,
      //                 ::object* pHint = nullptr);

      // Overridables
      // Special notifications
      virtual void on_changed_impact_list(); // after add or erase ::user::impact
      virtual void delete_contents(); // delete doc items etc

      virtual bool new_document();
      virtual bool open_document(::request * prequest);
      virtual bool open_document(const ::payload & payloadFile);
      virtual bool save_document();
      virtual bool defer_save_document();

      // File helpers
      virtual bool open_data(::data::data * pdata);
      virtual bool on_open_data(::data::data * pdata);
      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile);
      virtual bool on_open_document(::file::file * pfile);
      virtual bool on_save_document(const ::payload & payloadFile);
      virtual bool on_save_document(::file::file * pfile);
      virtual void on_close_document();
      virtual void pre_close_document();
      virtual void close_document();
      virtual void report_load_exception(const ::payload & payloadFile, ::file_pointer presult, const ::scoped_string & scopedstrDefault);
      virtual void report_save_exception(const ::payload & payloadFile, ::file_pointer presult, const ::scoped_string & scopedstrDefault);
      virtual void report_save_load_exception(const ::payload & payloadFile, ::file_pointer presult, bool bSave, const ::scoped_string & scopedstrDefault);


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
      virtual void disconnect_impacts();
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

      //virtual void on_request(::request * prequest) override;

      template < class DOCUMENT >
      DOCUMENT * get_typed_document()
      {
         ASSERT(::is_set(this));
         return dynamic_cast < DOCUMENT * >(this);
      }

      template < class DATA >
      ::pointer<DATA>get_typed_data()
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

      //template < class DOCUMENT >
      //::data::data * get_data(DOCUMENT * pthis)
      //{
      //   ASSERT(this == pthis);
      //   if (this != pthis)
      //      return nullptr;
      //   return m_datamap[pthis];
      //}

      template < class DOCUMENT >
      void set_typed_document_data(::data::data * pdata)
      {
         ASSERT(::is_set(this));
         set_data(get_typed_document < DOCUMENT >(), pdata);
      }


      virtual void form_document_set_property_set(const ::property_set & set);
      virtual ::property_set * form_document_get_property_set();
      virtual ::property_set & form_document_property_set();


      virtual bool has_toolbar();
      
      virtual ::atom get_toolbar_id();

      virtual toolbar * get_toolbar(::user::frame_interaction * pframe, bool bCreate = true);


   };


   CLASS_DECL_BASE ::pointer<::user::document>__document(::request * prequest);


} // namespace user




