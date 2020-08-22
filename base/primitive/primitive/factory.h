#pragma once


namespace factory
{


   class CLASS_DECL_AURA factory_interface :
      virtual public context_object
   {
   public:


      factory_interface();
      virtual ~factory_interface();


      virtual __pointer(::generic_object) call_new() = 0;

      


   };


   template < typename BASE_TYPE >
   class factory_base :
      public factory_interface
   {
   public:


      virtual __pointer(BASE_TYPE) _call_new() = 0;

      virtual __pointer(::generic_object) call_new() override
      {

         return _call_new();

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


   using factory_map = id_map < __pointer(factory_interface) >;

   using factory_array = __pointer_array(factory_interface);

   CLASS_DECL_AURA extern factory_array * g_pfactorya;
   CLASS_DECL_AURA extern critical_section * g_pcsFactory;
   CLASS_DECL_AURA extern factory_map * g_pfactorymap;


   CLASS_DECL_AURA void factory_init();

   CLASS_DECL_AURA void factory_close();

   CLASS_DECL_AURA void factory_term();

   
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



