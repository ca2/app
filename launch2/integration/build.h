//
//  build.hpp
//  integration_console_integration
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/23 17:57
//
#pragma once


namespace integration { class context; }


namespace console_integration
{


   class build :
      virtual public ::particle
   {
   public:
      

      ::file::path                                    m_pathPrefixBase;
      ::pointer < ::integration::context >            m_papplication;


      build();
      ~build() override;
      
      void initialize(::particle * pparticle) override;


      
   
   };



} // namespace console_integration



