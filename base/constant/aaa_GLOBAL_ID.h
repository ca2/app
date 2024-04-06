#pragma once


enum
{

   // here it is proper just no-argument updates
   INITIAL_UPDATE = 1'000'001,
   PRE_CLOSE_DOCUMENT_UPDATE,
   NEW_DOCUMENT_UPDATE,
   CLOSE_DOCUMENT_UPDATE,
   OPEN_DOCUMENT_UPDATE,
   SAVE_DOCUMENT_UPDATE,
   EVENT_ID,
   UPDATE_XXX,
   FULL_ID,
   DOCUMENT_ID,
   TOPIC_OK_ID,
   INITIALIZE_ID,
   BROWSE_ID,
   SYNCHRONIZE_PATH_ID,
   FILTER_ID,
   FORM_ID,
   REDRAW_ID,
   COUNT_ID,

   // calling
   CREATE_CALLING,
   DESTROY_CALLING,

   // promisse
   FINISH_PROMISSE,
   DIALOG_RESULT_PROMISSE,
   COMPLETE_PROMISSE,


};
