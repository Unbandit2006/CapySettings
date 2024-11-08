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
    TOKEN_COMMA,
	TOKEN_NEW_LINE,
	TOKEN_EOF,

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
    float Float; 
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
	int type; // 0 if file, 1 if string
} CSFile;

typedef struct {
	int size;
	int occupied;

	CSToken* tokens;
} Counter;

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

CSFile CapySettings_LoadFromString(char* string, bool debug);

CSFile CapySettings_LoadFromFile(FILE* pFile, bool debug);

void CapySettings_AddSetting(CSFile* pCSFile, CSettingType type, char* name, CSettingValue value);

int CapySettimgs_SaveFile(CSettings* pCsettings, char* path);

void CapySettings_CloseFile(CSFile* pCSFile);

#endif