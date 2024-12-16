# Tancodrom

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
├── tests/
│ └── # Test files
└── README.md
```

## Build

To build, you can import the project into CLion and run the `Tancodrom` target.

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

## Tests

// TODO