#ifndef BBM_H
#define BBM_H


#include <bps/event.h>
#include <bbmsp/bbmsp.h>
#include <bbmsp/bbmsp_events.h>
#include <bbmsp/bbmsp_userprofile.h>


namespace bbm {
	
	bbmsp_event_t* bbmspEvent;
	int eventCategory;
	int eventType;
	bool initialized;
	bbmsp_profile_t* userProfile;
	
	void Initialize ();
	void ProcessEvent (bps_event_t *event);
	
}


#endif