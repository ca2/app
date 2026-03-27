// From impact.h on 2023-01-15 19:26 <3ThomasBorregaardSørensen!!
#pragma once


#include "../x264.h"
#include "build.h"


namespace console_integration
{


namespace linux
{

class x264 :
virtual public ::console_integration::x264,
virtual public ::console_integration::linux::build
{
public:
   

   
//   ::string       m_strArch;
//   ::string       m_strTargetting;
//   ::string       m_strTarget;
//   ::string       m_strHost;
   
   
   x264();
   ~x264() override;
   
   
   void initialize(::particle * pparticle) override;
   
   void initialize_x264(
                        const ::scoped_string & scopedstrArch,
                        const ::scoped_string & scopedstrTargetting,
                        const ::scoped_string & scopedstrTarget,
                        const ::scoped_string & scopedstrHost);
   
   
   void build();
   
   void clean();
   
   void prepare();
   
   void download();
   
   void configure();
   
   void compile();
   
   void install();
   

   
};


} // namespace linux

} // namespace console_integration


