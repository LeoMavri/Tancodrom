# Tancodrom

A "simulation" in OpenGL that depicts Tanks and Helicopters.

## Team

* Radu-Leonard Mavrodin (@LeoMavri)
* Miruna-Lupu Cristina (@miru28)
* Andrei Palaghia (@PalaESef)

## Demo

[![Tancodrom Demo](https://img.youtube.com/vi/CNrxlhqxQIo/0.jpg)](https://www.youtube.com/watch?v=CNrxlhqxQIo)

## Structure

The project is structured as follows:

```
Tancodrom/
├── CMakeLists.txt
├── include/
│ └── other_header.h
├── src/
│ ├── main.cpp
│ └── other_source.cpp
├── models/
│ └── ru_tank.obj
├── lib/
│ └── # External libraries
└── README.md
```

## Build

To build, you can import the project into CLion and run the `Tancodrom` target.

Note: You'll have to change the resolution to match yours (`main.cpp`). You may also have to disable the `lto` flag within cmake if your CPU doesn't support link time optimisation (your results may vary).

Alternatively, you can manually build the project using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

## Run

To run the project, execute the following command:

```bash
./Tancodrom
```

## Taking "Inspiration"

Since the project themes are unlikely to change next year, I'll allow anyone to use anything in this project as long as you keep the current license (GPLv3). If you need to contact me, do so via `mavrileo@gmail.com` or any email linked to my Github account.

* https://github.com/bugbstrs/tancodrom
* https://github.com/robert-adrian99/Tancodrom (very old, very outdated, could be used to harvest obj files)
