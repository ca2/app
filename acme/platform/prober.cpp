// Created by camilo with chatgpt and lowluds on 2025-02-12 21:32 <3ThomasBorregaardSorensen.cpp
#include "framework.h"
#include "prober.h"



namespace platform
{
   test_case::test_case(const ::scoped_string& scopedstr, const ::procedure& procedure):
      m_strName(scopedstr),
      m_procedure(procedure)
   {



   }


   test_case::~test_case()
   {


   }


   void test_case::run()
   {

      m_procedure.m_pbase->run();

   }


   void prober::add_prober(const ::scoped_string& name, const ::procedure& test)
   {

      m_testcasea.add(__allocate test_case(name, test));

   }


   void prober::run()
   {
      
      int passed = 0;

      int failed = 0;

      for (const auto& ptestcase : m_testcasea)
      {

         try 
         {

            ptestcase->run();

            information() << "[PASS] " << ptestcase->name() << "\n";

            passed++;

         }
         catch (const ::exception& e) 
         {

            information() << "[FAIL] " << ptestcase->name() << " - Exception: " << e.get_message() << "\n";

            failed++;

         }
         catch (...) 
         {

            information() << "[FAIL] " << ptestcase->name() << " - Unknown error\n";

            failed++;

         }

      }

      information() << "\nTests Passed: " << passed << ", Failed: " << failed << "\n";

   }

   void prober::expect(bool condition, const ::scoped_string& message)
   {

      if (!condition)
      {

         throw ::exception(error_exception, "Assertion failed: " + message);

      }

   }

   //// Example usage
   //void test_addition(TestRunner& runner) {
   //   runner.expect(2 + 3 == 5, "2 + 3 should be 5");
   //   runner.expect(2 + 2 == 4, "2 + 2 should be 4");
   //}

   //void test_failure(TestRunner& runner) {
   //   runner.expect(2 + 2 == 5, "2 + 2 should be 5"); // This should fail
   //}

   //int main() {
   //   TestRunner runner;

   //   runner.add_test("Addition Test", [&]() { test_addition(runner); });
   //   runner.add_test("Failure Test", [&]() { test_failure(runner); });

   //   runner.run();

   //   return 0;
   //}


} // namespace platform





