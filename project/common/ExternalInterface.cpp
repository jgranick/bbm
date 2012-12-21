#include <hx/CFFI.h>
#include "BBM.h"


namespace bbm {
	
	//DEFINE_ENTRY_POINT (Initialize);
	
	value bbm_initialize (value uuid) {
		
		bool result = Initialize (alloc_string (uuid));
		return val_int (result);
		
	}
	DEFINE_PRIM (bbm_initialize, 1);
	
}