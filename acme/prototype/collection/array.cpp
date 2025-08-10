#include "framework.h"
#include "_array.h"
//#include "string_array.h"


void _123abc_debug_gen_array_randomize(::particle * pparticle);
void ___arrayStdSortTest();

/*
void _123abc_debug_gen_array_randomize(::particle * pparticle)
{
   ::int_array_base a;
   a.add_unique(1);
   a.add_unique(2);
   App(papp).array().randomize(a);
}
*/


#ifdef UNIT_TEST

void unit_test___arrayStdSortTest()
{
   array<int, int> ia;
   /*::acme::_sort::quick_sort(
      ia,
      sort::CompareAscending < int >);*/

}

#endif // UNIT_TEST





namespace acme
{

    string_array_base x1_decode_ida(const ::scoped_string & scopedstr)
	{
      string str(scopedstr);
      if(str.is_empty())
      	return string_array_base();
		str.replace_with(",", "><");
		str = str.substr(1, str.length() - 2);
		string_array_base stra;
      stra.explode(",", str);;
		return stra;
	}

    string x1_encode_ida(const string_array_base & stra)
	{
		string str;
      for(int i = 0 ; i < stra.get_count(); i++)
		{
			str += "<" + stra[i] + ">";
		}
		return str;
	}


} // namespace acme


#ifdef UNIT_TEST

void unit_test_quick_sort_iter()
{


   ::int_array_base ia;

   ia.add(3);
   ia.add(2);
   ia.add(1);

   ::sort::quick_sort_iter(ia.begin(), ia.end());


}



#endif //UNIT_TEST
