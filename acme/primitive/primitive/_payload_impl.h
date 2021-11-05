#pragma once



inline payload::payload()
{

   m_etype = e_type_new;
   //clear_data();

}


inline payload::payload(enum_type etype)
{

   m_etype = e_type_null;

   set_type(etype, false);
   //clear_data();

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
   case e_type_i32_array:
      return ::is_null(m_pia) ? 0 : m_pia->get_count();
   case e_type_string_array:
      return ::is_null(m_pstra) ? 0 : m_pstra->get_count();
   case e_type_payload_array:
      return ::is_null(m_ppayloada) ? 0 : m_ppayloada->get_count();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) ? 0 : m_ppropertyset->get_count();
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

   if (m_etype == e_type_string_array
      || m_etype == e_type_i32_array
      || m_etype == e_type_payload_array
      || m_etype == e_type_property_set)
   {
      return true;
   }
   else if (m_etype == e_type_property)
   {
      return this->property().is_array();
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

   return str == payload.string();

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
      return operator = (payload.string());
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

   if (m_etype == ::e_type_i32_array)
   {

      if (payload2.m_etype == ::e_type_i32_array)
      {

         payload = ia() - payload2.ia();

      }
      else
      {

         payload = *this;

         payload.ia().erase(payload2.i32());

      }

   }
   else if (m_etype == ::e_type_string_array)
   {

      if (payload2.m_etype == ::e_type_string_array)
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

         payload.stra().erase(payload2.string());

      }

   }
   else if (m_etype == ::e_type_payload_array)
   {
      if (payload2.m_etype == ::e_type_payload_array)
      {
         payload = payloada() - payload2.payloada();
      }
      else
      {
         payload = *this;
         payload.payloada().erase(payload2);
      }
   }
   else if (is_double() || payload2.is_double())
   {
      payload = f64() - payload2.f64();
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
      payload = atoi(string()) - atoi(payload2.string());
   }
   return payload;
}

template < payload_class PAYLOAD >
inline ::payload payload::operator + (const PAYLOAD & payload2) const
{

   ::payload payload;

   if (m_etype == ::e_type_i32_array || m_etype == ::e_type_i32_array)
   {

      if (m_etype == ::e_type_i32_array)
      {

         if (payload2.m_etype == ::e_type_i32_array)
         {

            payload = ia() + payload2.ia();

         }
         else
         {

            payload = *this;

            payload.ia().add(payload2.i32());

         }

      }
      else
      {

         payload = payload2;

         payload.ia().add(i32());

      }

   }
   else if (m_etype == ::e_type_string_array || payload2.m_etype == ::e_type_string_array)
   {

      if (m_etype == ::e_type_string_array)
      {

         if (payload2.m_etype == ::e_type_string_array)
         {

            payload = stra() + payload2.stra();

         }
         else
         {

            payload = *this;

            payload.stra().add(payload2.string());

         }

      }
      else
      {

         payload = payload2;

         payload.stra().add(string());

      }

   }
   else if (m_etype == ::e_type_payload_array || payload2.m_etype == ::e_type_payload_array)
   {

      if (payload2.m_etype == ::e_type_payload_array)
      {

         if (payload2.m_etype == ::e_type_payload_array)
         {

            payload = payloada() + payload2.payloada();

         }
         else
         {

            payload = *this;

            payload.payloada().add(payload2);

         }

      }
      else
      {

         payload = payload2;

         payload.payloada().add(*this);

      }

   }
   else if ((is_double() && payload2.is_number()) || (is_number() && payload2.is_double()))
   {

      payload = f64() + payload2.f64();

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

      payload = string() + payload2.string();

   }

   return payload;

}





template < payload_class PAYLOAD >
inline ::payload payload::operator / (const PAYLOAD & payload2) const
{

   ::payload payload;

   if (m_etype == ::e_type_i32_array)
   {
      if (payload2.m_etype == ::e_type_i32_array)
      {
         payload = *this;
         payload.ia().intersect(payload2.ia());
      }
      else
      {
         payload = *this;
         payload.ia().divide(payload2.i32());
      }
   }
   else if (m_etype == ::e_type_string_array)
   {
      if (payload2.m_etype == ::e_type_string_array)
      {
         //payload = stra().intersect(payload2.stra());
      }
      else
      {
         payload = *this;
         payload.stra().erase(payload2.string());
      }
   }
   else if (m_etype == ::e_type_payload_array)
   {
      if (payload2.m_etype == ::e_type_payload_array)
      {
         //payload = payloada() / payload2.payloada();
      }
      else
      {
         payload = *this;
         payload.payloada().erase(payload2);
      }
   }
   else if (is_double() || payload2.is_double())
   {
      payload = f64() / payload2.f64();
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
      payload = atoi(string()) / atoi(payload2.string());
   }
   return payload;
}



template < payload_class PAYLOAD >
inline ::payload payload:: operator * (const PAYLOAD & payload2) const
{

   ::payload payload;

   if (m_etype == ::e_type_i32_array || m_etype == ::e_type_i32_array)
   {

      ::papaya::array::intersection(payload.ia(), ia(), payload2.ia());

   }
   else if (m_etype == ::e_type_string_array || payload2.m_etype == ::e_type_string_array)
   {

      ::papaya::array::intersection(payload.stra(), stra(), payload2.stra());

   }
   else if (m_etype == ::e_type_payload_array || payload2.m_etype == ::e_type_payload_array)
   {

      ::papaya::array::intersection(payload.payloada(), payloada(), payload2.payloada());

   }
   else if (is_double() || payload2.is_double())
   {

      payload = f64() * payload2.f64();

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

      payload = get_string().intersection(payload2.to_string());

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

inline bool strictly_equal(const ::string & str, const class ::payload & payload)
{
   return payload.m_etype == ::e_type_string && str == payload.m_str;
}

inline bool strictly_equal(double d, const class ::payload & payload)
{
   return payload.m_etype == ::e_type_f64 && d == payload.m_f64;
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

inline bool strictly_different(const ::string & str, const class ::payload & payload)
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


inline payload::operator bool() const { return this->get_bool(); }

inline payload::operator ::i8() const { return this->i8(); }
inline payload::operator ::u8() const { return this->u8(); }
inline payload::operator ::i16() const { return this->i16(); }
inline payload::operator ::u16() const { return this->u16(); }
inline payload::operator ::i32() const { return this->i32(); }
inline payload::operator ::u32() const { return this->u32(); }
inline payload::operator ::i64() const { return this->i64(); }
inline payload::operator ::u64() const { return this->u64(); }
inline payload::operator ::f32() const { return this->f32(); }
inline payload::operator ::f64() const { return this->f64(); }


inline payload::operator ::string() const
{

   return this->string();

}



