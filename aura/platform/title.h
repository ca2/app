#pragma once


class title :
   public string
{
public:

   title(const string & str) : string(str) {}

};



inline var operator + (var var, const ::title& title)
{

   if (var.get_type() != type_propset)
   {

      var["message"] = var.get_string();

   }

   var["title"] = (const ::string&) title;

   return var;

}



inline var operator + (const char* psz, const ::title& title)
{

   return operator +((::var)psz, title);

}

