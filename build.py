import sys
import os
import subprocess as sub
import platform

CC = "gcc"

if platform.system().lower() == "windows":
    execution_path = sys.argv[0][:-len('build.py')]

elif platform.system().lower() == "linux":
    execution_path = sub.run(["pwd"], shell=True, capture_output=True, text=True).stdout[:-1]

def clean():
    if platform.system().lower() == "windows":
        sub.run(["rmdir", "/q", "/s", os.path.join(execution_path, "c-lib")], shell=True)
        sub.run(["mkdir", os.path.join(execution_path, "c-lib", "static")], shell=True)

        print("Cleaned the library")

        return True

    elif platform.system().lower() == "linux":
        sub.run(f"rm -rf {os.path.join(execution_path, 'c-lib')}", shell=True)
        sub.run(f"mkdir -p {os.path.join(execution_path, 'c-lib', 'static')}", shell=True)
        
        print("Cleaned the library")

        return True

def static_lib():
    try:
        compile = sub.run(f"{CC} -c {execution_path}/lib-src/CapySettings.c -o {execution_path}/c-lib/static/CapySettings.o", shell=True, check=True, capture_output=True, text=True)
        compile1 = sub.run(f"ar rcs {execution_path}/c-lib/static/libCapySettings.a {execution_path}/c-lib/static/CapySettings.o", shell=True, check=True , capture_output=True, text=True)

        print("Compiled the static library")
        
        return True

    except sub.CalledProcessError as error:
        print("Error compiling CapySettings[static]")
        print(f"\tOutput: {error.stdout}\n\tError output: {error.stderr}\n\tReturn code: {error.returncode}\n")

        print("Compiled the static library")

        return False


def main():
    try:
        if platform.system().lower() == "windows":
            compile = sub.run(f"{CC} main.c -o main.exe -Lc-lib/static -lCapySettings", shell=True, check=True , capture_output=True, text=True)
            
            print("Compiled main")

            return True

        elif platform.system().lower() == "linux":
            compile = sub.run(f"{CC} main.c -o main -Lc-lib/static -lCapySettings", shell=True, check=True , capture_output=True, text=True)
            
            print("Compiled main")
            
            return True           

    except sub.CalledProcessError as error:
        print("Error compiling main")
        print(f"\tOutput: {error.stdout}\n\tError output: {error.stderr}\n\tReturn code: {error.returncode}\n")
        
        return False

def final():
    return clean() and static_lib() and main()

DEFAULT = "final"

options = {
    "final": final,
    "clean": clean,
    "static_lib": static_lib,
    "main": main,
}

global executed
executed = False

try:
    option = sys.argv[1]   

    for opt in options:
        if opt == option and executed == False:
            if options[opt]():
                executed = True
            else:
                executed = False

except Exception as e:
    if options[DEFAULT]():
        executed = True
    else:
        executed = False

if executed == False:
    print(f"Error in building.")

else:
    print("Everything should be built")