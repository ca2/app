#pragma once


namespace user
{


   CLASS_DECL_BASE ::user::document* get_document(::user::interaction* pinteraction);


   class impact_data;


   class CLASS_DECL_BASE impact_host :
      virtual public ::user::impact,
      virtual public ::user::impact_creator
   {
   public:


      class CLASS_DECL_BASE exception :
         virtual public ::exception::exception
      {
      public:


         id       m_id;

         exception(id id) : m_id(id) {}


      };


      impact_data_map      m_impactdatamap;


      impact_host();
      virtual ~impact_host();


      virtual void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnDestroy);

      //virtual class impact_data * new_impact_data(impact_creator * pimpactcreator, id id);

      virtual bool on_prepare_impact_data(::user::impact_data * pimpactdata);
      virtual bool on_after_create_impact_data(::user::impact_data * pimpactdata);
      virtual void on_change_cur_sel();


      virtual ::user::impact_data * new_impact_data(const id & idconst, const ::id & idTitle = "");
      virtual ::user::impact_data * allocate_impact_data(const id & id, const ::id & idTitle = "");


      virtual ::user::impact_data * host_impact(const id& id, const ::id & idTitle, ::user::interaction * pinteraction, ::user::document * pdocument);

      virtual ::user::place_holder* updown_target_get_place_holder(::user::interaction* pinteraction, ::user::document* pdocument);

      virtual ::user::impact_data * impact_host_get_impact_data(const id& id, const ::id& idTitle, ::user::interaction* pinteraction, ::user::document* pdocument);


      virtual void on_erase_child(::user::interaction* pinteraction) override;
      virtual void on_erase_place_holder_child(::user::interaction* pinteraction) override;


      virtual void on_hide_child(::user::interaction* pinteraction) override;
      virtual void on_hide_place_holder_child(::user::interaction* pinteraction) override;


      template < class VIEW >
      __pointer(VIEW) host_view(const ::id & id, const ::id & idTitle = "")
      {

         impact_data* pimpactdata = allocate_impact_data(id, idTitle);

         pimpactdata->m_puserinteraction = create_view <VIEW>(pimpactdata);

         pimpactdata->m_pdocument = get_document();

         pimpactdata->m_bOk = true;

         on_after_host_impact(pimpactdata);

         return pimpactdata->m_puserinteraction;

      }


      virtual ::user::impact_data * create_impact(const id  & id, const string& strTitle = "", impact_creator * pcreator = nullptr);
      virtual void create_impact(::user::impact_data * pimpactdata, impact_creator * pcreator = nullptr);
      virtual bool _create_impact(impact_creator * pcreator, ::user::impact_data * pimpactdata);


      virtual void on_after_host_impact(::user::impact_data * pimpactdata);

      virtual bool is_hosting(::user::interaction * pinteraction);

      virtual ::user::impact_data * get_impact_data(const id& id, bool bCallOnCreateView = true);


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


      virtual ::count get_view_count();

      virtual id get_view_id();
      virtual __pointer(::user::impact) get_view();
      virtual ::user::document * get_view_document();


      virtual void hide_all_except(const id_array & id);


      template < class T > __pointer(T) get_typed_document()
      {

         __pointer(T) pdocument;

         for(auto & pair : m_impactdatamap)
         {

            auto key = pair.element1();

            auto pimpactdata = pair.element2();

            if(pimpactdata->m_pdocument != nullptr)
            {

               pdocument = pimpactdata->m_pdocument;

               if(pdocument)
               {

                  return pdocument;

               }

            }

         }

         return nullptr;

      }

   };


} // namespace user


