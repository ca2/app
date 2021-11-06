#pragma once




template < class root_derived >
inline i64 increment_reference_count(root_derived * pca);

template < class root_derived >
inline i64 release(root_derived * & pca);

// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system nullptr/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
template < class T >
class pointer
{
public:

   using TYPE = T;

   T * m_p;


   inline pointer();
   inline pointer(std::nullptr_t);
   inline pointer(const lparam& lparam);

   inline pointer(const pointer & t);
   inline pointer(pointer && t);
   inline pointer(const ::trait & trait);
   template < typename OBJECT >
   inline pointer(e_create_new, OBJECT * p);
   template < typename OBJECT >
   inline pointer(e_move_transfer, OBJECT * p);

   template < class T2 >
   inline pointer(const T2 * p)
   {

      if(::is_null(p))
      {

         m_p = nullptr;

         return;

      }

      m_p = dynamic_cast < T * > ((T2 *) p);

      ::increment_reference_count(m_p);

   }


   inline bool operator !() const
   {

      return is_null();

   }


   inline operator int() const
   {
      
      return is_set() ? 1 : 0;

   }


   inline pointer(const T * p);

   inline pointer(const void * p) : pointer(move_transfer, (T * ) p) {}

//   inline pointer(const thread_parameter & parameter): pointer(move_transfer, parameter.cast < T >()) {}

   template < class T2 >
   inline pointer(const pointer < T2 > & t) :
      m_p(nullptr)
   {

      operator = (dynamic_cast < T * >(t.m_p));

   }


   template < class T2 >
   inline pointer(pointer < T2 > && t)
   {

      if(::is_set(t.m_p))
      {

         m_p = dynamic_cast < T * >(t.m_p);

         if(::is_set(m_p))
         {

            t.m_p = nullptr;

         }

      }
      else
      {

         m_p = nullptr;

      }

   }


   inline ~pointer();


   inline T * operator ->();
   inline T * operator ->() const ;
   inline T & operator *();
   inline T & operator *() const ;
   inline operator T * ();
   inline operator T * const () const;
   inline T * get_();
   inline const T * get_() const;

   inline bool is_null() const;
   inline bool is_set() const;

   inline pointer & operator = (const pointer & t);
   inline pointer & operator = (pointer && t);
   inline pointer & operator = (const lparam& lparam);


   template < class T2 >
   inline pointer & operator = (T2 * p)
   {
      return operator = (dynamic_cast < T * > (p));
   }


   inline pointer & operator = (T * p)
   {

      return reset(p);

   }


   template < class T2 >
   inline pointer & operator = (const pointer < T2 > & t)
   {

      return operator = (dynamic_cast < T * > (t.m_p));

   }


   template < class T2 >
   inline pointer & operator = (pointer < T2 > && t)
   {

      if (*this != t)
      {

         auto pOld = m_p;

         if (::is_set(t.m_p))
         {

            m_p = dynamic_cast <T *>(t.m_p);

            if (::is_set(m_p))
            {

               t.m_p = nullptr;

            }

         }
         else
         {

            m_p = nullptr;

         }

         ::release(pOld);

      }

      return *this;

   }


   inline i64 release();

   inline __pointer(T) detach();


   template < class T2 >
   inline __pointer(T2) cast()
   {

      return m_p;

   }


   template < class T2 >
   inline __pointer(T2) cast() const
   {

      return m_p;

   }


   template < class T2 >
   inline bool is() const
   {

      return cast < T2 > ().is_set();

   }


   template < typename CONTAINER, typename OBJECT, typename ATTRIBUTE >
   pointer & merge(const CONTAINER & pcontainer, const OBJECT & pobject, const ATTRIBUTE& attribute)
   {

      auto pModified = __new(TYPE(*m_p));

      pModified->apply(pobject, attribute);

      return operator =(pcontainer->get_existing(pModified));

   }

   template < typename OBJECT, typename ATTRIBUTE >
   pointer& container_merge(const OBJECT& pobject, const ATTRIBUTE& attribute)
   {

      return merge(m_p->m_pcontainer, pobject, attribute);

   }

   inline pointer & reset(T * p);

   inline bool operator ==(std::nullptr_t) const { return is_null(); }

   inline bool operator !=(std::nullptr_t) const { return is_set(); }

   template < typename T2 >
   inline bool operator ==(const T2 * p) const { return m_p == p; }

   template < typename T2 >
   inline bool operator !=(const T2 * p) const { return m_p != p; }

   inline bool operator ==(const T * p) const { return m_p == p; }
   inline bool operator !=(const T * p) const { return m_p != p; }

   template < typename OBJECT >
   inline __pointer(T) & alloc(OBJECT * pobject);

   template < typename OBJECT >
   inline __pointer(T) & defer_alloc(OBJECT * pobject);

   inline __pointer(T) & clone(::matter * pobject);

   inline void run_and_release()
   {

      if (is_null())
      {

         return;

      }

      m_p->run();

      release();

   }

};


// It must not free memory directly allocated to matter pointed by 'p'.
// It is recommended to let final deletion and destruction happens at normal destructor.
// 'destruct' semantics gives a class the ability to use the scoped guard_pointer
// to release outer references (from operating system for example) that would prevent
// the matter to be deleted/destroyed when the matter is released by a conventional pointer.
//
template < class T >
inline void destruct(T * p)
{

   try
   {

      p->destruct();

   }
   catch(...)
   {

   }

}


// destroy solves this.

template < class T >
class guard_pointer :
   public ::pointer < T >
{
public:
   guard_pointer() {}
   guard_pointer(const lparam& lparam) : ::pointer<T>(lparam) {}

   guard_pointer(const pointer < T > & t): ::pointer< T>(t) {}
   guard_pointer(guard_pointer < T > && t): ::pointer<T>(::move(t)) {}
   guard_pointer(const allocer & allocer): ::pointer<T>(allocer) {}
   template < class T2 >
   guard_pointer(T2 * p) : ::pointer <T>(p) {}
   guard_pointer(T * p) : ::pointer <T>(p) {}

   template < class T2 >
   guard_pointer(const T2 * p): ::pointer <T>(p) {}

   template < class T2 >
   guard_pointer(const pointer < T2 > & t): ::pointer <T>(t) {}


   template < class T2 >
   guard_pointer(guard_pointer < T2 > && t) :
      ::pointer <T>(::move(t)) {}

   ~guard_pointer()
   {

      if(::is_set(this->m_p))
      {

         ::destruct(this->m_p);

      }

      this->release();

   }


};


namespace papaya
{


   template < typename T>
   __pointer(T) & defer_new(__pointer(T) & t, ::matter * p)
   {

      if (t.is_null())
      {

         T * ptype = new T(p);

         ptype->m_countReference--;

         t = ptype;



      }

      return t;
   }

} // namespace papaya





template < typename T >
inline __pointer(T) move_transfer(T * p) { return ::pointer < T >(e_move_transfer, p); }


//#define __new(...) __new(__VA_ARGS__)


// template < typename TYPE >
// inline auto __alloc(__pointer(TYPE)& t)
// {
//    return t.operator=(__new(TYPE));
// }

// template < typename TYPE >
// inline auto __alloc(__pointer(TYPE)& t, ::matter* pobject)
// {
//    return t.operator=(__new(TYPE(pobject)));
// }
