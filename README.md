# compiler2
An LLVM frontend for my own custom lisp-like language

## Build from source (debian/ubuntu)
1. Clone the repository
    - `git clone https://github.com/mwg2202/compiler2.git`
2. Install cmake and LLVM
    - `apt install cmake llvm-dev`
3. Install ninja or make
    - `apt install ninja`   (for ninja)
    - `apt install make`    (for make)
4. Run make.sh or ninja.sh
    - `cd compiler2 && ./make.sh`   (for make)
    - `cd compiler2 && ./ninja.sh`  (for ninja)

The built executable should now be located in the build directory named as "compiler".
