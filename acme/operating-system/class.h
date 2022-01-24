#pragma once




template < class T >
class base_class
{
public:


   template < class T2 >
   inline static bool bases(T2 * p)
   {
      return dynamic_cast <T *> (p) != nullptr;
   }

   template < class T2 >
   inline static bool bases(const ___pointer < T2 > & p)
   {
      return dynamic_cast <T *> ((T2 *)p.m_p) != nullptr;
   }

};




#define ASSERT_KINDOF(class_name, matter) ASSERT(base_class < class_name > ::bases(matter))
#define DYNAMIC_DOWNCAST(class_name, matter) (dynamic_cast < class_name * > (matter))
#define STATIC_DOWNCAST(class_name, matter) (dynamic_cast<class_name*>(matter))
#define STATIC_DOWNCAST_T(class_name, T1, matter) (static_cast<class_name<T1>*>(::acme::StaticDownCast(RUNTIME_CLASS_T(class_name, T1), matter)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, matter) (static_cast<class_name<T1, T2>*>(::acme::StaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), matter)))


