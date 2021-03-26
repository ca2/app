
      if(g_iFtLevel < 0)
      {

         strPath = pcontext->m_pcontext->dir().install() / "app/_matter/main/_std/_std/font/truetype/arialuni.ttf";

         if(g_ft == nullptr)
         {

            iError = FT_New_Face((FT_Library)psystem->ftlibrary(),strPath,0,&g_ft);

            iError = FT_Select_Charmap(g_ft, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         }

         g_iFtLevel = 0;

      }

      if(g_iFtLevel < 1)
      {

         strPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";

         if(g_ft == nullptr)
         {

            iError = FT_New_Face((FT_Library)psystem->ftlibrary(),strPath,0,&g_ft);

            iError = FT_Select_Charmap(g_ft, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         }

         g_iFtLevel = 1;

      }


      if(g_iFtLevel < 2)
      {

         strPath = "/usr/share/fonts/dejavu/DejaVuSans.ttf";

         if(g_ft == nullptr)
         {

            iError = FT_New_Face((FT_Library)psystem->ftlibrary(),strPath,0,&g_ft);

            iError = FT_Select_Charmap(g_ft, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         }

         g_iFtLevel = 2;

      }


      if(g_iFtLevel < 3)
      {

         strPath = "/usr/share/fonts/truetype/freefont/FreeSans.ttf";

         if(g_ft == nullptr)
         {

            iError = FT_New_Face((FT_Library)psystem->ftlibrary(),strPath,0,&g_ft);

            iError = FT_Select_Charmap(g_ft, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         }

         g_iFtLevel = 3;

      }

      if(g_iFtLevel < 4)
      {

         strPath = "/usr/share/fonts/freefont/FreeSans.ttf";

         if(g_ft == nullptr)
         {

            iError = FT_New_Face((FT_Library)psystem->ftlibrary(),strPath,0,&g_ft);

            iError = FT_Select_Charmap(g_ft, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         }

         g_iFtLevel = 4;

      }

      if (g_iFtLevel < 5)
      {

         strPath = "/system/fonts/DroidSans.ttf";

         if (g_ft == nullptr)
         {

            iError = FT_New_Face((FT_Library)psystem->ftlibrary(), strPath, 0, &g_ft);

            iError = FT_Select_Charmap(g_ft, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         }

         g_iFtLevel = 5;

      }

