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

      virtual __pointer(::element) create_element() = 0;

      virtual void return_back(::element * pelement) = 0;


   };


   template < typename BASE_TYPE >
   class factory_item_base :
      public factory_item_interface
   {
   public:


      string base_type_name() const override { return ::demangle(typeid(BASE_TYPE).name()); }

      virtual __pointer(BASE_TYPE) _create() = 0;

      virtual __pointer(::element) create_element() override
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

      __pointer(BASE_TYPE) _create() override
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

      __pointer(BASE_TYPE) _create() override;

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


   using factory_base = id_map < __pointer(factory_item_interface) >;


   class CLASS_DECL_ACME factory :
      virtual public ::factory::factory_base
   {
   public:


      inline __pointer(::factory::factory_item_interface) & get_factory_item(const ::id & id);

      inline ::factory::factory_item_interface * get_factory_item(const ::id& id) const;

      template < typename BASE_TYPE >
      inline __pointer(::factory::factory_item_interface) & get_factory_item();

      template < typename TYPE, typename BASE_TYPE = TYPE >
      inline __pointer(::factory::factory_item_base < BASE_TYPE >) add_factory_item();

      template < typename BASE_TYPE >
      inline __pointer(BASE_TYPE) create();

      void merge(const ::factory::factory* pfactory);

      void merge_to_global_factory() const;


      //template < typename BASE_TYPE >
      //inline __pointer(BASE_TYPE) create()
      //{
      //   return m_pfactory->create <BASE_TYPE>();
      //}

      template < typename BASE_TYPE >
      inline void __construct(__pointer(BASE_TYPE)& p)
      {

         auto pNew = this->create <BASE_TYPE>();

         if (!pNew)
         {

            throw_status(error_no_factory);

         }

         p = pNew;

         if (!p)
         {

            throw_status(error_no_interface);

         }

         //return ::success;

      }


      template < typename BASE_TYPE >
      inline void __defer_construct(__pointer(BASE_TYPE)& p)
      {

         //::e_status3 estatus = ::success_not_constructed;

         if (::is_null(p))
         {

            /*estatus =*/ this->__construct(p);

         }

         ///return estatus;

      }


      template < typename BASE_TYPE >
      inline void __compose(::object * pobjectComposer, __composite(BASE_TYPE)& pcomposite);

      template < typename BASE_TYPE >
      inline void __raw_compose(::object* pobjectComposer, __composite(BASE_TYPE)& pusermessage);


      virtual __pointer(::element) create(const ::string & strType);


      virtual bool has_type(const ::string & strType) const;


   };


   CLASS_DECL_ACME critical_section * get_factory_critical_section();


   using factory_array = __pointer_array(factory_item_interface);


   CLASS_DECL_ACME factory_array * get_factory_item_array();

   CLASS_DECL_ACME factory * get_factory();

   CLASS_DECL_ACME void factory_init();

   CLASS_DECL_ACME void factory_close();

   CLASS_DECL_ACME void factory_term();

   
   inline __pointer(factory_item_interface) & get_factory_item(const ::id & id);

   
   inline void set_factory(const ::id & id, const __pointer(factory_item_interface) & pfactory);


   template < typename BASE_TYPE >
   inline __pointer(factory_item_interface) & get_factory_item()
   {

      string strTypename = typeid(BASE_TYPE).name();

      strTypename = demangle(strTypename);

      return get_factory_item(strTypename);

   }


} // namespace factory


using factory_pointer = __pointer(::factory::factory);


using factory_pointer = __pointer(::factory::factory);


namespace factory
{


   template < typename TYPE, typename BASE_TYPE = TYPE >
   inline __pointer(::factory::factory_item_base < BASE_TYPE >) add_factory_item(const ::id& id);


   template < typename TYPE, typename BASE_TYPE = TYPE >
   inline __pointer(::factory::factory_item_base < BASE_TYPE >) add_factory_item();


   template < typename TYPE, typename BASE_TYPE = TYPE >
   inline __pointer(::factory::factory_item_base < BASE_TYPE >) create_reusable_factory();


   template < typename TYPE >
   __pointer(TYPE) create();


} // namespace factory



