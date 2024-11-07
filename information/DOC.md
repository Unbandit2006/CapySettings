### CapySettings_OpenFile ('char* path', 'bool debug')
Loads the CapySetting file into memory

Args:
----
char* path: The path for the CapySetting file
bool debug: Show developer output

Returns
-------
 - CSFile { .pos = -1 } | ERROR: File not found.
 - CSFile { .pos = -2 } | ERROR: Can't allocate memory.
 - CSFile { .pos = -3 } | ERROR: Can't copy file into struct.

Example
-------
```c
CSFile settings = CapySettings_OpenFile("sample.csettings", false);
```


### CapySettings_ReadFile ('CSFile* pCSFile',)
Reads the CapySetting file

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile

Returns
-------
 - 1 | ERROR: String not closed in file.
 - 2 | ERROR: String value can't be allocated
 - 3 | ERROR: Literal value can't be allocated
 - 4 | ERROR: Number value can't be allocated
 - 5 | ERROR: Not proper Integer declaration
 - 6 | ERROR: Not proper Float declaration
 - 7 | ERROR: Not proper String declaration
 - 8 | ERROR: Not proper Boolean declaration
 - 9 | ERROR: Not proper Illegal token
 - 10 | ERROR: Missing colon

Example
-------
```c
int value = CapySettings_ReadFile(&settings);
```


### CapySettings_AddSetting ('CSFile* pCSFile', 'CSettingType type', 'char* name', 'CSettingValue value')
Adds a setting (name, value) pair to the CSettings

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile
CSettingType type: The type of the setting to save as
char* name: Name of the setting
CSettingValue value: Value of the setting

Example
-------
```c
CapySettings_AddSetting(&settings);
```


### CapySettings_SaveFile ('CSFile* pCSFile', 'char* path')
Saves all the settings to a set path

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile
char* path: Path to save the settings to

Returns
-------
 - 11 | ERROR: Unaccessible file

Example
-------
```c
CapySettings_SaveFile(&settings, "sample.csettings");
```


### CapySettings_GetAsInteger ('CSFile* pCSFile', 'char* name')
Returns the value of the setting as an Integer for whatever language you have.

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile
char* name: Name of the setting to search for.

Returns
-------
 - int INT_MAX | ERROR: Unable to find setting with name

Example
-------
```c
int ageValue = CapySetting_GetAsInteger(&settings, "age");
```


### CapySettings_GetAsString ('CSFile* pCSFile', 'char* name')
Returns the value of the setting as an String for whatever language you have.

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile
char* name: Name of the setting to search for.

Returns
-------
 - char*  | ERROR: Unable to find setting with name

Example
-------
```c
char* nameValue = CapySettings_GetAsString(&settings, "name");
```


### CapySettings_GetAsDouble ('CSFile* pCSFile', 'char* name')
Returns the value of the setting as an Double for whatever language you have.

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile
char* name: Name of the setting to search for.

Returns
-------
 - double 0.0 | ERROR: Unable to find setting with name

Example
-------
```c
double calculatedBenefits = CapySettings_GetAsDouble(&settings, "calculatedBenefits");
```


### CapySettings_GetAsBoolean ('CSFile* pCSFile', 'char* name')
Returns the value of the setting as an Boolean for whatever language you have.

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile
char* name: Name of the setting to search for.

Returns
-------
 - int -1 | ERROR: Unable to find setting with name

Example
-------
```c
int hasDreams = CapySettings_GetAsBoolean(&settings, "hasDreams");
```


### CapySettings_CloseFile ('CSFile* pCSFile',)
Deallocates all the memory used

Args:
----
CSFile* pCSFile: Pointer to CSFile struct provided by CapySettings_OpenFile

Example
-------
```c
CapySettings_CloseFile(&settings);
```


