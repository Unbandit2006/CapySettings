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


int CapySettings_GetAsInteger(CSFile* pCSFile, char* name);

char* CapySettings_GetAsString(CSFile* pCSFile, char* name);

float CapySettings_GetAsFloat(CSFile* pCSFile, char* name);

bool CapySettings_GetAsBoolean(CSFile* pCSFile, char* name);

void CapySettings_PrintAllSettings(CSFile* pCSFile);

int CapySettings_ReadFile(CSFile* pCSFile);

CSFile CapySettings_LoadFromString(char* string, bool debug);

CSFile CapySettings_LoadFromFile(FILE* pFile, bool debug);

void CapySettings_AddSetting(CSFile* pCSFile, CSettingType type, char* name, CSettingValue value);

int CapySettings_SaveFile(CSettings* pCsettings, char* path);

void CapySettings_CloseFile(CSFile* pCSFile);

#endif