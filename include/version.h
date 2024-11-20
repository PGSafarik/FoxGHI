#ifndef FXGHI_VERSION_H
#define FXGHI_VERSION_H

namespace FXGHI{
/*
 Project Initial full version :
*/

namespace Version{
	/* Application */
	static const char PROJECT_ID[ ]        = "fxghi";
	static const char PROJECT_NAME[ ]      = "libFoxGHI";
	static const char PROJECT_COPYRIGHT[ ] = "P.G.Safarik";
	static const char PROJECT_LICENSION[ ] = "GNU GPL v3";
	static const char PROJECT_PLATFORM[ ]  = "amd64";
	static const char PROJECT_OS[ ]        = "Linux";
	static const char PROJECT_CATEGORY[ ]  = "Desktop, Library, GUI, Utils";

	//Date Version Types
	static const char DATE[]                 = "20";
	static const char MONTH[]                = "11";
	static const char YEAR[]                 = "2024";
	static const char UBUNTU_VERSION_STYLE[] = "24.11";

	//Software Status
	static const char STATUS[]       =  "Alpha";
	static const char STATUS_SHORT[] =  "a";

	//Standard Version Type
	static const long MAJOR    = 0;
	static const long MINOR    = 4;
	static const long REVISION = 4;
	static const long BUILD    = 1;

	//Miscellaneous Version Types
	#define RC_FILEVERSION 0,4,4,1
	#define RC_FILEVERSION_STRING "0, 4, 4, 1\0"
	static const char FULLVERSION_STRING[] = "20.11 0.4.4.1 ALPHA";

	//These values are to keep track of your versioning and testing state.
  static const long TEST_COUNT    = 0;
	static const long TEST_HISTORY  = 0;
}       /* version */
}       /* FXGHI */

#endif  /* FXGHI_VERSION_H */
