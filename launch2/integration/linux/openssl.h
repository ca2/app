// From impact.h on 2023-01-15 19:26 <3ThomasBorregaardSørensen!!
#pragma once


namespace integration { class context; }


namespace console_integration
{


namespace linux
{

class openssl :
virtual public ::particle
{
public:
   
   
   ::pointer < ::integration::context > m_papplication;
   
   
   ::string       m_strConfigure;
   ::string       m_strDebug;
   ::string       m_strShared;
   
   
   openssl();
   ~openssl() override;
   
   
   void initialize(::particle * pparticle) override;
   
   
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


