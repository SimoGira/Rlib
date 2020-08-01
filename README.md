# Rlib
Robotics Library based on Fast DDS.

**Authors**: Simone Girardi

## 1. Installing dependencies
### Fast DDS 2.0.0
Follow the installation procedure at https://fast-dds.docs.eprosima.com/en/latest/index.html.

## 2. Building the Project from Source
To download the code, navigate to a folder of your choosing on your Computer (we take as reference the $HOME folder). First, make sure git and cmake are installed:
```
$ sudo apt-get update
$ sudo apt-get install git cmake
```

Then clone the Rlib project:
```
$ git clone https://github.com/SimoGira/Rlib
```
And finally you can build dataflow-orbslam
```
$ cd ~/Rlib
$ mkdir build && cd build
$ cmake ..
$ make
```

## 2. Build and run the example.
```
$ cd ~/Rlib/testRlib
$ mkdir build && cd build
$ cmake ..
$ make
$ ./testRlibPub
```
Open another terminal and run:
```
$ ./testRlibSub
```
