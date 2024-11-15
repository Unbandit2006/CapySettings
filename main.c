#include <stdio.h>
#include "lib-src/CapySettings.h"

int main() {
	//CSFile string = CapySettings_LoadFromString("name:               String = \"Daniel\"\nage:                Integer = 18\nhasDreams:          Boolean = true\n// assumed benefits (as very hard to calculate)\ncalculatedBenefits: Float = 1896.890000\nname:               String = \"Bob\"\n// Based on new AddSetting function, the name should still be Daniel", true);

	//FILE* pfile = fopen("sample.csettings", "rb");
	//CSFile string = CapySettings_LoadFromFile(pfile, true);


    CSFile test = CapySettings_LoadFromString("//", false);
    CapySettings_CloseFile(&test);
}
