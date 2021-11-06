#pragma once


template < class T, class T_to_T = map < T, T, T, T > >
class biunique :
   virtual public ::matter
{
public:


   biunique();
   virtual ~biunique()
   {
   }

   bool has_a(T a) const;
   bool has_b(T b) const;


   T calc_max_a();
   T calc_max_b();


   T erase_a(T a);
   T erase_b(T b);

   T array_translate_a(T aNew, T aOld);

   T translate_a(T a1, T a2);
   T translate_b(T b1, T b2);


   T get_a(T b) const;
   T get_b(T a) const;
   void set(T a, T b);

   void __swap(T a1, T a2);

   T operator [](T a) const
   {
      return get_b(a);
   }

   T get_max_a() const;
   T get_max_b() const;

   void erase_all();

   void set_empty_a(T iEmpty);
   void set_empty_b(T iEmpty);

   T get_free_a() const;
   T get_free_b() const;

   T add(T b);
   T add_b_in_first_free_a(T b);
   T add_b_in_first_free_a_mod_w(T b, T w, T mod);
   T add_unique(T b);
   T get_size() const;

   void copy_data(const biunique & ia);

   //virtual ::stream & write(::stream & stream) const override;
//virtual ::stream & read(::stream & stream) override;

   biunique & operator = (const biunique & ia);

   void biunivoca(bool b = true);

   bool m_bBiunivoca;
   T m_iMaxA;
   T m_iMaxB;
   T m_iEmptyA;
   T m_iEmptyB;
   T_to_T m_ab;
   T_to_T m_ba;
};



template < class T, class T_to_T >
biunique < T, T_to_T > ::biunique()
{
   m_bBiunivoca = true;
   m_iEmptyA = -1;
   m_iEmptyB = -1;
   m_iMaxA = -1;
   m_iMaxB = -1;
}


template < class T, class T_to_T >
void biunique < T, T_to_T > ::biunivoca(bool b)
{
   m_bBiunivoca = b;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_a (T b) const
{
   T a;
   if(m_ba.lookup(b, a))
      return a;
   return m_iEmptyA;
}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_b (T a) const
{
   T b;
   if(m_ab.lookup(a, b))
      return b;
   return m_iEmptyB;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::erase_a(T a)
{
   if(has_a(a))
   {
      T b = get_b(a);
      m_ba.erase_key(b);
      m_ab.erase_key(a);
      m_iMaxA = calc_max_a();
      m_iMaxB = calc_max_b();
      return b;
   }
   return m_iEmptyB;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::array_translate_a(T aNew, T aOld)
{

   if (aOld < 0 || aNew < 0)
   {
      return m_iEmptyB;
   }

   T bParam = get_b(aOld);
   if (bParam == m_iEmptyB)
   {
      return m_iEmptyB;
   }

   if (aNew == aOld)
   {
      return bParam;
   }

   m_ba.erase_key(bParam);
   m_ab.erase_key(aOld);
   m_iMaxA = calc_max_a();
   m_iMaxB = calc_max_b();
   //if (aNew > aOld)
   //{
   //   T a = aOld;
   //   while (a + 1 <= m_iMaxA)
   //   {
   //      T b = get_b(a + 1);
   //      if (b == m_iEmptyB)
   //      {
   //         break;
   //      }
   //      m_ba.erase_key(b);
   //      m_ab.erase_key(a + 1);
   //      m_ba.set_at(b, a);
   //      m_ab.set_at(a, b);
   //      m_iMaxA = calc_max_a();
   //      m_iMaxB = calc_max_b();
   //      a++;
   //   }
   //}

   // making room
   if (has_a(aNew))
   {
      T a = aNew;
      T b;
      while (true)
      {
         a++;
         if (a > m_iMaxA)
         {
            break;
         }
         b = get_b(a);
         if (b == m_iEmptyB)
         {
            break;
         }
      }
      a--;
      while (a >= aNew)
      {
         b = get_b(a);
         if (b != m_iEmptyB)
         {
            m_ba.erase_key(b);
            m_ab.erase_key(a);
            m_ba.set_at(b, a + 1);
            m_ab.set_at(a + 1, b);
         }
         a--;
      }
   }

   // actually (in)se(r)tting
   m_ba.set_at(bParam, aNew);
   m_ab.set_at(aNew, bParam);

   m_iMaxA = calc_max_a();
   m_iMaxB = calc_max_b();

   return bParam;

}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::erase_b(T b)
{
   if(has_b(b))
   {
      T a = get_a(b);
      m_ab.erase_key(a);
      m_ba.erase_key(b);
      m_iMaxA = calc_max_a();
      m_iMaxB = calc_max_b();
      return a;
   }
   return m_iEmptyA;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::translate_a(T a1, T a2)
{
   T b = erase_a(a2);
   set(a1, b);
   return b;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::translate_b(T b1, T b2)
{
   T a = erase_b(b2);
   set(a, b1);
   return a;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::set(T a, T b)
{
   if(m_bBiunivoca)
   {
      if(has_a(a))
         erase_a(a);
      if(has_b(b))
         erase_b(b);
   }
   m_ab.set_at(a, b);
   m_ba.set_at(b, a);
   m_iMaxA = calc_max_a();
   m_iMaxB = calc_max_b();
}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_max_a() const
{
   return m_iMaxA;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_max_b() const
{
   return m_iMaxB;
}



template < class T, class T_to_T >
void biunique < T, T_to_T > ::erase_all()
{
   m_ab.erase_all();
   m_ba.erase_all();
   m_iMaxA = -1;
   m_iMaxB = -1;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::set_empty_a(T iEmpty)
{
   m_iEmptyA = iEmpty;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::set_empty_b(T iEmpty)
{
   m_iEmptyB = iEmpty;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::copy_data(const biunique & function)
{
   if(&function != this)
   {
      m_ab = function.m_ab;
      m_ba = function.m_ba;
   }
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::add(T b)
{
   T a = get_max_a() + 1;
   set(a, b);
   return a;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::add_b_in_first_free_a(T b)
{
   T a = get_free_a();
   set(a, b);
   return a;
}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::add_b_in_first_free_a_mod_w(T b, T w, T mod)
{
   if(mod <= 1)
      return add_b_in_first_free_a(b);
   if(w <= 0)
      return add_b_in_first_free_a(b);
   T ca = get_max_a() + 1;
   T a;
   for(a = 0; a < ca ; a++)
   {
      if((a % mod) >= w)
      {
         a = ((a / mod) + 1) * mod;
      }
      if(get_b(a) == m_iEmptyB)
      {
         set(a, b);
         return a;
      }
   }
   set(a, b);
   return a;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::add_unique(T b)
{
   T a;
   if(m_ba.lookup(b, a))
      return a;
   a = get_max_a() + 1;
   set(a, b);
   return a;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_size() const
{
   return get_max_a() + 1;
}

template < class T, class T_to_T >
void biunique < T, T_to_T > ::__swap(T a1, T a2)
{
   // because of Biunivoca
   T b1 = get_b(a1);
   T b2 = get_b(a2);
   set(a1, b2);
   set(a2, b1);

}

template < class T, class T_to_T >
bool biunique < T, T_to_T > ::has_a(T a) const
{
   T b;
   return m_ab.lookup(a, b) != false;
}


template < class T, class T_to_T >
bool biunique < T, T_to_T > ::has_b(T b) const
{
   T a;
   return m_ba.lookup(b, a) != false;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_free_a() const
{
   for(T a = 0; a <= m_iMaxA; a++)
   {
      if(!has_a(a))
         return a;
   }
   return m_iMaxA + 1;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::get_free_b() const
{
   for(T b = 0; b <= m_iMaxB; b++)
   {
      if(!has_b(b))
         return b;
   }
   return m_iMaxB + 1;
}

template < class T, class T_to_T >
biunique < T, T_to_T > & biunique < T, T_to_T > ::operator = (const biunique & ia)
{
   if(this != &ia)
   {
      m_bBiunivoca = ia.m_bBiunivoca;
      m_iMaxA = ia.m_iMaxA;
      m_iMaxB = ia.m_iMaxB;
      m_iEmptyA = ia.m_iEmptyA;
      m_iEmptyB = ia.m_iEmptyB;
      m_ab = ia.m_ab;
      m_ba = ia.m_ba;
   }
   return *this;
}


template < class t1, class t2, class t3, class t4 >
void serialize_write(stream & ostream, map < t1, t2, t3, t4 > & m)
{
   ::count count = m.get_count();
   typename map < t1, t2, t3, t4 >::assoc * passoc = m.get_start();
   ostream << count;
   while(passoc != nullptr)
   {
      ostream << passoc->element1();
      ostream << passoc->element2();
      passoc = m.get_next(passoc);
   }
}

template < class t1, class t2, class t3, class t4 >
void serialize_read(stream & istream, map < t1, t2, t3, t4 > & m)
{
   try
   {
      t1 iCount;
//      class map < t1, t2, t3, t4 >::assoc * passoc =
      //       m.get_start();
      istream >> iCount;
      t1 key;
      t3 value;
      m.erase_all();
      for(i32 i = 0; i < iCount; i++)
      {
         istream >> key;
         istream >> value;
         m.set_at(key, value);
      }
   }
   catch(const char * psz)
   {
      m.erase_all();
      throw ::exception(psz);
   }
}


template < class T, class T_to_T >
inline stream & operator << (stream & stream, const biunique < T, T_to_T > &biunique)
{

   stream << biunique.m_bBiunivoca;
   stream << biunique.m_iMaxA;
   stream << biunique.m_iMaxB;
   stream << biunique.m_iEmptyA;
   stream << biunique.m_iEmptyB;

   if (biunique.m_bBiunivoca)
   {
      stream << biunique.m_ab;
   }
   else
   {
      stream << biunique.m_ab;
      stream << biunique.m_ba;
   }

   return stream;

}


template < class T, class T_to_T >
inline stream & operator >> (stream & stream, biunique < T, T_to_T > & biunique)
{

   stream >> biunique.m_bBiunivoca;
   stream >> biunique.m_iMaxA;
   stream >> biunique.m_iMaxB;
   stream >> biunique.m_iEmptyA;
   stream >> biunique.m_iEmptyB;

   try
   {
      if (biunique.m_bBiunivoca)
      {
         T_to_T ab;
         stream >> ab;
         typename T_to_T::assoc * passoc = ab.get_start();
         while (passoc != nullptr)
         {
            biunique.set(passoc->element1(), passoc->element2());
            passoc = ab.get_next(passoc);
         }
      }
      else
      {
         stream >> biunique.m_ab;
         stream >> biunique.m_ba;
      }
   }
   catch (const char * psz)
   {
      biunique.m_ab.erase_all();
      biunique.m_ba.erase_all();
      biunique.m_bBiunivoca = true;
      biunique.m_iEmptyA = -1;
      biunique.m_iEmptyB = -1;
      biunique.m_iMaxA = -1;
      biunique.m_iMaxB = -1;
      throw ::exception(psz);
   }

   return stream;

}


template < class T, class T_to_T >
T biunique < T, T_to_T > ::calc_max_a()
{
   auto passoc = m_ab.get_start();
   T iMaxA = -1;
   while(passoc != nullptr)
   {
      if(passoc->element1() > iMaxA)
         iMaxA = passoc->element1();
      passoc = m_ab.get_next(passoc);
   }
   return iMaxA;
}

template < class T, class T_to_T >
T biunique < T, T_to_T > ::calc_max_b()
{
   auto passoc = m_ba.get_start();
   T iMaxB = -1;
   while(passoc != nullptr)
   {
      if(passoc->element1() > iMaxB)
         iMaxB = passoc->element1();
      passoc = m_ba.get_next(passoc);
   }
   return iMaxB;
}


class CLASS_DECL_ACME index_biunique :
   public biunique < index >
{
public:

   
   index_biunique();
   virtual ~index_biunique() {}


};


class CLASS_DECL_ACME int_biunique :
   public biunique < i32, int_to_int >
{
public:


   int_biunique();
   virtual ~int_biunique() {}


};


CLASS_DECL_ACME index array_translate_a(index_biunique & ia, index aNew, index aOld);



