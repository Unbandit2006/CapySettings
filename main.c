#include <stdio.h>
#include "lib-src/CapySettings.h"

int main() {
	CSFile settings = CapySettings_OpenFile("sample.csettings", false);

	CapySettings_ReadFile(&settings);

	printf("%s\n", CapySettings_GetAsString(&settings, "name"));

	CapySettings_CloseFile(&settings);

}
