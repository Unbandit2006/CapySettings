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

[Link to docs](DOC.md)


## Next steps
- [x] Fix CapySettings_AddSetting to not add multiple settings of the same name.
- [] Implement arrays
- [] Make a CapySettings_EditSetting function to edit values in the CapySettings

## Future
- [] Python implementation
