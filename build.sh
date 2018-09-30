#!/bin/sh  
  
buildPath="./build"
  
echo "Checking build folder for project." 

if [ ! -d "$buildPath" ]; then
    echo "Creating build folder"  
    mkdir "$buildPath"  
fi  

cd "$buildPath"
cmake ..
make
