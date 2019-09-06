# Dependencies

To build this repository, you must install the "Boost" libraries. On
a Debian Linux system, you should be able to do so using the following
command:

`
sudo apt-get install libboost-all-dev
`

# Cloning and Building this Repository

Run the following commands to clone and build the lidar-2019 project:

`git clone https://github.com/UA-NASA-Robotics/lidar-2019.git`
`cd lidar-2019`
`git submodule init`
`git submodule update`
`mkdir build`
`cd build`
`cmake ..`
`make`
