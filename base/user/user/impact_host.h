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
         virtual public ::exception
      {
      public:


         atom       m_atom;

         exception(atom atom) : m_atom(atom) {}


      };


      impact_data_map                              m_impactdatamap;

      __pointer_array(::user::impact_kit)          m_impactkita;
      __pointer_array(::user::impact_kit::item)    m_impactkititema;


      impact_host();
      ~impact_host() override;


      void install_message_routing(::channel * pchannel) override;




      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


      virtual void add_impact_kit2(::user::impact_kit * pimpactkit);

      //virtual void _add_impact_kit(::user::impact_kit * pimpactkit);

      ::user::impact_kit * find_impact_kit(const ::atom & atom = nullptr);

      ::user::impact_kit * get_impact_kit(const ::atom & atom = nullptr);


      virtual void add_impact_kit_items();


      virtual bool add_impact(const ::string & strName, const ::atom & atomImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr);
      virtual bool add_impact_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & atomImpact = nullptr, bool bVisible = true, bool bPermanent = false, ::user::place_holder * pholder = nullptr);

      virtual bool set_impact(const ::string & strName, const ::atom & atomImpact = nullptr, bool bVisible = true, ::user::place_holder * pholder = nullptr);
      virtual bool set_impact_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & atomImpact = nullptr, bool bVisible = true, ::user::place_holder * pholder = nullptr);

      
      bool create_impact(::user::impact_data * pimpactdata) override;


      impact_data * create_impact_by_id(const ::atom & atom);


      virtual bool on_prepare_impact_data(::user::impact_data * pimpactdata);
      virtual bool on_after_create_impact_data(::user::impact_data * pimpactdata);
      virtual void on_change_cur_sel();


      virtual ::user::impact_data * new_impact_data(const atom & atom);
      virtual ::user::impact_data * allocatimpact_data(const atom & atom);


      virtual ::user::impact_data * host_impact(const atom& atom, ::user::interaction * pinteraction, ::user::document * pdocument);

      virtual ::user::place_holder* updown_target_get_place_holder(::user::interaction* pinteraction, ::user::document* pdocument);

      virtual ::user::impact_data * impact_host_get_impact_data(const atom& atom, ::user::interaction* pinteraction, ::user::document* pdocument);


      virtual void on_erase_child(::user::interaction* pinteraction) override;
      virtual void on_erase_place_holder_child(::user::interaction* pinteraction) override;


      virtual void on_hide_child(::user::interaction* pinteraction) override;
      virtual void on_hide_place_holder_child(::user::interaction* pinteraction) override;


      template < class VIEW >
      __pointer(VIEW) host_impact(const ::atom & atom)
      {

         impact_data* pimpactdata = allocatimpact_data(atom);

         pimpactdata->m_puserinteraction = create_impact <VIEW>(pimpactdata);

         pimpactdata->m_pdocument = get_document();

         pimpactdata->m_bOk = true;

         on_after_host_impact(pimpactdata);

         return pimpactdata->m_puserinteraction;

      }


      //virtual ::user::impact_data * create_impact(const atom  & atom, const string& strTitle = "", impact_creator * pcreator = nullptr);
      //virtual void create_impact(::user::impact_data * pimpactdata, impact_creator * pcreator = nullptr);
      //virtual bool _create_impact(impact_creator * pcreator, ::user::impact_data * pimpactdata);


      virtual void on_after_host_impact(::user::impact_data * pimpactdata);

      virtual bool is_hosting(::user::interaction * pinteraction);

      virtual ::user::impact_data * get_impact_data(const atom& atom, bool bCallOnCreateImpact = true);


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      virtual ::count get_impact_count();

      virtual atom get_impact_id();
      virtual __pointer(::user::impact) get_impact();
      virtual ::user::document * get_impact_document();


      virtual void hide_all_except(const id_array & atom);


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


