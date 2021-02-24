# Stereo Matching and Depth Estimation using OpenCV

In order to build the project, create a directory and clone the repository using the following command:

```shell
git clone --recursive https://github.com/Aschratt/opencv-depth-from-stereo.git .
```

*Note that under Windows the directory path [must not contain](https://github.com/microsoft/vcpkg/issues/15592) any white spaces.*

You can use CMake to generate the project files for your target environment, as you are used to. The project uses [vcpkg](https://github.com/microsoft/vcpkg/), so all dependencies should be automatically resolved. If you are using Windows and Visual Studio, you can simply right-click the project directory and open it with Visual Studio. The project already defines a set of build environments (x64/x86 Release and Debug) for the integrated generator.