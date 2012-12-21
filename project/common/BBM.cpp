#include <NME/extension.h>
#include "BBM.h"


namespace bbm {
	
	
	bbmsp_event_t* bbmspEvent = NULL;
	int eventCategory = NULL;
	int eventType = NULL;
	bool initialized = false;
	bbmsp_profile_t* userProfile = NULL;
	
	
	bool Initialize (const char *uuid) {
		
		bbmsp_result_t rc = BBMSP_SUCCESS;
		
		rc = bbmsp_request_events (0);
		if (rc != BBMSP_SUCCESS) {
			
			return false;
			
		}
		
		rc = bbmsp_register (uuid);
		if (rc != BBMSP_SUCCESS) {
			
			return false;
			
		}
		
		nme_register_bps_event_handler (ProcessEvent, bbmsp_get_domain ());
		
		return true;
		
	}
	
	
	void ProcessEvent (bps_event_t *event) {
		
		bbmsp_event_get_category (event, &eventCategory);
		bbmsp_event_get_type (event, &eventType);
		bbmsp_event_get (event, &bbmspEvent);
		
		if (eventType == BBMSP_SP_EVENT_ACCESS_CHANGED) {
			
			int accessAllowed = bbmsp_event_access_changed_get_access_allowed (bbmsp_event);
			
			if (accessAllowed == 1) {
				
				initialized = true;
				
			} else {
				
				bbmsp_access_error_codes_t errorCode = bbmsp_event_access_changed_get_access_error_code (bbmsp_event);
				
			}
			
		}
		
		if (initialized) {
			
			rc = bbmsp_get_user_profile (userProfile);
			
		}
		
	}
	
	
}