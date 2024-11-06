#include "framework.h"
#include "application.h"
#include "acme/operating_system/message_box.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
//#include "acme/platform/sequencer.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/user/user/conversation.h"
//#include "acme/user/nano/nano.h"
#include "acme/memory/_new.inl"
#define FACTORY console_hello
#define __APP_ID "console/hello"
#include "acme/_iostream.h"
#include "acme/_stdio.h"
//#if defined(WINDOWS_DESKTOP) && defined(CUBE)
//#include "_static_factory.inl"
//#endif
//#include "acme_windows/_acme_windows.h"
//BEGIN_FACTORY(console_hello)
//FACTORY_DEPENDENCY(acme_windows)
//END_FACTORY()
#include "acme/console.h"
int * g_pi = nullptr;

enum enum_test_increment
{

   e_test_increment_none,
   e_test_increment_one,
   e_test_increment_two,
   e_test_increment_three,
   e_test_increment_four,
   e_test_increment_last = e_test_increment_four,
   e_test_increment_count,
   

};




//
//void implement(::platform::context * pcontext)
//{
//
//   //throw ::exception(error_debug_testing);
//
//   output_debug_string("\n");
//
//   output_debug_string("\n");
//
//   output_debug_string("Hello!!");
//
//   output_debug_string("\n");
//
//   output_debug_string("\n");
//
//   while (true)
//   {
//
//      auto result = auto pmessagebox = __initialize_new ::message_box(pcontext, "Hello!!\nNo: for exception test!!", "Hello App!", e_message_box_yes_no_cancel | e_message_box_default_button_3, "Hello Multiverse!!");

pmessagebox->sync();
//
//      if (result == e_dialog_result_yes)
//      {
//
//         output_debug_string("\n");
//
//         output_debug_string("Yes!!\n");
//
//         auto pmessagebox = __initialize_new ::message_box(pcontext, "Yes!!", "Yes!!", e_message_box_ok);

pmessagebox->sync();
//
//         break;
//
//      }
//      else if (result == e_dialog_result_no)
//      {
//
//         pcontext->fork([pcontext]()
//         {
//            
//            task_set_name("Second Thread");
//
//            pcontext->fork([pcontext]()
//                 {
//               
//               task_set_name("Third Thread");
//               
//               
//               try
//               {
//                  
////                  ::exception exception(error_catch_all_exception);
////
////                  auto psequencer = psystem->nano()->exception_message_console(exception, "Dummy inline Catchall Exception at Hello Console App!!\n", "Dummy inline Hello Console App!", e_message_box_ok, "Dummy inline Hello Console App!!");
////
////                  pmessagebox->async();
//                  
//                  //int * pi = nullptr;
//                  
//                  g_pi[1024] = 1;
//                  
//                  //int i = 23 / (iptr)g_pi;
//
//                  //output_debug_string("this is the result %d", i);
//                  
//               }
//               catch(::exception & exception)
//               {
//                  
//                  auto psequencer = pcontext->nano()->exception_message_console(exception, "Exception at Hello Console App!!\n" + exception.get_message(), "Hello Console App!", e_message_box_ok, "Hello Console App!!\n");
//
//                  pmessagebox->async();
//                  
//               }
//               catch(...)
//               {
//                  
//                  ::exception exception(error_catch_all_exception);
//
//                  auto psequencer = pcontext->nano()->exception_message_console(exception, "Catchall Exception at Hello Console App!!\n", "Hello Console App!", e_message_box_ok, "Hello Console App!!");
//
//                  pmessagebox->async();
//
//               }
//
//            });
//
//         });
//
//         output_debug_string("\n");
//
//         output_debug_string("No!\n");
//
//         auto pmessagebox = __initialize_new ::message_box(pcontext, "No!", "No!", e_message_box_ok);

pmessagebox->sync();
//
//      }
//      else if (result == e_dialog_result_cancel)
//      {
//
//         output_debug_string("\n");
//
//         output_debug_string("Cancel!!\n");
//
//         auto pmessagebox = __initialize_new ::message_box(pcontext, "Cancel", "Cancel", e_message_box_ok);

pmessagebox->sync();
//
//      }
//
//   }
//
//#ifdef UNIVERSAL_WINDOWS
//
//   getchar();
//
//   getchar();
//
//#endif
//
//}
//
//
//
//
//class MyPoint
//{
//public:
//
//   int x;
//   int y;
//
//
//   auto operator <=> (const MyPoint&p) const
//   {
//
//      auto yCompare = y - p.y();
//
//      return yCompare ? yCompare : x - p.x();
//      
//   }
//
//};

string checking_string_move_001()
{

   string str("checking_string_move_001");


   return str;

}


string checking_string_move_002()
{

   string str;

   auto p = ___new char[123];

   ansi_cpy(p, "checking_string_move_002");

   str = p;

   delete [] p;

   return str;

}


#include <algorithm>


void trim_left_001()
{


   string str("001Test");

   str.trim_left("01");

   output_debug_string_formatf("trim_left_001:\"%s\"\n\n", str.c_str());


}

void trim_right_001()
{


   string str("Test001");

   str.trim_right("01");

   output_debug_string_formatf("trim_right_001:\"%s\"\n\n", str.c_str());


}



void test_001()
{

   int_array a{ 1,1,2,3,5,8,13,21,34 };

   auto print_elem = [](auto const e) {::platform::get()->informationf(::as_string(e) + "\n"); };

   for(auto & item : a) print_elem(item);

   //::std::ranges::for_each(a, print_elem);

}


void test_002()
{



   auto pstart = __FILE__;
   auto pend = pstart + ansi_len(pstart);

   //const char * pSearch = __FILE__;
   //const char * pSearchEnd = pstart + strlen(pstart);

   string str(pstart, pend);


   //auto size = str.size();

   auto find = str.find("application.cpp");

   ASSERT(!ansi_icmp(find, "application.cpp"));

}


__IMPLEMENT_APPLICATION_RELEASE_TIME(console_hello);


//#error "error_compiled back function"

namespace console_hello
{
 
   
   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(console_hello));


   application::application()
   {
   }

   application::~application()
   {

   }


   ::string generatecontatenation(::particle * pparticle, char ch)
   {

      ::string str;

      int iCount = pparticle->mathematics()->random(20, 200);

      for (int i = 0; i < iCount; i++)
      {

         char ch1 = (ch + (char)pparticle->mathematics()->random(0, 4));

         str.append(&ch1, 1);

      }

      return str;

   }

   void application::test_contatenation(char ch)
   {

      
      fork([this, ch]()
   {

      string strLastA;
      string strLastB;
      ::file::path pathLast;
      ::file::path pathLast2;

   for (int i = 0; i < 100'000; i++)
   {
      string strA = generatecontatenation(this, ch);

      wstring wstrB = strA;

      string strC(wstrB);

      string str = strA + strC;

      string str1;

      string strD = generatecontatenation(this, ch);
      
      string strMillis;

      ::file::path path = strA / strLastB / "dynamic_source" / pathLast2.name() + ".exp";

      auto path1 = path.sibling(pathLast.name());

      strMillis = ::as_string(::i64_millisecond() % 1000);

      str1.formatf("this is a contatenation%s and format test%s ", str.c_str(), strD.c_str());

      if (str.size() < 20)
      {
         
         informationf("What!!");

      }
      if (str1.size() < 20)
      {

         informationf("What(1)!!");

      }

      if (i % 1'000 == 0)
      {

         output_debug_string_formatf("%c", ch);

      }

      strLastA = strA;
      pathLast = path;
      pathLast2 = pathLast;
   }

      output_debug_string_formatf("\nCompleted concatenation \"%c\"!!", ch);

      });


   }

   void application::test_datetime_format(char ch)
   {


      fork([this, ch]()
         {

            auto pdatetime = system()->datetime();
            ::earth::time timeNow;


      for (int i = 0; i < 1'000'000; i++)
      {

         timeNow.Now();

         string strCompileLogUnique = pdatetime->format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeNow);

         if (strCompileLogUnique.size() < 5)
         {
            informationf("What!!");

         }
         if (i % 10'000 == 0)
         {

            output_debug_string_formatf("%c", ch);

         }
      }

      output_debug_string_formatf("\nCompleted datetime_format\"%c\"!!", ch);

            });


   }


#if defined(__STD_FORMAT__)

   void application::test_std_format()
   {

      ::string str;

      str.format("{2}{1}{0}", "!!", "Multiverse", "Hello");

      print("{}**", str);
      println("{}**", str);

   }

#endif // __STD_FORMAT__

   
   void application::main()
   {

      bool bTestOnlyUrl = true;

      if (bTestOnlyUrl)
      {

         {

            ::url::url url("http://website.com:80/script%20folder/strict%20object?param1=1&param2=2");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "http");

            auto strHost = url.connect().host();
            ASSERT(strHost == "website.com");

            auto strPort = url.connect().port();
            ASSERT(strPort == "80");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "/script%20folder/strict%20object?param1=1&param2=2");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "/script%20folder/strict%20object");

            auto strPath = url.request().path();
            ASSERT(strPath == "/script folder/strict object");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "strict%20object");

            auto strName = url.request().name();
            ASSERT(strName == "strict object");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "param1=1&param2=2");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }

         {

            ::url::url url("http://website.com/strict%20object?param1=1&param2=2");

            auto strProtocol = url.connect().protocol(); 
            ASSERT(strProtocol == "http");

            auto strHost = url.connect().host(); 
            ASSERT(strHost == "website.com");

            auto strPort = url.connect().port(); 
            ASSERT(strPort == "");
            
            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "/strict%20object?param1=1&param2=2");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "/strict%20object");

            auto strPath = url.request().path();
            ASSERT(strPath == "/strict object");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "strict%20object");

            auto strName = url.request().name();
            ASSERT(strName == "strict object");

            auto strQuery = url.request().query(); 
            ASSERT(strQuery == "param1=1&param2=2");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }

         {

            ::url::url url("http://website.com:80/");

            auto strProtocol = url.connect().protocol(); 
            ASSERT(strProtocol == "http");

            auto strHost = url.connect().host(); 
            ASSERT(strHost == "website.com");

            auto strPort = url.connect().port(); 
            ASSERT(strPort == "80");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "/");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "/");

            auto strPath = url.request().path();
            ASSERT(strPath == "/");

            auto strRawName = url.request().raw_name(); 
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query(); 
            ASSERT(strQuery == "");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }

         {

            ::url::url url("http://website.com:80");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "http");

            auto strHost = url.connect().host();
            ASSERT(strHost == "website.com");

            auto strPort = url.connect().port();
            ASSERT(strPort == "80");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "");

            auto strPath = url.request().path();
            ASSERT(strPath == "");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }

         {

            ::url::url url("http://website.com/");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "http");

            auto strHost = url.connect().host();
            ASSERT(strHost == "website.com");

            auto strPort =url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "/");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "/");

            auto strPath = url.request().path();
            ASSERT(strPath == "/");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }

         {

            ::url::url url("http://website.com");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "http");

            auto strHost = url.connect().host();
            ASSERT(strHost == "website.com");

            auto strPort = url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "");

            auto strPath = url.request().path();
            ASSERT(strPath == "");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }


         {

            ::url::url url("C:/");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "C");

            auto strHost = url.connect().host();
            ASSERT(strHost == "");

            auto strPort = url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "");

            auto strPath = url.request().path();
            ASSERT(strPath == "");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }

         {

            ::url::url url("C:\\");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "");

            auto strHost = url.connect().host();
            ASSERT(strHost == "");

            auto strPort = url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "");

            auto strPath = url.request().path();
            ASSERT(strPath == "");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(!bIsUrl);

         }


         {

            ::url::url url("C:/Windows/");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "C");

            auto strHost = url.connect().host();
            ASSERT(strHost == "Windows");

            auto strPort = url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "/");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "/");

            auto strPath = url.request().path();
            ASSERT(strPath == "/");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);

         }


         {

            ::url::url url("C:/Windows");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "C");

            auto strHost = url.connect().host();
            ASSERT(strHost == "Windows");

            auto strPort = url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "");

            auto strPath = url.request().path();
            ASSERT(strPath == "");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(bIsUrl);


         }

         {

            ::url::url url("C:\\Windows");

            auto strProtocol = url.connect().protocol(); 
            ASSERT(strProtocol == "");

            auto strHost = url.connect().host(); 
            ASSERT(strHost == "");

            auto strPort = url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "");

            auto strPath = url.request().path();
            ASSERT(strPath == "");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(!bIsUrl);

         }


         {

            ::url::url url("/C/Windows");

            auto strProtocol = url.connect().protocol();
            ASSERT(strProtocol == "");

            auto strHost = url.connect().host();
            ASSERT(strHost == "");

            auto strPort = url.connect().port();
            ASSERT(strPort == "");

            auto strRequestUri = url.request().as_string();
            ASSERT(strRequestUri == "");

            auto strRawPath = url.request().raw_path();
            ASSERT(strRawPath == "");

            auto strPath = url.request().path();
            ASSERT(strPath == "");

            auto strRawName = url.request().raw_name();
            ASSERT(strRawName == "");

            auto strName = url.request().name();
            ASSERT(strName == "");

            auto strQuery = url.request().query();
            ASSERT(strQuery == "");

            auto strFragment = url.request().fragment();
            ASSERT(strFragment == "");

            bool bIsUrl = url.is();
            ASSERT(!bIsUrl);

         }


         return;

      }



#if defined(__STD_FORMAT__)

      test_std_format();

#endif // __STD_FORMAT__

      if (system()->m_argc == 2)
      {


         if (system()->get_arg(1) == "remove_utf8_bom_phase1")
         {

            remove_utf8_bom_phase1();

         }
         else if (system()->get_arg(1) == "remove_utf8_bom_phase2")
         {

            remove_utf8_bom_phase2();

         }
         else if (system()->get_arg(1) == "search_special_characters")
         {

            search_special_characters();

         }


         return;


      }

      auto etestincrement = e_test_increment_none;

      for (; etestincrement <= e_test_increment_last; etestincrement = (enum_test_increment)((int)etestincrement+ 1))
      {

         switch (etestincrement)
         {
         case e_test_increment_none:
            output_debug_string("e_test_increment_none\n");
            break;
         case e_test_increment_one:
            output_debug_string("e_test_increment_one\n");
            break;
         case e_test_increment_two:
            output_debug_string("e_test_increment_two\n");
            break;
         case e_test_increment_three:
            output_debug_string("e_test_increment_three\n");
            break;
         case e_test_increment_four:
            output_debug_string("e_test_increment_four\n");
            break;


         };

      }



      //test_datetime_format('w');
      //test_datetime_format('x');
      //test_datetime_format('y');
      //test_datetime_format('z');
      //test_contatenation('a');
      //test_contatenation('f');
      //test_contatenation('l');
      //test_contatenation('s');

      //preempt(5_min);

      trim_left_001();

      trim_right_001();

      test_001();

      test_002();

      {

         string str = checking_string_move_001();

         information(str);

      }

      {

         string str = checking_string_move_002();

         information(str);

      }

      string_array stra{ "StringNumber1", "StringNumber2", "StringNumber5" };

      string str4("StringNumber4");

      stra.insert_at(2, str4);

      //MyPoint p1{ 1,1 };
      //MyPoint p2{ 1,4 };


      //auto compare = p1 <=> p2;

      //if (compare < 0)
      //{

      //   output_debug_string("p1 < p2");

      //}
      //else if (compare > 0)
      //{

      //   output_debug_string("p1 > p2");

      //}
      //else
      //{

      //   output_debug_string("p1  p2");

      //}

      {

         string str("HiHelloYou!!");

         auto psz1 = (const char *)str;

         output_debug_string_formatf("(\"%%s\", str) : %s\n", (const char*)str);
         output_debug_string_formatf("(\"%%s\", psz = (const char *)str; ) : %s\n", psz1);

      }





      output_debug_string("\n");

      output_debug_string("\n");

      output_debug_string("Hello!!");

      output_debug_string("\n");

      output_debug_string("\n");

      while (true)
      {

         auto pmessagebox = message_box((const char *) unsigned char"Hello!!\nNo: for exception test(\u2717)!!", "Hello App!", e_message_box_yes_no_cancel | e_message_box_default_button_3, "Hello Multiverse!!");

         auto result = pmessagebox->sync();

         if (result == e_dialog_result_yes)
         {

            output_debug_string("\n");

            output_debug_string("Yes!!\n");

            psequencer = message_box("Yes!!", "Yes!!", e_message_box_ok);

            pmessagebox->sync();

            break;

         }
         else if (result == e_dialog_result_no)
         {

            fork([this]()
               {

                  task_set_name("Second Thread");

            fork([this]()
               {

                  task_set_name("Third Thread");


            try
            {

               //                  ::exception exception(error_catch_all_exception);
               //
               //                  auto psequencer = psystem->nano()->exception_message_console(exception, "Dummy inline Catchall Exception at Hello Console App!!\n", "Dummy inline Hello Console App!", e_message_box_ok, "Dummy inline Hello Console App!!");
               //
               //                  pmessagebox->async();

                                 //int * pi = nullptr;

               g_pi[1024] = 1;

               //int i = 23 / (iptr)g_pi;

               //output_debug_string("this is the result %d", i);

            }
            catch (::exception& exception)
            {

               auto psequencer = exception_message_box(exception, "Exception at Hello Console App!!\n" + exception.get_message(), "Hello Console App!", e_message_box_ok, "Hello Console App!!\n");
               
               psequencer->then([this](auto)
                  {

                     auto pmessagebox = message_box("Got ::exception", "Got ::exception", e_message_box_ok | e_message_box_icon_information);

                     pmessagebox->async();

                  });

                  pmessagebox->async();


            }
            catch (...)
            {

               ::exception exception(error_catch_all_exception);

               auto psequencer = exception_message_box(exception, "Catchall Exception at Hello Console App!!\n", "Hello Console App!", e_message_box_ok, "Hello Console App!!");
               
               psequencer->then([this](auto)
               {

                     auto pmessagebox = message_box("Caught (...)", "Caught (...)", e_message_box_ok | e_message_box_icon_information);

                     pmessagebox->async();

               });

               pmessagebox->async();

            }

               });

               });

            output_debug_string("\n");

            output_debug_string("No!\n");

            psequencer = message_box("No!", "No!", e_message_box_ok);

            pmessagebox->sync();

         }
         else if (result == e_dialog_result_cancel)
         {

            output_debug_string("\n");

            output_debug_string("Cancel!!\n");

            psequencer = message_box("Cancel", "Cancel", e_message_box_ok);

            pmessagebox->sync();

         }

      }

#ifdef UNIVERSAL_WINDOWS

      getchar();

      getchar();

#endif


   }


};


////#ifdef WINDOWS
////int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
////#else
////int main(int argc, platform_char** argv, platform_char** envp)
////#endif
////{
////
////   class main main(argc, argv, envp);
////   //::acme::acme acme(argc, wargv, wenvp);
////
////   //sub_system subsystem(&acme);
////
////   //acme.m_pplatform = &subsystem;
////
////   //subsystem.m_pacme = &acme;
//////   subsystem.m_argc = argc;
//////#if defined(WINDOWS)  && defined(UNICODE)
//////   subsystem.m_wargv = argv;
//////   subsystem.m_wenvp = envp;
//////#else
//////   subsystem.m_argv = argv;
//////   subsystem.m_envp = envp;
//////#endif
////
////   //main_hold mainhold;
////
////   //set_argc_argv_envp(argc, argv, envp);
////
////   ::platform::application application;
////
////   application.m_applicationflags.m_bConsole = true;
////
////
////   application.initialize_application(&main);
////
////
////   //::pointer<APPLICATION_CLASS>papp(__allocate APPLICATION_CLASS());
//////
//////#ifdef NO_NETWORKING
//////
//////   papp->m_bNetworking = false;
//////
//////#endif
////
////   //#ifdef WINDOWS
////   //
////   //   papp->get_arguments_from_command_line();
////   //
////   //#else
////   //
////   //   papp->set_args(argc, argv, envp);
////   //
////   //#endif
////
////
////   //   {
////   //      //__FACTORY(FACTORY)(factory());
////   //
////   //      class ::main main;
////   //
////   //      //Sleep(30'000);
////   //
////   //      main.m_argc = argc;
////   //
////   //#ifdef WINDOWS
////   //
////   //      main.m_wargv = argv;
////   //      main.m_wenvp = envp;
////   //
////   //#else
////   //
////   //      main.m_argv = argv;
////   //      main.m_envp = envp;
////   //
////   //#endif
////
//////#ifdef APP_ID
//////
//////   papp->m_strAppId = APP_ID;
//////
//////#endif
////
////
////   //papp->m_pfnImplement = &::implement;
////
////   //try
////   //{
////
////      //__main(papp);
////
////   //}
////   //catch (const ::exception& exception)
////   //{
////
////   //   string strReport;
////
////   //   strReport += "Exception has occurred:\n";
////   //   strReport += exception.m_strMessage + ";\n";
////   //   //strReport += "Command Line:\n";
////   //   //strReport += node()->get_command_line() + ";\n";
////   //   strReport += exception.m_strDetails;
////   //   strReport += "Callstack:\n";
////   //   strReport += exception.m_strCallstack;
////
////   //   fprintf(stderr, "%s", strReport.c_str());
////
////   //}
////   //catch (...)
////   //{
////
////   //   fprintf(stderr, "Unknown exception has occurred\n");
////
////   //}
////
////   //      papp->m_bConsole = true;
////   //
////   //      papp->m_strAppId = __APP_ID;
////   //
////   //      try
////   //      {
////   //
////   //         int iExitCode = papp->main_loop();
////   //
////   //         return iExitCode;
////   //
////   //      }
////   //      catch (const ::exception & exception)
////   //      {
////   //
////   //         fprintf(stderr, "Exception has occurred \"%s\"(\"%s\")", exception.m_strMessage.c_str(), exception.m_strDetails.c_str());
////   //
////   //      }
////   //      catch (...)
////   //      {
////   //
////   //         fprintf(stderr, "Unknown Exception has occurred");
////   //
////   //      }
////
////
////   //   process_set_args(argc, argv);
////   //
////   //   auto psystem = acme_system_init();
////   //
////   //   {
////   //
////   //#ifdef WINDOWS
////   //
////   //      wcsdup_array wcsdupa;
////   //
////   //      auto envp = psystem->node()->_get_envp(wcsdupa);
////   //
////   //#endif
////
////   //   ::e_status estatus = ::success;
////   //
////   //   //process_set_args(argc, argv);
////   //
////   //   auto psystem = acme_system_init();
////   //
////   //   if (!psystem)
////   //   {
////   //
////   //      return -1;
////   //
////   //   }
////   //
////   //   //psystem->m_bConsole = false;
////   //
////   //   //application_common(psystem);
////   //
////   //   //string strCommandLine(pCmdLine);
////   //
////   //   {
////   ////#ifdef WINDOWS
////   ////
////   ////      //wcsdup_array wcsdupa;
////   ////
////   ////      //auto envp = psystem->node()->_get_envp(wcsdupa);
////   ////
////   ////      platform_char** envp = nullptr;
////   ////
////   ////#endif
////   //
////   //      psystem->system_construct(argc, argv, envp);
////   //
////   //   //psystem->set_current_handles();
////   //
////   //   estatus = psystem->init_system();
////   //
////   //   if (!estatus)
////   //   {
////   //
////   //      return estatus.error_status();
////   //
////   //   }
////   //
////   //
////   //      implement(psystem);
////   //
////   //   }
////   //
////   //   acme_system_term();
////   //
////   //   return process_get_status();
////
////   //   }
////
////     // ::acme::finalize();
////
////   
////   //throw ::exception(error_debug_testing);
//
//   output_debug_string("\n");
//
//   output_debug_string("\n");
//
//   output_debug_string("Hello!!");
//
//   output_debug_string("\n");
//
//   output_debug_string("\n");
//
//   while (true)
//   {
//
//      auto psequencer = application.message_box("Hello!!\nNo: for exception test!!", "Hello App!", e_message_box_yes_no_cancel | e_message_box_default_button_3, "Hello Multiverse!!");
//
//      auto result = pmessagebox->sync();
//
//      if (result == e_dialog_result_yes)
//      {
//
//         output_debug_string("\n");
//
//         output_debug_string("Yes!!\n");
//
//         psequencer = application.message_box("Yes!!", "Yes!!", e_message_box_ok);
//
//         pmessagebox->sync();
//
//         break;
//
//      }
//      else if (result == e_dialog_result_no)
//      {
//
//         auto pcontext = application.m_papplication;
//
//         pcontext->fork([pcontext]()
//         {
//            
//            task_set_name("Second Thread");
//
//            pcontext->fork([pcontext]()
//                 {
//               
//               task_set_name("Third Thread");
//               
//               
//               try
//               {
//                  
////                  ::exception exception(error_catch_all_exception);
////
////                  auto psequencer = psystem->nano()->exception_message_console(exception, "Dummy inline Catchall Exception at Hello Console App!!\n", "Dummy inline Hello Console App!", e_message_box_ok, "Dummy inline Hello Console App!!");
////
////                  pmessagebox->async();
//                  
//                  //int * pi = nullptr;
//                  
//                  g_pi[1024] = 1;
//                  
//                  //int i = 23 / (iptr)g_pi;
//
//                  //output_debug_string("this is the result %d", i);
//                  
//               }
//               catch(::exception & exception)
//               {
//                  
//                  auto psequencer = pcontext->exception_message_box(exception, "Exception at Hello Console App!!\n" + exception.get_message(), "Hello Console App!", e_message_box_ok, "Hello Console App!!\n");
//
//                  pmessagebox->async();
//                  
//               }
//               catch(...)
//               {
//                  
//                  ::exception exception(error_catch_all_exception);
//
//                  auto psequencer = pcontext->exception_message_box(exception, "Catchall Exception at Hello Console App!!\n", "Hello Console App!", e_message_box_ok, "Hello Console App!!");
//
//                  pmessagebox->async();
//
//               }
//
//            });
//
//         });
//
//         output_debug_string("\n");
//
//         output_debug_string("No!\n");
//
//         psequencer = application.message_box("No!", "No!", e_message_box_ok);
//
//         pmessagebox->sync();
//
//      }
//      else if (result == e_dialog_result_cancel)
//      {
//
//         output_debug_string("\n");
//
//         output_debug_string("Cancel!!\n");
//
//         psequencer = application.message_box("Cancel", "Cancel", e_message_box_ok);
//
//         pmessagebox->sync();
//
//      }
//
//   }
//
//#ifdef UNIVERSAL_WINDOWS
//
//   getchar();
//
//   getchar();
//
//#endif
//
//}

//console_hello::application g_consolehelloapplication;

void application_main()
{

   auto papplication = __allocate console_hello::application();

   auto iExitCode = application.application_main();

   return iExitCode;

}



