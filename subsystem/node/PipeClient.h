// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "subsystem/_common_header.h"
#include "NamedPipe.h"


namespace subsystem
{
   /**
    * Pipe client factory.
    */
   class PipeClientInterface :
      virtual public ::Particle
   {
   public:



      //PipeClient();
      //virtual ~PipeClientInterface() = 0;

      virtual ::pointer < NamedPipe  >connect(const ::scoped_string & scopedstrName, unsigned int maxPortionSize) = 0;

   //private:


      //unsigned int m_maxPortionSize;
   };


    //using PipeClientInterface = particle_interface<PipeClientInterface>;

   /**
 * Pipe client factory.
 */
   class CLASS_DECL_SUBSYSTEM PipeClientComposite :
   virtual public Composite<PipeClientInterface>
   {
   public:

       
      ImplementCompositeø(PipeClient, pipeclient)

      //PipeClient();

      //~PipeClient() override;

         ::pointer < NamedPipe  >connect(const ::scoped_string& scopedstrName, unsigned int maxPortionSize) override
      {

         return m_ppipeclient->connect(scopedstrName, maxPortionSize);

      }

   // private:
   //    PipeClient();
   //
   //    unsigned int m_maxPortionSize;
   };

    class CLASS_DECL_SUBSYSTEM PipeClientAggregate :
    virtual public Aggregate< PipeClientComposite >
    {
    public:

        ImplementBaseø(PipeClient);

    };


   class CLASS_DECL_SUBSYSTEM PipeClient :
 virtual public Object < PipeClientAggregate >
   {
   public:

      ImplementObjectø(PipeClient)

   };



} //namespace subsystem