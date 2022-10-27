#include "framework.h"
#include "acme/primitive/primitive/payload.h"


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

payload_array::payload_array(const int_array & ia)
{
   operator = (ia);
}

payload_array::payload_array(const property_set & propset)
{
   operator = (propset);
}

payload_array::payload_array(const payload_array & payloada)
{
   operator = (payloada);
}

payload_array::~payload_array()
{

}


index payload_array::add(const ::payload & payload)
{

   if(payload.is_empty())
   {

      return -1;

   }

   return BASE_ARRAY::add(payload);

}


::count payload_array::append(const payload_array & payloada)
{

   for(i32 i = 0; i < payloada.get_size(); i++)
   {

      add(payloada[i]);

   }

   return this->get_count();

}


index payload_array::append(const std::initializer_list < ::payload > & list)
{

   ::index i = -1;

   for(auto & payload : list)
   {

      auto iItem = add(payload);

      if(i < 0) i = iItem;

   }

   return i;

}



::count payload_array::append_unique(const payload_array & payloada)
{

   ::count c = 0;

   for(i32 i = 0; i < payloada.get_size(); i++)
   {

      if(!contains(payloada[i]))
      {

         add(payloada[i]);

         c++;

      }

   }

   return c;

}


string payload_array::implode(const char * pszGlue) const
{

   string str;

   for(i32 i = 0; i < this->get_count(); i++)
   {

      if (i > 0)
      {

         str += pszGlue;

      }

      str += this->element_at(i).string();

   }

   return str;

}


index payload_array::find_first(const char * psz, index find, index last) const
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

      if (this->element_at(find).string() == psz)
      {

         return find;

      }

   }

   return -1;

}


index payload_array::find_first_ci(const char * psz, index find, index last) const
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

      if (this->element_at(find).string().compare_ci(psz) == 0)
      {

         return find;

      }

   }

   return -1;

}


index payload_array::find_first(const ::payload & payload, index find, index last) const
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


bool payload_array::contains_ci(const char * pcsz, index find, index last, ::count countMin, ::count countMax) const
{

   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first_ci(pcsz, find, last)) >= 0)

      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


bool payload_array::contains(const char * pcsz, index find, index last, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(pcsz, find, last)) >= 0)
      count++;

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


bool payload_array::contains(const ::payload & payload, index find, index last, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(payload, find, last)) >= 0)
      count++;

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


::count payload_array::erase_first_ci(const char * pcsz, index find, index last)
{

   if ((find = find_first_ci(pcsz, find, last)) >= 0)
   {

      erase_at(find);

   }

   return find;

}


::count payload_array::erase_first(const char * pcsz, index find, index last)
{

   if ((find = find_first(pcsz, find, last)) >= 0)
   {

      erase_at(find);

   }

   return find;

}


::count payload_array::erase_first(const ::payload & payload, index find, index last)
{

   if ((find = find_first(payload, find, last)) >= 0)
   {

      erase_at(find);

   }

   return find;

}


::count payload_array::erase_ci(const char * pcsz, index find, index last, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if (contains_ci(pcsz, find, last, countMin, countMax))
   {
    
      while (conditional(countMax >= 0, count < countMax)
         && (find = erase_first_ci(pcsz, find, last)) >= 0)
      {

         count++;

      }

   }

   return count;

}


::count payload_array::erase(const char * pcsz, index find, index last, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if (contains(pcsz, find, last, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax)
         && (find = erase_first(pcsz, find, last)) >= 0)
      {

         count++;

      }

   }

   return count;

}


::count payload_array::erase(const ::payload & payload, index find, index last, ::count countMin, ::count countMax)
{
   
   ::count count = 0;

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


::count payload_array::erase(const payload_array & payloada)
{

   if(&payloada == this)
   {

      return erase_all();

   }

   ::count count = 0;

   for(index i = 0; i < payloada.get_count(); i++)
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
   add(payloada);
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
   payloada.add(payloadaParam);
   return payloada;
}

payload_array & payload_array::operator = (const string_array & stra)
{
   erase_all();
   for(i32 i = 0; i < stra.get_count(); i++)
   {
      add(stra[i]);
   }
   return *this;
}

payload_array & payload_array::operator = (const int_array & inta)
{
   erase_all();
   for(i32 i = 0; i < inta.get_count(); i++)
   {
      add(inta[i]);
   }
   return *this;
}


payload_array & payload_array::operator = (const property_set & propset)
{

   erase_all();

   index i = 0;

   for(auto & pproperty : propset)
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
      for(i32 i = 0; i < payloada.get_count(); i++)
      {
         add(payloada[i]);
      }
   }
   return *this;
}

void payload_array::parse_network_payload(const char * & pszJson)
{
   parse_network_payload(pszJson, pszJson + strlen(pszJson) - 1);
}

int g_iRandomNumberGenerator = 0;


void payload_array::parse_network_payload(const char * & pszJson, const char * pszEnd)
{

   if(pszJson > pszEnd)
   {

      return;

   }

   ::str().consume_spaces(pszJson, 0, pszEnd);

   ::str().consume(pszJson, "[", 1, pszEnd);

   ::str().consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == ']')
   {

      pszJson++;

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

      payload.parse_network_payload(pszJson, pszEnd);

      ::str().consume_spaces(pszJson, 0, pszEnd);

      if(*pszJson == ',')
      {

         pszJson++;

         continue;

      }
      else if(*pszJson == ']')
      {

         pszJson++;

         return;

      }
      else
      {

         string str = "not expected character : ";

         str += pszJson;

         throw_exception(error_parsing, str);

      }

   }

}


void var_array_skip_network_payload(const char *& pszJson)
{

   var_array_skip_network_payload(pszJson, pszJson + strlen(pszJson) - 1);

}


void var_array_skip_network_payload(const char *& pszJson, const char * pszEnd)
{
   
   ::str().consume_spaces(pszJson, 0, pszEnd);
   
   ::str().consume(pszJson, "[", 1, pszEnd);

   while (true)
   {
      
      var_skip_network_payload(pszJson, pszEnd);
      
      ::str().consume_spaces(pszJson, 0, pszEnd);

      if (*pszJson == ',')
      {
         
         pszJson++;
         
         continue;

      }
      else if (*pszJson == ']')
      {
         
         pszJson++;
         
         return;

      }
      else
      {
         
         string str = "not expected character : ";
         
         str += pszJson;

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

   for (index i = 1; i < get_count(); i++)
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





