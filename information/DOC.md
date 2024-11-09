# CapySettings documentation

## Example code
```c
#include "CapySettings.h"

CSFile string = CapySettings_LoadFromString("name: String = 'Daniel'", false);
CapySettings_ReadFile(&string);

CapySettings_PrintAllSettings(&string);

CapySettings_CloseFile(&string);
```

CapySettings_LoadFromString (char* string, bool debug)
----
Prepares proper structs, and information for proper reading.

### Arguments:
    char* string | String to be processed.
	bool  debug  | Flag to get debug info.

### Returns:
    CSFile | CapySettingsFile that will be used for almost everything.

### Example:
```c
CSFile csFile = CapySettings_LoadFromString("developer_name: String = \"Daniel\"", true);
```
</br>


CapySettings_LoadFromFile (FILE* pFile, bool debug)
----
Prepares proper structs, and information for proper reading, loads file into memory.

### Arguments:
	FILE* pFile | A pointer to the that you want to use. Be sure to open in binary mode reading.
	bool  debug | Flag to get debug info.

### Returns:
	CSFile | CapySetingFile that will be used for almost everything.

### Examples:
```c
FILE* pfile = fopen("sample.csettings", "rb");
CSFile csFile = CapySettings_LoadFromFile(pfile, true);
```
</br>


CapySettings_ReadFile (CSFile* pCSFile)
----
Reads the CapySettingFile (csettings), properly parses it, and creates CSettings.

### Arguments:
	CSFile* pCSFile | A pointer to the CSFile made by one of the load functions.

### Returns:
	1  | Reached the end of file without closing quote.
	2  | Allocation for string error.
	3  | Allocation for literal error.
	4  | Allocation for number error.
	5  | Literal count is not equal to value count.
	6  | No type was provided for CSetting.
	7  | Not proper value for String.
	8  | Not proper value for Boolean.
	9  | Not proper value for type Float.
	10 | Not proper value for type Integer.
	0  | All is good.

### Example:
```c
int result = CapySettings_ReadFile(&csFile);
```
</br>


CapySettings_CloseFile (CSFile* pCSFile)
----
Closes and deallocated all the memory used by the library.

### Arguments:
	CSFile* pCSFile | A pointer to the CSFile made by one of the load functions.

### Example:
```c
CapySettings_CloseFile(&csFile);
```
</br>


CapySettings_AddSetting (CSFile* pCSFile, CSettingType type, char* name, CSettingValue value)
----
Adds a CSetting to the settings for a developer to use.

### Arguments:
	CSFile*       pCSFile | A pointer to the CSFile made by one of the load functions.
	CSettingType  type    | An enum of CSettingType specifing what is the type of the Setting.
	char*         name    | Name of the CSetting. {name: type = value}
	CSettingValue value   | Union of the correct value.

### Examples:
```c
CSettingValue value;
value.Integer = 18;

CapySettings_AddSetting(&csFile, INTEGER, "age", value);
```
</br>


CapySettings_SaveFile (CSFile* pCSFile, char* path)
----
Saves all of the settings to a file, by either creating it or overwriting it.

### Arguments:
	CSFile* pCSFile | A pointer to the CSFile made by one of the load functions.
	char*   path    | The path to the file that you want to put all of the Settings to.

### Returns:
	11 | Unable to access file.
	0  | All is good.

### Examples:
```c
int result = CapySettings_SaveFile(&csFile, "sample_saved.csettings");
```
</br>


CapySettings_GetAsInteger (CSFile* pCSFile, char* name)
----
Returns the value of an CSetting Integer in int format 

### Arguments:
	CSFile* pCSFile | A pointer to the CSFile made by one of the load functions.
	char*   name    | Name of the CSetting you want to retrieve.

### Returns:
	INT_MAX | If value is not an Integer

### Examples:
```c
int age = CapySettings_GetAsInteger(&csFile, "age");
```
</br>


CapySettings_GetAsString (CSFile* pCSFile, char* name)
----
Returns the value of an CSetting String in char* format 

### Arguments:
	CSFile* pCSFile | A pointer to the CSFile made by one of the load functions.
	char*   name    | Name of the CSetting you want to retrieve.

### Returns:
	"" | If value is not an String

### Examples:
```c
int name = CapySettings_GetAsString(&csFile, "name");
```
</br>


CapySettings_GetAsBoolean (CSFile* pCSFile, char* name)
----
Returns the value of an CSetting Boolean in bool format 

### Arguments:
	CSFile* pCSFile | A pointer to the CSFile made by one of the load functions.
	char*   name    | Name of the CSetting you want to retrieve.

### Returns:
	false | If value is not an Boolean

### Examples:
```c
bool isDope = CapySettings_GetAsBoolean(&csFile, "dope");
```
</br>


CapySettings_GetAsFloat (CSFile* pCSFile, char* name)
----
Returns the value of an CSetting Float in float format 

### Arguments:
	CSFile* pCSFile | A pointer to the CSFile made by one of the load functions.
	char*   name    | Name of the CSetting you want to retrieve.

### Returns:
	0.0f | If value is not an Float

### Examples:
```c
float percentageOfSuccess = CapySettings_GetAsFloat(&csFile, "success");
```
</br>