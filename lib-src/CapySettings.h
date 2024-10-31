#ifndef CAPYSETTINGS_H
#define CAPYSETTINGS_H

#include <stdbool.h>

#define KEYWORD_COUNT 6

typedef enum {
    TOKEN_STRING,
    TOKEN_STRING_VALUE,

    TOKEN_LITERAL,
    TOKEN_EQUAL,
    TOKEN_COLON,

    TOKEN_FLOAT,
    TOKEN_FLOAT_VALUE,

    TOKEN_INTEGER,
    TOKEN_INTEGER_VALUE,

    TOKEN_BOOLEAN,
    TOKEN_BOOLEAN_FALSE,
    TOKEN_BOOLEAN_TRUE,

    TOKEN_ILLEGAL
} CSTokenType;

typedef struct {
    CSTokenType type;
    char *value;
    int line;
} CSToken;

typedef struct {
    int size;
    int occupied;
    CSToken *tokens;
} CSTokenList;


typedef enum {
    INTEGER,
    FLOAT,
    BOOLEAN,
    STRING,
} CSettingType;

typedef union {
    int   Integer;
    double Float; // done to get more percision than a float
    bool  Boolean;
    char* String;
} CSettingValue;

typedef struct {
    char* name;

    CSettingType type;
    CSettingValue value;
} CSettingObj;

typedef struct {
    int size;
    int occupied;
    CSettingObj* objects;
} CSettings;

typedef struct {
    char *data;
    int pos;

    CSTokenList tokens;
    CSettings settings;
    bool debug;
} CSFile;

/*
	Returns the value of an Integer in int format
    
	if value != Integer then returns INT_MAX
*/
int CapySettings_GetAsInteger(CSFile* pCSFile, char* name);

/*
	Returns the value of an String in char* format

	if value != String then returns ""
*/
char* CapySettings_GetAsString(CSFile* pCSFile, char* name);

/*
	Returns the value of an Float in double format

	if value != Float then returns 0.0
*/
double CapySettings_GetAsDouble(CSFile* pCSFile, char* name);

/*
	Returns the value of an Boolean in int format

	if value != Boolean then returns -1
*/
int CapySettings_GetAsBoolean(CSFile* pCSFile, char* name);

/*
	Reads CapySettings file

	returns 0 if good
	returns 1 if string value not closed
	returns 2 if string value cant be allocated
	returns 3 if literal cant be allocated
	returns 4 if number cant be allocated

	returns 5 Not proper integer
	returns 6 Not proper float
	returns 7 Not proper string
	returns 8 Not proper boolean
	returns 9 Illegal token

	returns 10 Missing colon
*/
int CapySettings_ReadFile(CSFile* pCSFile);

/*
	Loads CapySettings file into memory

	returns CSFile if good
	returns CSFile { .data = NULL, .pos = -1, .debug = debug } if file not found
	returns CSFile { .data = NULL, .pos = -2, .debug = debug } if couldn't allocate memory
	returns CSFile { .data = NULL, .pos = -3, .debug = debug } if couldn't put data into memory
*/
CSFile CapySettings_OpenFile(char *path, bool debug);

void CapySettings_AddSetting(CSettings* pCsettings, CSettingType type, char* name, CSettingValue value);

int CapySettimgs_SaveFile(CSettings* pCsettings, char* path);

void CapySettings_CloseFile(CSFile* pCSFile);

#endif