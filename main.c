#include <stdio.h>
#include "lib-src/CapySettings.h"

int main() {
	//CSFile string = CapySettings_LoadFromString("name:               String = \"Daniel\"\nage:                Integer = 18\nhasDreams:          Boolean = true\n// assumed benefits (as very hard to calculate)\ncalculatedBenefits: Float = 1896.890000\nname:               String = \"Bob\"\n// Based on new AddSetting function, the name should still be Daniel", true);

	//FILE* pfile = fopen("sample.csettings", "rb");
	//CSFile string = CapySettings_LoadFromFile(pfile, true);

    CSFile string = CapySettings_LoadFromString("name: String = 'Daniel'\nidk: Boolean = true\nsmth, cool: Boolean = true, true", false);

	CapySettings_ReadFile(&string);

    CSettingValue value;
    value.String = "Is good band";
    CapySettings_AddSetting(&string, CSettingType_STRING, "Greenday", value);

    CapySettings_PrintAllSettings(&string);

	CapySettings_CloseFile(&string);
}
