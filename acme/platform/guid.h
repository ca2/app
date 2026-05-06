// Created by camilo on 2026-05-02 00:16 <3ThomasBorregaardSørensen!!
#pragma once


namespace acme
{


#pragma pack(push, guid, 1)


   struct guid_t
   {
      unsigned long Data1;
      unsigned short Data2;
      unsigned short Data3;
      unsigned char Data4[8];
   };

#pragma pack(pop, guid)


   class CLASS_DECL_ACME guid : public guid_t
   {
   public:
      guid() noexcept :
         guid_t{ 0, 0, 0, {0} }
      {}
      guid(const guid & guid) noexcept :
         guid_t{ guid.Data1, guid.Data2, guid.Data3, 
            {guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
         guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] } }
      {
      }
//      guid(const char * psz) noexcept
  //       {}

      guid(const string & str) noexcept;
      bool operator == (const guid & guid) const noexcept
      {

         return Data1 == guid.Data1
               && Data2 == guid.Data2
               && Data3 == guid.Data3
               && Data4[0] == guid.Data4[0]
               && Data4[1] == guid.Data4[1]
               && Data4[2] == guid.Data4[2]
               && Data4[3] == guid.Data4[3]
               && Data4[4] == guid.Data4[4]
               && Data4[5] == guid.Data4[5]
               && Data4[6] == guid.Data4[6] 
         && Data4[7] == guid.Data4[7];

      }
    //  bool operator != (const guid & guid) const noexcept;
      string to_string() const
      {
          string str;
            str.format("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
               Data1, Data2, Data3,
               Data4[0], Data4[1], Data4[2], Data4[3],
               Data4[4], Data4[5], Data4[6], Data4[7]);
         return str;
      }

   };


} // namespace acme
 



