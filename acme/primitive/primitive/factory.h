#pragma once


namespace factory
{


   class CLASS_DECL_ACME factory_item_interface :
      virtual public matter
   {
   public:


      factory_item_interface();
      ~factory_item_interface() override;


      virtual string base_type_name() const = 0;

      virtual string __type_name() const = 0;

      virtual ::pointer<::element>create_element() = 0;

      virtual void return_back(::element * pelement) = 0;


   };


   template < typename BASE_TYPE >
   class factory_item_base :
      public factory_item_interface
   {
   public:


      string base_type_name() const override { return ::demangle(typeid(BASE_TYPE).name()); }

      virtual ::pointer<BASE_TYPE>_create() = 0;

      virtual ::pointer<::element>create_element() override
      {

         return _create();

      }

      virtual void return_back(::element * pelement) override
      {

         delete pelement;

      }


   };


   template < typename TYPE, typename BASE_TYPE >
   class factory_item :
      public factory_item_base < BASE_TYPE >
   {
   public:


      string __type_name() const override { return ::demangle(typeid(TYPE).name()); }


      ::pointer<BASE_TYPE>_create() override
      {

         return __new(TYPE);
            
      }


   };


   template < typename TYPE, typename BASE_TYPE >
   class reusable_factory_item :
      public factory_item < TYPE, BASE_TYPE >
   {
   public:

      critical_section   m_criticalsection;

      BASE_TYPE * m_pfree;

      ~reusable_factory_item()
      {

         free_all();

      }

      ::pointer<BASE_TYPE>_create() override;

      void return_back(BASE_TYPE * p);

      void free_all()
      {

         while (m_pfree)
         {

            auto p = m_pfree;

            m_pfree = m_pfree->m_pnext;

            try
            {

               delete p;

            }
            catch (...)
            {

            }

         }

      }

   };


   using factory_base = id_map < ::pointer<factory_item_interface > >;


   class CLASS_DECL_ACME factory :
      virtual public factory_base
   {
   public:


      ::atom                                 m_atomSource;
      ::pointer<::acme::library>            m_plibrary;


      inline ::pointer<::factory::factory_item_interface>& get_factory_item(const ::atom & atom);

      //inline ::pointer<::factory::factory_item_interface>& get_factory_item_from(const ::atom& atom, const ::atom & atomSource);

      inline ::factory::factory_item_interface * get_factory_item(const ::atom& atom) const;

      //inline ::factory::factory_item_interface * get_factory_item_from(const ::atom& atom, const ::atom & atomSource) const;

      template < typename BASE_TYPE >
      inline ::pointer<::factory::factory_item_interface>& get_factory_item();

      template < typename BASE_TYPE >
      inline ::pointer<::factory::factory_item_interface>& get_factory_item(const ::atom& atom);

      //template < typename BASE_TYPE >
      //inline ::pointer<::factory::factory_item_interface>& get_factory_item_from(const ::atom & atomSource);

      template < typename TYPE, typename BASE_TYPE = TYPE >
      inline pointer< ::factory::factory_item_base < BASE_TYPE > > add_factory_item();

      //template < typename TYPE, typename BASE_TYPE >
      //inline pointer< ::factory::factory_item_base < BASE_TYPE > > add_factory_item_from(const ::atom& atomSource);


      template < typename BASE_TYPE >
      inline ::pointer<BASE_TYPE>create();

      void merge(const ::factory::factory* pfactory);

      void merge_to_global_factory() const;

      void set_currently_loading_library();


      //template < typename BASE_TYPE >
      //inline ::pointer<BASE_TYPE>create()
      //{
      //   return m_pfactory->create <BASE_TYPE>();
      //}

      template < typename BASE_TYPE >
      inline void __construct(::pointer<BASE_TYPE> & p)
      {

         auto pNew = this->create <BASE_TYPE>();

         if (!pNew)
         {

            throw ::exception(error_no_factory);

         }

         p = pNew;

         if (!p)
         {

            throw ::exception(error_no_interface);

         }

         //return ::success;

      }


      template < typename BASE_TYPE >
      inline void __defer_construct(::pointer<BASE_TYPE> & p)
      {

         //::e_status estatus = ::success_not_constructed;

         if (::is_null(p))
         {

            /*estatus =*/ this->__construct(p);

         }

         ///return estatus;

      }


      template < typename BASE_TYPE >
      inline void __construct(::object * pobjectComposer, ::pointer<BASE_TYPE> & pcomposite);

      //template < typename BASE_TYPE >
      //inline void __raw_construct(::object* pobjectComposer, ::pointer<BASE_TYPE> pusermessage);


      virtual ::pointer<::element>create(const ::string & strType);


      virtual bool has_type(const ::string & strType) const;


   };


   CLASS_DECL_ACME critical_section * get_factory_critical_section();


   using factory_array = pointer_array < factory_item_interface >;


   //CLASS_DECL_ACME factory_array * get_factory_item_array();

   CLASS_DECL_ACME factory * get_factory();

   CLASS_DECL_ACME factory * get_factory(const ::atom & atomSource);

   //CLASS_DECL_ACME void factory_init();

   //CLASS_DECL_ACME void factory_close();

   //CLASS_DECL_ACME void factory_term();

   
   inline ::pointer<factory_item_interface>& get_factory_item(const ::atom & atom);


   inline ::pointer<factory_item_interface>& get_existing_factory_item(const ::atom & atom);


   inline ::pointer<factory_item_interface>& get_factory_item(const ::atom & atom, const ::atom & atomSource);


   inline bool has(const ::atom& atom);
   

   
   inline void set_factory(const ::atom & atom, const ::pointer<factory_item_interface>& pfactory);

   template < typename BASE_TYPE >
   inline ::atom get_atom()
   {

      auto pszTypename = typeid(BASE_TYPE).name();

#ifdef WINDOWS

      pszTypename = c_demangle(pszTypename);

      return pszTypename;

#else

      auto strTypename = ::move(demangle(pszTypename));

      return strTypename;


#endif

   }


   template < typename BASE_TYPE >
   inline ::pointer<factory_item_interface>& get_factory_item()
   {

      static auto atom = get_atom<BASE_TYPE>();

      return get_factory_item(atom);

   }


   template < typename BASE_TYPE >
   inline ::pointer<factory_item_interface> get_factory_item(const ::atom & atomSource)
   {

      static auto atom = get_atom<BASE_TYPE>();

      return get_factory_item(atom, atomSource);

   }


   //void merge_library_to_global_factory(const ::atom & atomSource);


} // namespace factory


using factory_pointer = ::pointer<::factory::factory>;


using factory_pointer = ::pointer<::factory::factory>;


namespace factory
{


   template < typename TYPE, typename BASE_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < BASE_TYPE > > add_factory_item();


   template < typename TYPE, typename BASE_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < BASE_TYPE > > add_factory_item(const ::atom& atom);


   template < typename TYPE, typename BASE_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < BASE_TYPE > > add_factory_item_from(const ::atom& atomSource);


   template < typename TYPE, typename BASE_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < BASE_TYPE > > create_reusable_factory();


   template < typename TYPE >
   ::pointer<TYPE>create();


} // namespace factory



