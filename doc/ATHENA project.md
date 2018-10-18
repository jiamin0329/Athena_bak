ATHENA project
==============


## 0. Introduction

## 1. Get Started

### 1.1 Install Dependencies

- Install git

  ```bash
  sudo apt-get install git
  ```

- Install cmake

  ```bash
  sudo apt-get install cmake
  ```

- Install gcc/g++/gfortran

  ```bash
  sudo apt-get install gcc g++ gfortran
  ```

- Install boost, see https://www.boost.org/, download boost then 

  ```bash
  ./bootstrap.sh
  ./b2 install
  ```

- Install cgns, see http://cgns.github.io/, download cgns package then

- Install glog, see https://github.com/google/glog.



Start to using Athena





cd Athena
sh build.sh

### 1.2 Development Tools

If you want to develop Athena, you need to install VSCode, see https://code.visualstudio.com/Download, then install C/C++ extension provided by Microsoft.



 ### 1.3 Project Structure

* .clang-format: clang-format is a strong tool to format your code automatically. Specific options should be defined in this file and then VSCode will use such options.


