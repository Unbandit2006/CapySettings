# CapySettings

This is a library for a new configuration file type.

```CapySettings

//       name       |     value    
name:       String  = "CapySettings"
smart:      Boolean = true
usefulness: Integer = 10             // out of 10
version:    Float   = 1.0

```

## Reason
Why make another configuration/markdown file again. Simply, USABILITY. I have had the issue of having data from these config/markdown files be provided in string format. 
This is an issue as if you forget to cast the result, your program will crash or simply execute undefined behavior and thats never good. So I created a statically typed 
configuration/markdown file type. I also wanted comments to better explain certain values. And making a statically typed configuration file, also provides the editor of
such a file, better understanding of what value is expected.

## Compile on Windows/MinGW
So I predominantly work on a barebones Windows/MinGW build, so my ways maybe archaic, but they work for me.

### Static Library
```cmd
gcc -c lib-src/CapySettings.c -o c-lib/static-lib/CapySettings.o
```
You may modify the output file, just be aware the other commands use this Repo as a structure
```cmd
ar rcs c-lib/static-lib/libCapySettings.a c-lib/static-lib/CapySettings.o
```

Then when building your code with gcc dont forget to use:
```cmd
-Lc-lib/static-lib -lCapySettings
```
Again if you modified the output please change the flags respective of your change.

## Documentation

```c
CSFile CapySettings_OpenFile(char *path, bool debug);

// example
CSFile settings = CapySettings_OpenFile("sample.csettings", false); // The library includes stdbool.h

```
First command you should run. Loads command into memory, returns CSFile



```c
int CapySettings_ReadFile(CSFile* pCSFile);

// example
CapySettings_ReadFile(&settings);
```
This function lexs, parses, pre-checks, just overall converts the configuration file to be usable by languages.


```c
void CapySettings_CloseFile(CSFile* pCSFile);

// example
CapySettings_CloseFile(&settings);
```
This function deallocates all memory used by the lib.


```c
int CapySettings_GetAsInteger(CSFile* pCSFile, char* name);
char* CapySettings_GetAsString(CSFile* pCSFile, char* name);
double CapySettings_GetAsDouble(CSFile* pCSFile, char* name);
int CapySettings_GetAsBoolean(CSFile* pCSFile, char* name);

// example
printf("name: %s\n", CapySettings_GetAsString(&settings, "name");
printf("smart: %i\n", CapySettings_GetAsBoolean(&settings, "smart");
printf("usefulness: %i\n", CapySettings_GetAsInteger(&settings, "usefulness");
printf("version: %d\n", CapySettings_GetAsDouble(&settings, "version");
```
These functions are different functions that returns different types of the same pair with the same name. 
You may only call this after CapySettings_ReadFile



## Next steps
- [] Fix CapySettings_AddSetting to not add multiple settings of the same name.
- [] Implement arrays

## Future
- [] Python implementation
