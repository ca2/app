#pragma once


namespace factory
{


   class CLASS_DECL_ACME factory_interface :
      virtual public matter
   {
   public:


      factory_interface();
      virtual ~factory_interface();


      virtual __pointer(::matter) call_new() = 0;

      virtual void return_back(::matter* pmatter) = 0;


   };


   template < typename BASE_TYPE >
   class factory_base :
      public factory_interface
   {
   public:


      virtual __pointer(BASE_TYPE) _call_new() = 0;

      virtual __pointer(::matter) call_new() override
      {

         return _call_new();

      }

      virtual void return_back(::matter* pmatter) override
      {

         delete pmatter;

      }


   };


   template < typename TYPE, typename BASE_TYPE >
   class factory :
      public factory_base < BASE_TYPE >
   {
   public:


      virtual __pointer(BASE_TYPE) _call_new()
      {

         return ::move_transfer(new TYPE());

      }


   };


   template < typename TYPE, typename BASE_TYPE >
   class reusable_factory :
      public factory < TYPE, BASE_TYPE >
   {
   public:

      critical_section m_cs;

      BASE_TYPE* m_pfree;

      ~reusable_factory()
      {

         free_all();

      }

      

      virtual __pointer(BASE_TYPE) _call_new()
      {

         {

            cslock lock(&m_cs);

            if (m_pfree)
            {

               auto pNew = m_pfree;

               m_pfree = pNew->m_pnext;

               pNew->reuse();

               return pNew;

            }

         }

         return factory < TYPE, BASE_TYPE >::_call_new();

      }


      void return_back(BASE_TYPE* p)
      {

         cslock lock(&m_cs);

         p->m_pnext = m_pfree;

         m_pfree = p;

      }

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

   using factory_map = id_map < __pointer(factory_interface) >;

   using factory_array = __pointer_array(factory_interface);


   CLASS_DECL_ACME factory_array * get_factory_array();
   CLASS_DECL_ACME critical_section * get_factory_critical_section();
   CLASS_DECL_ACME factory_map * get_factory_map();


   CLASS_DECL_ACME void factory_init();

   CLASS_DECL_ACME void factory_close();

   CLASS_DECL_ACME void factory_term();

   
   inline __pointer(factory_interface) & get_factory(const ::id & id);

   
   inline void set_factory(const ::id & id, const __pointer(factory_interface) & pfactory);


   template < typename BASE_TYPE >
   inline __pointer(factory_interface) & get_factory()
   {

      string strTypename(typeid(BASE_TYPE).name());

      demangle(strTypename);

      return get_factory(strTypename);

   }


} // namespace factory



template < typename TYPE, typename BASE_TYPE = TYPE >
//inline __pointer(::factory::factory_base < BASE_TYPE >) create_factory(const ::id & id = ::str::demangle(typeid(BASE_TYPE).name()));
inline __pointer(::factory::factory_base < BASE_TYPE >) create_factory(const ::id & id);


template < typename TYPE, typename BASE_TYPE = TYPE >
inline __pointer(::factory::factory_base < BASE_TYPE >) create_factory();


template < typename TYPE, typename BASE_TYPE = TYPE >
inline __pointer(::factory::factory_base < BASE_TYPE >) create_reusable_factory();


