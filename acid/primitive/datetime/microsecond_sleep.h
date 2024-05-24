#pragma once


class CLASS_DECL_ACID microsecond_sleep
{
public:

   char sz[16];

   // should be enough to hold struct of { HANDLE }

   microsecond_sleep();
   

   ~microsecond_sleep();
   bool sleep(unsigned long usec);


};

