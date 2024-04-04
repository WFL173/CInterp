# CInterp
CInterp is a project where the aim is to create a Python like interpreter to interprete the CI language. Where the CI language is a superset of the C, and a subset of the C++ languages. The aim of the lanaguage and the interpreter is to bring together, the easy importing of external libraries and configurationless building of projects that python provides and the structured nature of the C/C++ syntax. 

**Warning: This software is unfinished.**

## Building
This project uses build scripts to build. The project currently has no platform specific dependencies. 

### Windows
Windows does not come pre-installed with a default compiler. Therefore, to compile for Windows, build tools for visual studio will be necessary. These tools can be downloaded from [here](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022) under tools for visual studio > build tools for visual studio. After downloading the tools open the x64 native tools command prompt or if you already have visual studio installed you can open a command prompt and call vcvarsall.bat located in your visual studio files to setup the build environment in the command prompt. In the command prompt you just configured, change your current working directory to the RegMata folder and run the commands below and the project will be built and run.

    build.bat
    build\debug\Main.exe
    
If you want a release version the project run the commands below to build and run.

    build.bat release
    build\release\Main.exe

You could also open the project folder in visual studio code using the configured command prompt. After doing this you will be able to build with your visual studio code build shortcut.

### LINUX
The linux build scripts require the g++ compiler to build. If you don't have g++ you can install it using the command below.

    sudo apt install g++

With the compiler installed change your current workind directory to the project folder and run the command below.

    ./build.sh
    ./build/debug/Main.out
    
If you want a release version the project run the commands below to build and run.

    ./build.sh release
    ./build/debug/Main.out

You could also open the project folder in visual studio code using the configured command prompt. After doing this you will be able to build with your visual studio code build shortcut. 