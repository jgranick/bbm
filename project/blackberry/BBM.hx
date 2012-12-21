package blackberry;


import cpp.Lib;


class BBM {
	
	
	public static function initialize (uuid:String):Bool {
		
		return bbm_initialize (uuid);
		
	}
	
	
	private static function bbm_initialize = Lib.load ("bbm", "bbm_initialize", 1);
	
	
}