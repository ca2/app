#pragma once


////#include "acme/prototype/collection/numeric_array.h"


template < class ENUM >
class flags :
   virtual public ::particle
{
public:


   long_long_array m_ia;


   flags();
   flags(ENUM eenum);
   flags(const ::std::initializer_list < ENUM >& evaluelist);
   flags(const flags & f);
   ~flags() override;


   bool add(ENUM eenum);
   bool erase(ENUM eenum);
   bool has(ENUM eenum) const;
   bool set(ENUM eenum, bool bSet);
   int add(flags < ENUM > & f);
   bool clear();
   bool toggle(ENUM eenum);


   flags operator & (ENUM eenum) const
   {
      if (has(eenum))
      {
         return flags(eenum);
      }
      else
      {
         return flags();
      }
   }


   flags operator | (ENUM eenum) const
   {
      flags flags(*this);
      flags.add(eenum);
      return flags;
   }
   flags < ENUM > & operator = (const flags < ENUM >  & f);
   bool operator == (const flags < ENUM >  & f);
   bool operator != (const flags < ENUM >  & f);
   bool operator == (const ENUM e) { return ::is_set(this) && m_ia.get_size() == 1 && (ENUM) m_ia.element_at(0) == e; }

   flags < ENUM > & operator |= (ENUM eenum)
   {
      add(eenum);
      return *this;
   }
   flags < ENUM > & operator -= (ENUM eenum)
   {
      erase(eenum);
      return *this;
   }
   flags < ENUM > & operator |= (const flags < ENUM > & f)
   {
      if (this != &f)
      {
         add(f);
      }
      return *this;
   }

   operator bool()
   {
      return ::is_set(this) && m_ia.has_elements();
   }


   //void io(::stream & stream)
   //{

   //   __io_array(stream, m_ia);

   //}


};


template < class ENUM >
flags < ENUM > ::flags()
{
}

template < class ENUM >
flags < ENUM > ::flags(ENUM eenum)
{
   add(eenum);
}

template < class ENUM >
flags < ENUM > ::flags(const ::std::initializer_list < ENUM >& evaluelist)
{

   for (auto& evalue : evaluelist)
   {

      add(evalue);

   }

}

template < class ENUM >
flags < ENUM > ::flags(const flags < ENUM > & f)
{
   operator = (f);
}

template < class ENUM >
flags < ENUM > ::~flags()
{
}

template < class ENUM >
bool flags < ENUM > ::add(ENUM eenum)
{
   return m_ia.add_unique((long long)eenum);
}


template < class ENUM >
bool flags < ENUM > ::erase(ENUM eenum)
{
   return m_ia.erase((long long)eenum);
}


template < class ENUM >
bool flags < ENUM > ::has(ENUM eenum) const
{
   return ::is_set(this) && m_ia.has((long long)eenum);
}


template < class ENUM >
bool flags < ENUM > ::set(ENUM eenum, bool bSet)
{
   if (bSet)
   {
      return add(eenum);
   }
   else
   {
      return erase(eenum);
   }
}

template < class ENUM >
int flags < ENUM > ::add(flags < ENUM > & f)
{
   int iCount = 0;
   for (int i = 0; i < f.m_ia.get_size(); i++)
   {
      if (add((ENUM)f.m_ia[i]))
         iCount++;
   }
   return iCount;
}

template < class ENUM >
bool flags < ENUM > ::toggle(ENUM eenum)
{
   ASSERT(((int)eenum) < 128);
   if (has(eenum))
   {
      return erase(eenum);
   }
   else
   {
      return add(eenum);
   }
}

template < class ENUM >
bool flags < ENUM > ::clear()
{
   m_ia.erase_all();
   return true;
}

template < class ENUM >
flags < ENUM > & flags < ENUM > ::operator = (const flags < ENUM > & f)
{
   m_ia.copy(f.m_ia);
   return *this;
}

template < class ENUM >
bool flags < ENUM > ::operator == (const flags < ENUM > & f)
{
   return ::is_set(this) && ::acme::array::is_equal(m_ia, f.m_ia);
}

template < class ENUM >
bool flags < ENUM > ::operator != (const flags < ENUM > & f)
{
   return !this->operator == (f);
}

template < class ENUM >
class flags_ex;

template < class ENUM >
class flags_listener
{
   friend class flags_ex < ENUM >;
protected:
   virtual void on_change_signalization(ENUM eenum);
   void on_change_signalization(int iEnum);
};

template < class ENUM >
void flags_listener < ENUM > ::on_change_signalization(ENUM)
{
}

template < class ENUM >
void flags_listener < ENUM > ::on_change_signalization(int iEnum)
{
   on_change_signalization((ENUM)iEnum);
}


//template < class ENUM >
//class flags_ex :
//   virtual public flags < ENUM >
//{
//public:
//
//
//   flags_ex();
//   flags_ex(flags_ex & flags);
//   virtual ~flags_ex();
//
//   using ::flags < ENUM >::add;
//   virtual bool add(ENUM eenum);
//   virtual bool erase(ENUM eenum);
//   virtual bool clear();
//   virtual bool toggle(ENUM eenum);
//
//   virtual void on_change_signalization(ENUM eenum);
//
//protected:
//
//   class ::channel        m_signal;
//
//};
//
//template < class ENUM >
//flags_ex < ENUM > ::flags_ex()
//{
//}
//
//template < class ENUM >
//flags_ex < ENUM > ::flags_ex(flags_ex < ENUM > & f)
//{
//   operator = (f);
//}
//
//template < class ENUM >
//flags_ex < ENUM > ::~flags_ex()
//{
//}
//
//template < class ENUM >
//bool flags_ex < ENUM > ::add(ENUM eenum)
//{
//   if (flags<ENUM>::add(eenum))
//   {
//      on_change_signalization(eenum);
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//}
//
//template < class ENUM >
//bool flags_ex < ENUM > ::erase(ENUM eenum)
//{
//   if (flags<ENUM>::erase(eenum))
//   {
//      on_change_signalization(eenum);
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//}
//
//template < class ENUM >
//bool flags_ex < ENUM > ::toggle(ENUM eenum)
//{
//   if (flags<ENUM>::toggle(eenum))
//   {
//      on_change_signalization(eenum);
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//}
//
//template < class ENUM >
//bool flags_ex < ENUM > ::clear()
//{
//   return flags<ENUM>::clear();
//}
//
////class flag_change_signalization :
////   public ::message::message
////{
////public:
////
////   int m_iEnum;
////
////
////   flag_change_signalization()
////   {
////   }
////
////
////};
////
////template < class ENUM >
////void flags_ex < ENUM > ::on_change_signalization(ENUM eenum)
////{
////
////   flag_change_signalization obj;
////
////   obj.m_iEnum = (int)eenum;
////
////   m_signal.route_message(&obj);
////
////}
////
////
////
