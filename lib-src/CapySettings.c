#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "CapySettings.h"

char* keywords[KEYWORD_COUNT] = {
    "String",
    "Integer",
    "Float",
    "Boolean",

    "false",
    "true",
};

CSTokenType keywordType[KEYWORD_COUNT] = {
    TOKEN_STRING,
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_BOOLEAN,
    TOKEN_BOOLEAN_FALSE,
    TOKEN_BOOLEAN_TRUE,
};

///////////////////////
/// IMPLEMENTATION ///
/////////////////////

CSFile CapySettings_LoadFromFile(FILE* pFile, bool debug) {

	fseek(pFile, 0, SEEK_END);
	int fileSize = ftell(pFile);	
	fseek(pFile, 0, SEEK_SET);

	char* string = calloc(fileSize+1, sizeof(char));
	size_t read = fread(string, 1, fileSize, pFile);
	string[read] = '\0';
	
	CSFile file = {
		.data = string,
		.pos = 0,
		.debug = debug,
	};

    CSettings settings = {
        .size = 10,
        .occupied = 0,
        .objects = calloc(10, sizeof(CSettingObj) ),
    };

    CSTokenList tokenList = {
        .occupied = 0,
        .size = 10,
        .tokens = calloc(10, sizeof(CSToken)),
    };

	file.settings = settings;
	file.tokens = tokenList;
	file.type = 0;

	return file;
}

CSFile CapySettings_LoadFromString(char* string, bool debug) {

	CSFile file = {
		.data = string,
		.pos = 0,
		.debug = debug,
	};

    CSettings settings = {
        .size = 10,
        .occupied = 0,
        .objects = calloc(10, sizeof(CSettingObj) ),
    };

    CSTokenList tokenList = {
        .occupied = 0,
        .size = 10,
        .tokens = calloc(10, sizeof(CSToken)),
    };

	file.settings = settings;
	file.tokens = tokenList;
	file.type = 1;

	return file;
}

static void AddToken( CSTokenList* pList, CSTokenType type, char* value, int line ) {
    CSToken token = {
        .type = type,
        .value = value,
        .line = line
    };

    if (pList->occupied >= pList->size) {
        pList->size *= 2;
        pList->tokens = realloc(pList->tokens, sizeof(CSToken) * pList->size);
    }

    pList->tokens[pList->occupied] = token;
    pList->occupied++;
}

static char* ConvertTypeToString(CSTokenType type) {
    
    switch (type) {    
        case (TOKEN_STRING): { return "STRING"; } break;
        case (TOKEN_STRING_VALUE): { return "STRING_VALUE"; } break;
        case (TOKEN_LITERAL): { return "LITERAL"; } break;
        case (TOKEN_EQUAL): { return "EQUAL"; } break;
        case (TOKEN_COLON): { return "COLON"; } break;
        case (TOKEN_FLOAT): { return "FLOAT"; } break;
        case (TOKEN_FLOAT_VALUE): { return "FLOAT_VALUE"; } break;
        case (TOKEN_INTEGER): { return "INTEGER"; } break;
        case (TOKEN_INTEGER_VALUE): { return "INTEGER_VALUE"; } break;
        case (TOKEN_BOOLEAN): { return "BOOLEAN"; } break;
        case (TOKEN_BOOLEAN_TRUE): { return "BOOLEAN_TRUE"; } break;
        case (TOKEN_BOOLEAN_FALSE): { return "BOOLEAN_FALSE"; } break;
        case (TOKEN_ILLEGAL): { return "ILLEGAL"; } break;
		case (TOKEN_NEW_LINE): { return "NEW_LINE"; } break;
		case (TOKEN_COMMA): { return "COMMA"; } break;
		case (TOKEN_EOF): { return "END_OF_FILE"; } break;
        default: { return "Unknown token"; } break;
    }

}

static void ResetCounter(Counter* pCounter) {
	pCounter->size = 10;
	pCounter->occupied = 0;
	pCounter->tokens = calloc(10, sizeof(CSToken));
}

static void AddToCounter(Counter* pCounter, CSToken token) {
    if (pCounter->occupied >= pCounter->size) {
        pCounter->size *= 2;
        pCounter->tokens = realloc(pCounter->tokens, sizeof(CSToken) * pCounter->size);
    }

    pCounter->tokens[pCounter->occupied] = token;
    pCounter->occupied++;
}

void CapySettings_AddSetting( CSFile* pCSFile, CSettingType type, char* name, CSettingValue value ) {
    CSettingObj setting = {
        .type = type,
        .value = value,
        .name = name
    };

	bool able = true;

	for (int i = 0; i < pCSFile->settings.occupied; i++) {

		if (strcmp(name, pCSFile->settings.objects[i].name) == 0) {
			able = false;
		}

	}

	if (able == true) {
		if (pCSFile->settings.occupied >= pCSFile->settings.size) {
			pCSFile->settings.size *= 2;
			pCSFile->settings.objects = realloc(pCSFile->settings.objects, sizeof(CSettingObj) * pCSFile->settings.size);
		}

		pCSFile->settings.objects[pCSFile->settings.occupied] = setting;
		pCSFile->settings.occupied++;
	}
}

static int Parse(CSFile* pCSFile, CSToken literal, CSToken value, CSTokenType type) {
	CSettingValue val;
	CSettingType csettingType;

	switch (type) {

		case (TOKEN_STRING): {
			if (value.type != TOKEN_STRING_VALUE) {
				if (pCSFile->debug) {
					printf("{CapySettings} Not proper value for type String.\n{CapySettings} ERROR CODE: 8.\n");
				}

				exit(8);
				return 8;
			}

			val.String = value.value;
			csettingType = STRING;
		} break;

		case (TOKEN_BOOLEAN): {
			if (value.type != TOKEN_BOOLEAN_TRUE && value.type != TOKEN_BOOLEAN_FALSE) {
				if (pCSFile->debug) {
					printf("{CapySettings} Not proper value for type Boolean.\n{CapySettings} ERROR CODE: 9.\n");
				}

				exit(9);
				return 9;
			}

			if (value.type == TOKEN_BOOLEAN_TRUE) { val.Boolean = true; csettingType = BOOLEAN;  }
			
			if (value.type == TOKEN_BOOLEAN_FALSE) { val.Boolean = false; csettingType = BOOLEAN; }
		
		} break;

		case (TOKEN_FLOAT): {
			if (value.type != TOKEN_FLOAT_VALUE) {
				if (pCSFile->debug) {
					printf("{CapySettings} Not proper value for type Float.\n{CapySettings} ERROR CODE: 10.\n");
				}

				exit(10);
				return 10;
			}

			val.Float = strtof(value.value, NULL);
			csettingType = FLOAT;
		} break;

		case (TOKEN_INTEGER): {
			if (value.type != TOKEN_INTEGER_VALUE) {
				if (pCSFile->debug) {
					printf("{CapySettings} Not proper value for type Integer.\n{CapySettings} ERROR CODE: 11.\n");
				}

				exit(11);
				return 11;
			}

			val.Integer = atoi(value.value);
			csettingType = INTEGER;
		} break;

		default: {

		} break;

	}

	CapySettings_AddSetting(pCSFile, csettingType, literal.value, val);

	return 0;
}

int CapySettings_SaveFile(CSFile* pCSFile, char* path) {
    FILE* fp = fopen(path, "w");

    if (fp == NULL) {
        printf("{CapySettings} Unable to access file.\n{CapySettings} ERROR CODE: 12.\n");
        return 12;
    }

    for (int i = 0; i < pCSFile->settings.occupied; i++) {
        switch (pCSFile->settings.objects[i].type) {
            case STRING: {
                fprintf(fp, "%s: String = \"%s\"\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.String);
            } break;
                
            case BOOLEAN: {
                if (pCSFile->settings.objects[i].value.Boolean == 1) {
                    fprintf(fp, "%s: Boolean = %s\n", pCSFile->settings.objects[i].name, "true");
                } else {
                    fprintf(fp, "%s: Boolean = %s\n", pCSFile->settings.objects[i].name, "false");
                }
            } break;

            case INTEGER: {
                fprintf(fp, "%s: Integer = %i\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.Integer);
            } break;

            case FLOAT: {
                fprintf(fp, "%s: Float = %f\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.Float);
            } break;
        }
    }

    fclose(fp);

    return 0;
}

int CapySettings_ReadFile(CSFile* pCSFile) {
		
	int lineCount = 1;
	int lineCountC = 1;

	//////////////
	/// LEXING ///
	//////////////	
	while (pCSFile->data[pCSFile->pos] != '\0') {

		switch (pCSFile->data[pCSFile->pos]) {
        
			case '/': {
				if (pCSFile->data[pCSFile->pos + 1] == '/') {
					while (pCSFile->data[pCSFile->pos] != '\n') {
						pCSFile->pos++;
						lineCountC++;
					}
                
				} else {
					AddToken(&pCSFile->tokens, TOKEN_ILLEGAL, NULL, lineCount);
				}

			} break;

			case ' ':
			case '\t': {
				pCSFile->pos++;
				lineCountC++;
			} break;

			case '\n': {
				AddToken(&pCSFile->tokens, TOKEN_NEW_LINE, NULL, lineCount);
                
				lineCount++;
				lineCountC = 1;
				pCSFile->pos++;
			} break;

			case '\r': {
				pCSFile->pos++;
				lineCountC++;
			} break;

			case '=': {
				AddToken(&pCSFile->tokens, TOKEN_EQUAL, NULL, lineCount);
				pCSFile->pos++;
				lineCountC++;
			} break;
            
			case ':': {
				AddToken(&pCSFile->tokens, TOKEN_COLON, NULL, lineCount);
				pCSFile->pos++;
				lineCountC++;
			} break;

			case '\'':
			case '"': {
				char endChar = pCSFile->data[pCSFile->pos];

				pCSFile->pos++;
				lineCountC++;

				int start = pCSFile->pos;

				while (pCSFile->data[pCSFile->pos] != endChar && pCSFile->data[pCSFile->pos] != '\0') {
					pCSFile->pos++;
					lineCountC++;
				}

				if (pCSFile->data[pCSFile->pos] == '\0') {
					if (pCSFile->debug) {
						printf("{CapySettings} Reached end of file without string closure.\n{CapySettings} ERROR CODE: 1.\n");
					}
					return 1;
				}

				int end = pCSFile->pos - 1;

				char* string = (char*) calloc(end - start + 2, sizeof(char));
				if (string == NULL) {
					if (pCSFile->debug) {
						printf("{CapySettings} Couldn't allocate memory for string.\n{CapySettings} ERROR CODE: 2.\n");
					}
					return 2;
				}

				memcpy(string, pCSFile->data + start, end - start + 1);
				string[end - start + 1] = '\0'; // TODO: Needs to be freed

				AddToken(&pCSFile->tokens, TOKEN_STRING_VALUE, string, lineCount);

				pCSFile->pos++;
				lineCountC++;
			} break;

			case ',': {
				AddToken(&pCSFile->tokens, TOKEN_COMMA, NULL, lineCount);

				pCSFile->pos++;
				lineCountC++;
			} break;

			default: {
				bool isSomething = false;

				if (isalpha(pCSFile->data[pCSFile->pos]) != 0 || pCSFile->data[pCSFile->pos] == '_') {
					int start = pCSFile->pos;

					pCSFile->pos++;
					lineCountC++;

					while (isalnum(pCSFile->data[pCSFile->pos]) != 0 || pCSFile->data[pCSFile->pos] == '_' || pCSFile->data[pCSFile->pos] == '-') {
						pCSFile->pos++;
						lineCountC++;
					}

					int end = pCSFile->pos - 1;
			
					char* string = (char*) calloc(end - start + 2, sizeof(char));
					if (string == NULL) {
						if (pCSFile->debug) {
							printf("{CapySettings} Couldn't allocate memory for literal.\n{CapySettings} ERROR CODE: 3.\n");
						}
						return 3;
					}
					memcpy(string, pCSFile->data + start, end - start + 1);
					string[end - start + 1] = '\0'; // TODO: Needs to be freed
            
					bool isKeyword = false;
					for (int i = 0; i < KEYWORD_COUNT; i++) {
						if (strcmp(string, keywords[i]) == 0) {
							AddToken(&pCSFile->tokens, keywordType[i], NULL, lineCount);
							isKeyword = true;
						}
					}

					if (isKeyword == false) {
						AddToken(&pCSFile->tokens, TOKEN_LITERAL, string, lineCount);
					}
		
					isSomething = true;
				}
                
				if (isdigit(pCSFile->data[pCSFile->pos]) != 0) {
					int start = pCSFile->pos;

					pCSFile->pos++;
					lineCountC++;
            
					bool isFloat = false;

					while (isdigit(pCSFile->data[pCSFile->pos]) != 0) {
						pCSFile->pos++;
						lineCountC++;

						if (pCSFile->data[pCSFile->pos] == '.' && isdigit(pCSFile->data[pCSFile->pos + 1]) != 0) {
							pCSFile->pos++;
							lineCountC++;
							isFloat = true;

						}
					}

					int end = pCSFile->pos - 1;
			
					char* string = (char*) calloc(end - start + 2, sizeof(char));
					if (string == NULL) {
						if (pCSFile->debug) {
							printf("{CapySettings} Couldn't allocate memory for number.\n{CapySettings} ERROR CODE: 4.\n");
						}
						return 4;
					}
					memcpy(string, pCSFile->data + start, end - start + 1);
					string[end - start + 1] = '\0';

					if (isFloat == true) {
						AddToken(&pCSFile->tokens, TOKEN_FLOAT_VALUE, string, lineCount);
					} else {
						AddToken(&pCSFile->tokens, TOKEN_INTEGER_VALUE, string, lineCount);
					}

					isSomething = true;
				}

				if (isSomething == false) {
					AddToken(&pCSFile->tokens, TOKEN_ILLEGAL, NULL, lineCount);
                    
					pCSFile->pos++;
					lineCountC++;
				}
            
			} break;

		}

	}

	AddToken(&pCSFile->tokens, TOKEN_EOF, NULL, lineCount);


	//////////////////
	/// PRECHECKER ///
	/////////////////

	Counter literals = {
		.size = 10,
		.occupied = 0,
		.tokens = calloc(10, sizeof(CSToken))
	};

	Counter values = {
		.size = 10,
		.occupied = 0,
		.tokens = calloc(10, sizeof(CSToken))
	};

	CSTokenType type = -1;
	bool colon = false;     // NEED TO IMPLEMENT
	bool equal = false;     // NEED TO IMPLEMENT

	for (int i = 0; i < pCSFile->tokens.occupied; i++) {
		CSToken token = pCSFile->tokens.tokens[i];
		if (token.type == TOKEN_NEW_LINE || token.type == TOKEN_EOF) {
            if (!colon && !equal) {
                if (pCSFile->debug) {
                    printf("{CapySettings} No equal or colon on line %i.\n{CapySettings} ERROR CODE: 7.\n", pCSFile->tokens.tokens[i].line);
                }
				
                exit(7);
                return 7;
            }

			if (literals.occupied != values.occupied && literals.occupied != 0) {
				if (pCSFile->debug) {
					printf("{CapySettings} Literals and values are unequal on line %i.\n{CapySettings} ERROR CODE: 5.\n", pCSFile->tokens.tokens[i].line);
				}
				
				exit(5);
				return 5;
			}

			if (type == -1 && literals.occupied != 0) {
				if (pCSFile->debug) {
					printf("{CapySettings} No type provided on line %i.\n{CapySettings} ERROR CODE: 6.\n", pCSFile->tokens.tokens[i].line);
				}
				
				exit(6);
				return 6;
			}

			if (literals.occupied == 1) {
				Parse(pCSFile, literals.tokens[0], values.tokens[0], type);

			} else if (literals.occupied > 1) {
				for (int i = 0; i < literals.occupied; i++) {
					Parse(pCSFile, literals.tokens[i], values.tokens[i], type);
				}
			}

			ResetCounter(&literals);
			ResetCounter(&values);
			type = -1;
            colon = false;
            equal = false;

		} else {
			if (token.type == TOKEN_LITERAL) {
				AddToCounter(&literals, token);

			} else if (
				token.type == TOKEN_FLOAT_VALUE || token.type == TOKEN_STRING_VALUE || token.type == TOKEN_INTEGER_VALUE || token.type == TOKEN_BOOLEAN_TRUE
				|| token.type == TOKEN_BOOLEAN_FALSE
			) {
				AddToCounter(&values, token);
			
			} else if (
				token.type == TOKEN_STRING || token.type == TOKEN_FLOAT || token.type == TOKEN_INTEGER || token.type == TOKEN_BOOLEAN
			) {
				type = token.type;
			
            } else if (token.type == TOKEN_EQUAL) {
                equal = true;

            } else if (token.type == TOKEN_COLON) {
                colon = true;

            }

		}
	} 

	return 0;
}

int CapySettings_GetAsInteger( CSFile* pCSFile, char* name ) {
    for (int i = 0; i < pCSFile->settings.occupied; i++) {
        if (strcmp(pCSFile->settings.objects[i].name, name) == 0) {
            
            if (pCSFile->settings.objects[i].type == INTEGER) {
                return pCSFile->settings.objects[i].value.Integer;
            } else {
                return INT_MAX;
            }

        }
    }

    return 0;
}

char* CapySettings_GetAsString( CSFile* pCSFile, char* name ) {
    for (int i = 0; i < pCSFile->settings.occupied; i++) {
        if (strcmp(pCSFile->settings.objects[i].name, name) == 0) {
            
            if (pCSFile->settings.objects[i].type == STRING) {
                return pCSFile->settings.objects[i].value.String;
            } else {
                return "";
            }

        }
    }

    return "";
}

float CapySettings_GetAsFloat( CSFile* pCSFile, char* name ) {
    for (int i = 0; i < pCSFile->settings.occupied; i++) {
        if (strcmp(pCSFile->settings.objects[i].name, name) == 0) {
            
            if (pCSFile->settings.objects[i].type == FLOAT) {
                return pCSFile->settings.objects[i].value.Float;
            } else {
                return 0.0f;
            }

        }
    }

    return 0.0f;
}

bool CapySettings_GetAsBoolean( CSFile* pCSFile, char* name ) {
    for (int i = 0; i < pCSFile->settings.occupied; i++) {
        if (strcmp(pCSFile->settings.objects[i].name, name) == 0) {
            
            if (pCSFile->settings.objects[i].type == BOOLEAN) {
                return pCSFile->settings.objects[i].value.Boolean;
            } else {
                return false;
            }

        }
    }

	return false;
}

void CapySettings_CloseFile(CSFile* pCSFile) {

	if (pCSFile->type == 0) {
		free(pCSFile->data);
		pCSFile->data = NULL;
		pCSFile->pos = 0;
	}

    if (pCSFile->debug) { 
		printf("TOKEN COUNT: %i\n", pCSFile->tokens.occupied);
		printf("SETTINGS COUNT: %i\n", pCSFile->settings.occupied);

        printf("{\n");
        for (int i = 0; i < pCSFile->settings.occupied; i++) {
            switch (pCSFile->settings.objects[i].type) {
                case STRING: {
                    printf("\t\"%s\": \"%s\",\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.String);
                } break;
                
                case BOOLEAN:
                case INTEGER: {
                    printf("\t\"%s\": %i,\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.Integer);
                } break;

                case FLOAT: {
                    printf("\t\"%s\": %f,\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.Float);
                } break;
            }
        }
        printf("}\n");
    }

    for (int i = 0; i < pCSFile->tokens.occupied; i++) {
        
        if (pCSFile->debug) {
            printf("[%i]: %s %s %i\n", i, ConvertTypeToString(pCSFile->tokens.tokens[i].type), pCSFile->tokens.tokens[i].value, pCSFile->tokens.tokens[i].line);
        }

        if (pCSFile->tokens.tokens[i].value != NULL) {
            free(pCSFile->tokens.tokens[i].value);
            pCSFile->tokens.tokens[i].value = NULL;
        }
    }
}

void CapySettings_PrintAllSettings(CSFile* pCSFile) {
    printf("{\n");
    for (int i = 0; i < pCSFile->settings.occupied; i++) {
        switch (pCSFile->settings.objects[i].type) {
            case STRING: {
                printf("\t\"%s\": \"%s\",\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.String);
            } break;
                
            case BOOLEAN: {
                if (pCSFile->settings.objects[i].value.Boolean == true) {
                    printf("\t\"%s\": %s,\n", pCSFile->settings.objects[i].name, "true");
                } else {
                    printf("\t\"%s\": %s,\n", pCSFile->settings.objects[i].name, "false");
                }
            } break;
            
            case INTEGER: {
                printf("\t\"%s\": %i,\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.Integer);
            } break;

            case FLOAT: {
                printf("\t\"%s\": %f,\n", pCSFile->settings.objects[i].name, pCSFile->settings.objects[i].value.Float);
            } break;
        }
    }
    printf("}\n");
}
