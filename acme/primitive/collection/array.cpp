#include "framework.h"


void _123abc_debug_gen_array_randomize(::matter * pobject);
void ___arrayStdSortTest();

/*
void _123abc_debug_gen_array_randomize(::matter * pobject)
{
   int_array a;
   a.add_unique(1);
   a.add_unique(2);
   App(papp).array().randomize(a);
}
*/


#ifdef UNIT_TEST

void unit_test___arrayStdSortTest()
{
   array<i32, i32> ia;
   /*::acme::_sort::quick_sort(
      ia,
      sort::CompareAscending < i32 >);*/

}

#endif // UNIT_TEST





namespace papaya
{

    string_array x1_decode_ida(const char * psz)
	{
      string str(psz);
      if(str.is_empty())
      	return string_array();
		str.replace_with(",", "><");
		str = str.Mid(1, str.get_length() - 2);
		string_array stra;
      stra.explode(",", str);;
		return stra;
	}

    string x1_encode_ida(const string_array & stra)
	{
		string str;
      for(i32 i = 0 ; i < stra.get_count(); i++)
		{
			str += "<" + stra[i] + ">";
		}
		return str;
	}


} // namespace papaya


#ifdef UNIT_TEST

void unit_test_quick_sort_iter()
{


   int_array ia;

   ia.add(3);
   ia.add(2);
   ia.add(1);

   ::sort::quick_sort_iter(ia.begin(), ia.end());


}



#endif //UNIT_TEST
