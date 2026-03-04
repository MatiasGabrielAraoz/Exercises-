# Trajectory
This is a C++ app that calculates the trajectory of an object with a force and angle

# Installation Guide:
## 1. Clone the repo
```
git clone https://github.com/MatiasGabrielAraoz/Trajectory.git
cd Trajectory
```
## 2. Install dependencies with VCPKG
```
vcpkg install
```
## 3. Create build dir
```
mkdir -p build
cd build
```
## 4. Configure it with CMake
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
```
## 5. Build it
```
cd ..
cmake --build build --parallel
```
