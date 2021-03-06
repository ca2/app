#include "framework.h"


var_array::var_array()
{

}


var_array::var_array(const std::initializer_list < ::payload > & varlist)
{

   for (auto & payload : varlist)
   {

      add(payload);

   }

}

var_array::var_array(const string_array & stra)
{
   operator = (stra);
}

var_array::var_array(const int_array & ia)
{
   operator = (ia);
}

var_array::var_array(const property_set & propset)
{
   operator = (propset);
}

var_array::var_array(const var_array & vara)
{
   operator = (vara);
}

var_array::~var_array()
{

}


index var_array::add(const ::payload & payload)
{

   if(payload.is_empty())
   {

      return -1;

   }

   return ::array < class ::payload >::add(payload);

}


::count var_array::add(const var_array & vara)
{
   for(i32 i = 0; i < vara.get_size(); i++)
   {
      add(vara[i]);
   }
   return this->get_count();
}


::count var_array::add_unique(const var_array & vara)
{

   ::count c = 0;

   for(i32 i = 0; i < vara.get_size(); i++)
   {

      if(!contains(vara[i]))
      {

         add(vara[i]);

         c++;

      }

   }

   return c;

}


string var_array::implode(const char * pszGlue) const
{
   string str;
   for(i32 i = 0; i < this->get_count(); i++)
   {
      if(i > 0)
         str += pszGlue;
      str += this->element_at(i).get_string();
   }
   return str;
}

index var_array::find_first(const char * psz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(this->element_at(find).get_string() == psz)
         return find;
   }
   return -1;
}

index var_array::find_first_ci(const char * psz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(this->element_at(find).get_string().compare_ci(psz) == 0)
         return find;
   }
   return -1;
}


index var_array::find_first(const ::payload & payload, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(this->element_at(find) == payload)
         return find;
   }
   return -1;
}

bool var_array::contains_ci(const char * pcsz, index find, index last, ::count countMin, ::count countMax) const

{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first_ci(pcsz, find, last)) >= 0)

      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool var_array::contains(const char * pcsz, index find, index last, ::count countMin, ::count countMax) const

{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(pcsz, find, last)) >= 0)

      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool var_array::contains(const ::payload & payload, index find, index last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_first(payload, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

::count var_array::erase_first_ci(const char * pcsz, index find, index last)

{
   if((find = find_first_ci(pcsz, find, last)) >= 0)

      erase_at(find);
   return find;
}

::count var_array::erase_first(const char * pcsz, index find, index last)

{
   if((find = find_first(pcsz, find, last)) >= 0)

      erase_at(find);
   return find;
}

::count var_array::erase_first(const ::payload & payload, index find, index last)
{
   if((find = find_first(payload, find, last)) >= 0)
      erase_at(find);
   return find;
}


::count var_array::erase_ci(const char * pcsz, index find, index last, ::count countMin, ::count countMax)

{
   ::count count = 0;
   if(contains_ci(pcsz, find, last, countMin, countMax))

      while(conditional(countMax >= 0, count < countMax)
            && (find = erase_first_ci(pcsz, find, last)) >= 0)

         count++;
   return count;
}


::count var_array::erase(const char * pcsz, index find, index last, ::count countMin, ::count countMax)

{
   ::count count = 0;
   if(contains(pcsz, find, last, countMin, countMax))

      while(conditional(countMax >= 0, count < countMax)
            && (find = erase_first(pcsz, find, last)) >= 0)

         count++;
   return count;
}


::count var_array::erase(const ::payload & payload, index find, index last, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains(payload, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
            && (find = erase_first(payload, find, last)) >= 0)
         count++;
   return count;
}

::count var_array::erase(const var_array & vara)
{
   if(&vara == this)
   {
      return erase_all();
   }
   else
   {
      ::count count = 0;
      for(index i = 0; i < vara.get_count(); i++)
      {
         count += erase(vara[i]);
      }
      return count;
   }
}

var_array & var_array::operator -=(::payload payload)
{
   erase(payload);
   return *this;
}

var_array & var_array::operator -=(var_array vara)
{
   erase(vara);
   return *this;
}

var_array var_array::operator -(::payload payload) const
{
   var_array vara(*this);
   vara.erase(payload);
   return vara;
}

var_array var_array::operator -(var_array varaParam) const
{
   var_array vara(*this);
   vara.erase(varaParam);
   return vara;
}

var_array & var_array::operator +=(::payload payload)
{
   add(payload);
   return *this;
}

var_array & var_array::operator +=(var_array vara)
{
   add(vara);
   return *this;
}

var_array var_array::operator +(::payload payload) const
{
   var_array vara(*this);
   vara.add(payload);
   return vara;
}

var_array var_array::operator +(var_array varaParam) const
{
   var_array vara(*this);
   vara.add(varaParam);
   return vara;
}

var_array & var_array::operator = (const string_array & stra)
{
   erase_all();
   for(i32 i = 0; i < stra.get_count(); i++)
   {
      add(stra[i]);
   }
   return *this;
}

var_array & var_array::operator = (const int_array & inta)
{
   erase_all();
   for(i32 i = 0; i < inta.get_count(); i++)
   {
      add(inta[i]);
   }
   return *this;
}


var_array & var_array::operator = (const property_set & propset)
{

   erase_all();

   index i = 0;

   for(auto & pproperty : propset)
   {

      set_at(i++, *pproperty);

   }

   return *this;

}


var_array & var_array::operator = (const var_array & vara)
{
   if(this != &vara)
   {
      erase_all();
      for(i32 i = 0; i < vara.get_count(); i++)
      {
         add(vara[i]);
      }
   }
   return *this;
}

void var_array::parse_json(const char * & pszJson)
{
   parse_json(pszJson, pszJson + strlen(pszJson) - 1);
}

int g_iRandomNumberGenerator = 0;


void var_array::parse_json(const char * & pszJson, const char * pszEnd)
{

   if(pszJson > pszEnd)
   {

      return;

   }

   ::str::consume_spaces(pszJson, 0, pszEnd);

   ::str::consume(pszJson, "[", 1, pszEnd);

   ::str::consume_spaces(pszJson, 0, pszEnd);

   if (*pszJson == ']')
   {

      pszJson++;

      return;

   }

   //::thread * pthread = nullptr;

   while(true)
   {

      
      //__throw(todo("thread"));
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

         __throw(::exit_exception(pthread));

      }*/

      ::payload & payload = add_new();

      payload.parse_json(pszJson, pszEnd);

      ::str::consume_spaces(pszJson, 0, pszEnd);

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

         __throw(error_parsing, str);

      }

   }

}


void var_array_skip_json(const char *& pszJson)
{

   var_array_skip_json(pszJson, pszJson + strlen(pszJson) - 1);

}


void var_array_skip_json(const char *& pszJson, const char * pszEnd)
{
   
   ::str::consume_spaces(pszJson, 0, pszEnd);
   
   ::str::consume(pszJson, "[", 1, pszEnd);

   while (true)
   {
      
      var_skip_json(pszJson, pszEnd);
      
      ::str::consume_spaces(pszJson, 0, pszEnd);

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

         __throw(error_parsing, str);

      }

   }

}


string & var_array::get_json(string & str, bool bNewLine) const
{

   str +="[";

   if(get_count() > 0)
   {

      element_at(0).get_json(str, bNewLine);

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

      element_at(i).get_json(str, bNewLine);

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "]";

   return str;

}





