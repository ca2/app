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
   inline static bool bases(const pointer < T2 > & sp)
   {
      return dynamic_cast <T *> ((T2 *)sp.m_p) != nullptr;
   }

};




#define ASSERT_KINDOF(class_name, object) ASSERT(base_class < class_name > ::bases(object))
#define DYNAMIC_DOWNCAST(class_name, object) (dynamic_cast < class_name * > (object))
#define STATIC_DOWNCAST(class_name, object) (dynamic_cast<class_name*>(object))
#define STATIC_DOWNCAST_T(class_name, T1, object) (static_cast<class_name<T1>*>(::aura::StaticDownCast(RUNTIME_CLASS_T(class_name, T1), object)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, object) (static_cast<class_name<T1, T2>*>(::aura::StaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), object)))


