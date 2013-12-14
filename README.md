# qml2teapot

- C++ Advent Calendar 2013-12-14: Qt5/QML2でteapot
    - http://blog.wonderrabbitproject.net/2013/12/c-advent-calendar-2013-12-14.html

## require

- Qt5/QML2 runtime & development files
- clang++-3.2 or g++-4.8
- cmake-2.8.10
- ninja-1.3.4

## build

git clone https://github.com/usagi/qml2teapot.git
mkdir qml2teapot.build
cd qml2teapot.build
cmake -G Ninja ../qml2teapot
ninja

## run

qmlscene test.qml

