#pragma once




template < class T >
class base_class
{
public:


   template < class T2 >
   inline static bool bases(T2 * point)
   {
      return dynamic_cast <T *> (point) != nullptr;
   }

   template < class T2 >
   inline static bool bases(const ___pointer < T2 > & sp)
   {
      return dynamic_cast <T *> ((T2 *)sp.m_p) != nullptr;
   }

};




#define ASSERT_KINDOF(class_name, elemental) ASSERT(base_class < class_name > ::bases(elemental))
#define DYNAMIC_DOWNCAST(class_name, elemental) (dynamic_cast < class_name * > (elemental))
#define STATIC_DOWNCAST(class_name, elemental) (dynamic_cast<class_name*>(elemental))
#define STATIC_DOWNCAST_T(class_name, T1, elemental) (static_cast<class_name<T1>*>(::acme::StaticDownCast(RUNTIME_CLASS_T(class_name, T1), elemental)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, elemental) (static_cast<class_name<T1, T2>*>(::acme::StaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), elemental)))


