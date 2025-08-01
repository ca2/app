#include "framework.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/prototype/string/str.h"


payload_array::payload_array()
{

}


payload_array::payload_array(const std::initializer_list < ::payload > & varlist)
{

   for (auto & payload : varlist)
   {

      add(payload);

   }

}

payload_array::payload_array(const string_array & stra)
{
   operator = (stra);
}

payload_array::payload_array(const ::int_array & ia)
{
   operator = (ia);
}

payload_array::payload_array(const ::property_set & propset)
{
   operator = (propset);
}

payload_array::payload_array(const payload_array & payloada) :
BASE_ARRAY(payloada)
{
}

payload_array::payload_array(payload_array && payloada) :
BASE_ARRAY(::transfer(payloada))
{

}

payload_array::~payload_array()
{

}


::collection::index payload_array::add(const ::payload & payload)
{

   //if(payload.is_empty())
   //{

   //   return -1;

   //}

   return BASE_ARRAY::add(payload);

}


::collection::count payload_array::append(const payload_array & payloada)
{

   for(int i = 0; i < payloada.get_size(); i++)
   {

      add(payloada[i]);

   }

   return this->get_count();

}


::collection::index payload_array::append(const std::initializer_list < ::payload > & list)
{

   ::collection::index i = -1;

   for(auto & payload : list)
   {

      auto iItem = add(payload);

      if(i < 0) i = iItem;

   }

   return i;

}



::collection::count payload_array::append_unique(const payload_array & payloada)
{

   ::collection::count c = 0;

   for(int i = 0; i < payloada.get_size(); i++)
   {

      if(!contains(payloada[i]))
      {

         add(payloada[i]);

         c++;

      }

   }

   return c;

}


string payload_array::implode(const ::scoped_string & scopedstrGlue) const
{

   string str;

   for(int i = 0; i < this->get_count(); i++)
   {

      if (i > 0)
      {

         str += scopedstrGlue;

      }

      str += this->element_at(i);

   }

   return str;

}


::collection::index payload_array::find_first(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last) const
{

   if (find < 0)
   {

      find += this->get_count();

   }

   if (last < 0)
   {

      last += this->get_count();

   }

   for(; find < this->get_count(); find++)
   {

      if (this->element_at(find) == scopedstr)
      {

         return find;

      }

   }

   return -1;

}


::collection::index payload_array::case_insensitive_find_first(const ::scoped_string & scopedstr, ::collection::index find,::collection::index last) const
{
   
   if (find < 0)
   {

      find += this->get_count();

   }
   
   if (last < 0)
   {

      last += this->get_count();

   }

   for(; find < this->get_count(); find++)
   {

      if (this->element_at(find).case_insensitive_equals(scopedstr))
      {

         return find;

      }

   }

   return -1;

}


::collection::index payload_array::find_first(const ::payload & payload, ::collection::index find, ::collection::index last) const
{

   if (find < 0)
   {

      find += this->get_count();

   }

   if (last < 0)
   {

      last += this->get_count();

   }

   for (; find < this->get_count(); find++)
   {

      if (this->element_at(find) == payload)
      {

         return find;
      }

   }

   return -1;

}


bool payload_array::case_insensitive_contains(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax) const
{

   ::collection::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = case_insensitive_find_first(scopedstr, find, last)) >= 0)

      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


bool payload_array::contains(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax) const
{

   ::collection::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(scopedstr, find, last)) >= 0)
      count++;

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


bool payload_array::contains(const ::payload & payload, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax) const
{

   ::collection::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(payload, find, last)) >= 0)
      count++;

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


::collection::count payload_array::case_insensitive_erase_first(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last)
{

   if ((find = case_insensitive_find_first(scopedstr, find, last)) >= 0)
   {

      erase_at(find);

   }

   return find;

}


::collection::count payload_array::erase_first(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last)
{

   if ((find = find_first(scopedstr, find, last)) >= 0)
   {

      erase_at(find);

   }

   return find;

}


::collection::count payload_array::erase_first(const ::payload & payload, ::collection::index find, ::collection::index last)
{

   if ((find = find_first(payload, find, last)) >= 0)
   {

      erase_at(find);

   }

   return find;

}


::collection::count payload_array::case_insensitive_erase(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax)
{

   ::collection::count count = 0;

   if (case_insensitive_contains(scopedstr, find, last, countMin, countMax))
   {
    
      while (conditional(countMax >= 0, count < countMax)
         && (find = case_insensitive_erase_first(scopedstr, find, last)) >= 0)
      {

         count++;

      }

   }

   return count;

}


::collection::count payload_array::erase(const ::scoped_string & scopedstr, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax)
{

   ::collection::count count = 0;

   if (contains(scopedstr, find, last, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax)
         && (find = erase_first(scopedstr, find, last)) >= 0)
      {

         count++;

      }

   }

   return count;

}


::collection::count payload_array::erase(const ::payload & payload, ::collection::index find, ::collection::index last, ::collection::count countMin, ::collection::count countMax)
{
   
   ::collection::count count = 0;

   if (contains(payload, find, last, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax)
         && (find = erase_first(payload, find, last)) >= 0)
      {

         count++;

      }

   }

   return count;

}


::collection::count payload_array::erase(const payload_array & payloada)
{

   if(&payloada == this)
   {

      return erase_all();

   }

   ::collection::count count = 0;

   for(::collection::index i = 0; i < payloada.get_count(); i++)
   {

      count += erase(payloada[i]);

   }
   
   return count;

}


payload_array & payload_array::operator -=(const ::payload & payload)
{

   erase(payload);

   return *this;

}


payload_array & payload_array::operator -=(const payload_array & payloada)
{

   erase(payloada);

   return *this;

}


payload_array payload_array::operator -(const ::payload & payload) const
{

   payload_array payloada(*this);

   payloada.erase(payload);

   return payloada;

}


payload_array payload_array::operator -(const payload_array & payloadaParam) const
{

   payload_array payloada(*this);

   payloada.erase(payloadaParam);

   return payloada;

}


payload_array & payload_array::operator +=(const ::payload & payload)
{

   add(payload);

   return *this;

}


payload_array & payload_array::operator +=(const payload_array & payloada)
{
   append(payloada);
   return *this;
}

payload_array payload_array::operator +(const ::payload & payload) const
{
   payload_array payloada(*this);
   payloada.add(payload);
   return payloada;
}

payload_array payload_array::operator +(const payload_array & payloadaParam) const
{
   payload_array payloada(*this);
   payloada.append(payloadaParam);
   return payloada;
}

payload_array & payload_array::operator = (const string_array & stra)
{
   erase_all();
   for(int i = 0; i < stra.get_count(); i++)
   {
      add(stra[i]);
   }
   return *this;
}

payload_array & payload_array::operator = (const ::int_array & inta)
{
   erase_all();
   for(int i = 0; i < inta.get_count(); i++)
   {
      add(inta[i]);
   }
   return *this;
}


payload_array & payload_array::operator = (const ::property_set & propertyset)
{

   erase_all();

   ::collection::index i = 0;

   for(auto & pproperty : propertyset)
   {

      set_at(i++, *pproperty);

   }

   return *this;

}


payload_array & payload_array::operator = (const payload_array & payloada)
{
   if(this != &payloada)
   {
      erase_all();
      for(int i = 0; i < payloada.get_count(); i++)
      {
         add(payloada[i]);
      }
   }
   return *this;
}


//void payload_array::parse_network_payload(::const_ansi_range & range)
//{
//
//   parse_network_payload(range);
//
//}

int g_iRandomNumberGenerator = 0;


void payload_array::parse_network_payload(::ansi_range & range)
{

   if(range.is_empty())
   {

      return;

   }

   range.consume_spaces(0);

   range.consume("[");

   range.consume_spaces(0);

   if (*range.m_begin == ']')
   {

      range.m_begin++;

      return;

   }

   //::thread * pthread = nullptr;

   while(true)
   {

      
      //throw ::exception(todo("thread"));
     /* g_iRandomNumberGenerator++;

      if(pthread == nullptr)
      {

         if((g_iRandomNumberGenerator % 25) == 0)
         {

            pthread = ::get_task();

         }

      }
      else if(!pthread->task_get_run())
      {

         throw ::exception(::exit_exception(pthread));

      }*/

      ::payload & payload = add_new();

      payload.parse_network_payload(range);

      range.consume_spaces(0);

      if(*range.m_begin == ',')
      {

         range.m_begin++;

         continue;

      }
      else if(*range.m_begin == ']')
      {

         range.m_begin++;

         return;

      }
      else
      {

         string str = "not expected character : ";

         str += range.m_begin;

         throw_exception(error_parsing, str);

      }

   }

}


//void var_array_skip_network_payload(const_char_pointer &pszJson)
//{
//
//   var_array_skip_network_payload(scopedstrJson, pszJson + strlen(scopedstrJson) - 1);
//
//}


void payload_array_skip_network_payload(::ansi_range & range)
{
   
   range.consume_spaces(0);
   
   range.consume("[");

   while (true)
   {
      
      payload_skip_network_payload(range);
      
      range.consume_spaces(0);

      if (*range.m_begin == ',')
      {
         
         range.m_begin++;
         
         continue;

      }
      else if (*range.m_begin == ']')
      {
         
         range.m_begin++;
         
         return;

      }
      else
      {
         
         string str = "not expected character : ";
         
         str += range.m_begin;

         throw_exception(error_parsing, str);

      }

   }

}


string & payload_array::get_network_payload(string & str, bool bNewLine) const
{

   str +="[";

   if(get_count() > 0)
   {

      element_at(0).get_network_payload(str, bNewLine);

   }

   for (::collection::index i = 1; i < get_count(); i++)
   {

      if (bNewLine)
      {

         str += ", \r\n";

      }
      else
      {

         str += ", ";

      }

      element_at(i).get_network_payload(str, bNewLine);

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "]";

   return str;

}



std::strong_ordering payload_array::order(const ::payload_array & payloada) const
{

   auto iMinimumSize = minimum(this->size(), payloada.size());

   for (::collection::index i = 0; i < iMinimumSize; i++)
   {

      auto ordering = element_at(i).order_payload(payloada.element_at(i));

      if (ordering != 0)
      {

         return ordering;

      }

   }

   return this->size() <=> payloada.size();

}


std::strong_ordering payload_array::case_insensitive_order(const ::payload_array & payloada) const
{

   return stra().case_insensitive_order(payloada.stra());

}

