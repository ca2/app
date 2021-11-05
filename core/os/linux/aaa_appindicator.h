#pragma once


class user_notify_icon_bridge;


namespace linux
{


   class appindicator
   {
   public:


      virtual ~appindicator();

      virtual bool create(const ::string & pszId, const ::string & pszIcon, const ::string & pszFolder, user_notify_icon_bridge * pbridge) = 0;


   };


   appindicator * allocate_appindicator();


   void appindicator_destroy(appindicator * pindicator);


} // namespace linux



