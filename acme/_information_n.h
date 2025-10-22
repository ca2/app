// Created by camilo with mummys on 2025-10-21 13:40 <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_ACME::string _017Time(const class ::time& time);


class CLASS_DECL_ACME item_n40585
{
public:


   ::string          m_strPath;
   class ::time      m_timeGetHere;
   class ::time      m_timeLockElapsed;
   class ::time      m_timeLookUpElapsed;
   class ::time      m_timeLock2Elapsed;
   class ::time      m_timeShouldBuildElapsed;


   item_n40585();
   item_n40585(
      const ::scoped_string& scopedstrName,
      const class ::time& timeGetHere,
      const class ::time& timeLockElapsed,
      const class ::time& timeLockUpElapsed,
      const class ::time& timeLock2Elapsed,
      const class ::time& timeShouldBuildElapsed
   );
   ~item_n40585();


   ::string as_string() const;
  

};


class CLASS_DECL_ACME information_n40585 :
   virtual public ::particle
{
public:


   ::array_base < item_n40585 > m_itema;

   ::string as_string() const;


};


CLASS_DECL_ACME::string as_string(const ::item_n40585& item);



