# AAC
### Ascii Art Conversion library
Little simple library bringing joy to our dull lifes by creating cute images of ascii frogs and other heart warming things.

### Building library

After cloning the library, go to the downloaded directory then run:

```bash
mkdir build
cd build
cmake ..
make
```

This will build the cmake project and the library. The binary of the library is found in the build directory with name ```libAAClib.a```. The header for the library is in the main project directory

### Docs
For documentation install Doxygen with Graphviz for website version and for pdf version install latex compiler. After building project run ```make doc``` to generate website documentation and ```make man``` for pdf documentation.

Installation of Doxygen

```bash
sudo apt-get update
sudo apt-get install doxygen
```

Installation of Graphviz

```bash
sudo apt install graphviz
```

Installation of Latex

```bash
sudo apt-get update
sudo apt-get install texlive-latex-extra
```

### Examples

For example usage of library run 
```bash 
make examples
```
There are four simple examples presenting how to operate the library. The examples code can be found in directory ```ProjectDir/examples```. The compiled examples binaries are in the directory ```ProjectDir/examples/bin```.
