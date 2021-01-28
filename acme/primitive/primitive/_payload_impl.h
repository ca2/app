#pragma once



inline payload::payload()
{

   m_etype = e_type_new;
   clear_data();

}


inline payload::payload(enum_type etype)
{

   m_etype = etype;
   clear_data();

}


//inline payload::payload(const ::e_status & estatus)
//{
//
//   set_type(type_enum_status);
//
//   m_estatus = estatus;
//
//}


//inline payload::payload(enum_command ecommand)
//{
//
//   set_type(type_enum_command);
//
//   m_ecommand = ecommand;
//
//}


//inline payload::payload(enum_check echeck)
//{
//
//   set_type(type_enum_check);
//
//   m_echeck = echeck;
//
//}


inline payload::payload(std::nullptr_t)
{

   m_etype = e_type_null;

}


inline ::count payload::get_count() const
{
   switch (m_etype)
   {
   case e_type_bool:
      return 1;
   case e_type_inta:
      return ::is_null(m_pia) ? 0 : m_pia->get_count();
   case e_type_stra:
      return ::is_null(m_pstra) ? 0 : m_pstra->get_count();
   case type_vara:
      return ::is_null(m_pvara) ? 0 : m_pvara->get_count();
   case e_type_propset:
      return ::is_null(m_pset) ? 0 : m_pset->get_count();
   case e_type_empty:
   case e_type_null:
   case e_type_new:
   case e_type_empty_argument:
      return 0;
   default:
      return 1;
   }
}


inline ::count payload::array_get_count() const
{
   if (m_etype == e_type_new
      || m_etype == e_type_null
      || m_etype == e_type_empty
      || m_etype == e_type_empty_argument)
   {
      return -1; // indicates that this ::payload is not an array
   }
   else if (is_array())
      return this->get_count();
   else
      return 1; // this ::payload is an scalar or object that can be retrieved through "array_" methods
}



inline index payload::array_get_upper_bound() const
{
   if (m_etype == e_type_new
      || m_etype == e_type_null
      || m_etype == e_type_empty
      || m_etype == e_type_empty_argument)
   {
      return -1; // indicates that this ::payload is not an array
   }
   else if (is_array())
      return this->get_count() - 1;
   else
      return 0; // this ::payload is an scalar or object that can be retrieved through "array_" methods
}


inline bool payload::is_array() const
{

   if (m_etype == e_type_stra
      || m_etype == e_type_inta
      || m_etype == type_vara
      || m_etype == e_type_propset)
   {
      return true;
   }
   else if (m_etype == type_prop)
   {
      return prop().is_array();
   }
   else if (m_etype == e_type_element)
   {
      return false;
   }
   else
   {
      return false;
   }
}



inline bool operator == (const string& str, const ::payload & payload)
{

   return str == payload.get_string();

}



inline id& id::operator = (const ::payload & payload)
{

   if (payload.is_null())
   {
      m_all = {};
      return *this;
   }
   else if (payload.is_empty())
   {
      return operator =("");
   }
   else if (payload.is_integer())
   {
      return operator = (payload.iptr());
   }
   else
   {
      return operator = (payload.get_string());
   }

}

inline id& id::operator = (const property& prop)
{

   return operator = ((const ::payload&)prop);

}



inline id::id(const ::payload & payload)
{
   m_all = {};
   operator = (payload);

}



template < payload_class PAYLOAD >
inline ::payload payload::operator - (const PAYLOAD & payload2) const
{

   ::payload payload;

   if (m_etype == ::e_type_inta)
   {
      if (payload2.m_etype == ::e_type_inta)
      {
         payload = inta() - payload2.inta();
      }
      else
      {
         payload = *this;
         payload.inta().remove(payload2.i32());
      }
   }
   else if (m_etype == ::e_type_stra)
   {
      if (payload2.m_etype == ::e_type_stra)
      {
         payload = stra() - payload2.stra();
      }
      else if (payload2.is_array())
      {
         payload = stra() - payload2.stra();
      }
      else
      {
         payload = *this;
         payload.stra().remove(payload2.get_string());
      }
   }
   else if (m_etype == ::type_vara)
   {
      if (payload2.m_etype == ::type_vara)
      {
         payload = vara() - payload2.vara();
      }
      else
      {
         payload = *this;
         payload.vara().remove(payload2);
      }
   }
   else if (is_double() || payload2.is_double())
   {
      payload = get_double() - payload2.get_double();
   }
   else if (is_integer() || payload2.is_integer())
   {
      payload = i32() - payload2.i32();
   }
   else if (is_natural() || payload2.is_natural())
   {
      payload = u32() - payload2.u32();
   }
   else
   {
      payload = atoi(get_string()) - atoi(payload2.get_string());
   }
   return payload;
}

template < payload_class PAYLOAD >
inline ::payload payload::operator + (const PAYLOAD & payload2) const
{

   ::payload payload;

   if (m_etype == ::e_type_inta || m_etype == ::e_type_inta)
   {
      if (m_etype == ::e_type_inta)
      {
         if (payload2.m_etype == ::e_type_inta)
         {
            payload = inta() + payload2.inta();
         }
         else
         {
            payload = *this;
            payload.inta().add(payload2.i32());
         }
      }
      else
      {
         payload = payload2;
         payload.inta().add(i32());
      }
   }
   else if (m_etype == ::e_type_stra || payload2.m_etype == ::e_type_stra)
   {

      if (m_etype == ::e_type_stra)
      {

         if (payload2.m_etype == ::e_type_stra)
         {

            payload = stra() + payload2.stra();

         }
         else
         {

            payload = *this;

            payload.stra().add(payload2.get_string());

         }

      }
      else
      {

         payload = payload2;

         payload.stra().add(get_string());

      }

   }
   else if (m_etype == ::type_vara || payload2.m_etype == ::type_vara)
   {

      if (payload2.m_etype == ::type_vara)
      {

         if (payload2.m_etype == ::type_vara)
         {

            payload = vara() + payload2.vara();

         }
         else
         {

            payload = *this;

            payload.vara().add(payload2);

         }

      }
      else
      {

         payload = payload2;

         payload.vara().add(*this);

      }

   }
   else if ((is_double() && payload2.is_number()) || (is_number() && payload2.is_double()))
   {

      payload = get_double() + payload2.get_double();

   }
   else if (is_integer() && payload2.is_integer())
   {

      payload = i32() + payload2.i32();

   }
   else if (is_natural() && payload2.is_natural())
   {

      payload = u32() + payload2.u32();

   }
   else
   {

      payload = get_string() + payload2.get_string();

   }

   return payload;

}





template < payload_class PAYLOAD >
inline ::payload payload::operator / (const PAYLOAD & payload2) const
{

   ::payload payload;

   if (m_etype == ::e_type_inta)
   {
      if (payload2.m_etype == ::e_type_inta)
      {
         payload = *this;
         payload.inta().intersect(payload2.inta());
      }
      else
      {
         payload = *this;
         payload.inta().divide(payload2.i32());
      }
   }
   else if (m_etype == ::e_type_stra)
   {
      if (payload2.m_etype == ::e_type_stra)
      {
         //payload = stra().intersect(payload2.stra());
      }
      else
      {
         payload = *this;
         payload.stra().remove(payload2.get_string());
      }
   }
   else if (m_etype == ::type_vara)
   {
      if (payload2.m_etype == ::type_vara)
      {
         //payload = vara() / payload2.vara();
      }
      else
      {
         payload = *this;
         payload.vara().remove(payload2);
      }
   }
   else if (is_double() || payload2.is_double())
   {
      payload = get_double() / payload2.get_double();
   }
   else if (is_integer() || payload2.is_integer())
   {
      payload = i32() / payload2.i32();
   }
   else if (is_natural() || payload2.is_natural())
   {
      payload = u32() / payload2.u32();
   }
   else
   {
      payload = atoi(get_string()) / atoi(payload2.get_string());
   }
   return payload;
}



template < payload_class PAYLOAD >
inline ::payload payload:: operator * (const PAYLOAD & payload2) const
{

   ::payload payload;

   if (m_etype == ::e_type_inta || m_etype == ::e_type_inta)
   {

      ::papaya::array::intersection(payload.inta(), inta(), payload2.inta());

   }
   else if (m_etype == ::e_type_stra || payload2.m_etype == ::e_type_stra)
   {

      ::papaya::array::intersection(payload.stra(), stra(), payload2.stra());

   }
   else if (m_etype == ::type_vara || payload2.m_etype == ::type_vara)
   {

      ::papaya::array::intersection(payload.vara(), vara(), payload2.vara());

   }
   else if (is_double() || payload2.is_double())
   {

      payload = get_double() * payload2.get_double();

   }
   else if (is_integer() || payload2.is_integer())
   {

      payload = i32() * payload2.i32();

   }
   else if (is_natural() || payload2.is_natural())
   {

      payload = u32() * payload2.u32();

   }
   else
   {

      payload = to_string().intersection(payload2.to_string());

   }

   return payload;

}








template < payload_class PAYLOAD >
inline ::payload & payload:: operator -= (const PAYLOAD & payload) 
{

   *this = *this - payload;

   return *this;

}


template < payload_class PAYLOAD >
inline ::payload & payload:: operator += (const PAYLOAD & payload)
{

   *this = *this + payload;

   return *this;

}


template < payload_class PAYLOAD >
inline ::payload & payload:: operator /= (const PAYLOAD & payload)
{

   *this = *this / payload;

   return *this;

}


template < payload_class PAYLOAD >
inline ::payload & payload:: operator *= (const PAYLOAD & payload)
{

   *this = *this * payload;

   return *this;

}








inline bool strictly_equal(const char * psz, const class ::payload & payload)
{
   return payload.m_etype == ::e_type_string && psz == payload.m_str;
}

inline bool strictly_equal(const string & str, const class ::payload & payload)
{
   return payload.m_etype == ::e_type_string && str == payload.m_str;
}

inline bool strictly_equal(double d, const class ::payload & payload)
{
   return payload.m_etype == ::e_type_double && d == payload.m_d;
}

inline bool strictly_equal(::i32 i, const class ::payload & payload)
{
   return payload.m_etype == ::e_type_i32 && i == payload.m_i32;
}

inline bool strictly_equal(bool b, const class ::payload & payload)
{
   return payload.m_etype == ::e_type_bool && is_equivalent(b, payload.m_b);
}

inline bool strictly_different(const char * psz, const class ::payload & payload)
{
   return !strictly_equal(psz, payload);
}

inline bool strictly_different(const string & str, const class ::payload & payload)
{
   return !strictly_equal(str, payload);
}

inline bool strictly_different(double d, const class ::payload & payload)
{
   return !strictly_equal(d, payload);
}

inline bool strictly_different(::i32 i, const class ::payload & payload)
{
   return !strictly_equal(i, payload);
}

inline bool strictly_different(bool b, const class ::payload & payload)
{
   return !strictly_equal(b, payload);
}
