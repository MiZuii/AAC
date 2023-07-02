# AAC
### Ascii Art Conversion library
Little simple library bringing joy to our dull lifes by creating cute images of ascii frogs and other heart warming things.


⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀                                                        
⠀⠀⠀⠀⠀⠀⣠⣶⡿⢭⡉⠳⡄⠀⠀⠀⠀⠀⠀⣠⠞⣩⣴⣿⡷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                 
⠀⠀⠀⠀⠀⢰⠿⢿⣷⡾⠛⡆⠙⠛⠛⠋⠙⠛⠛⠋⢰⡿⠻⣿⣶⡞⠂⠀⠀⠀⠀⠀⠀⠀⠀                                                 
⠀⠀⠀⠀⠀⢻⣦⣾⣿⣿⣶⠃⣀⣀⣤⠤⠤⣤⣀⣀⠘⣷⣶⣿⣿⣷⡆⠀⠀⠀⠀⠀⠀⠀⠀                                                     
⠀⠀⠀⠀⢀⡾⠛⠿⠿⠿⠛⠋⠉⠀⠀⠀⠀⠀⠀⠉⠙⠓⠻⠿⠟⠛⢦⠀⠀⠀⠀⠀⠀⠀⠀                                                 
⠀⠀⠀⠀⢸⡃⠀⠀⠀⠀⠀⠀⠀⠀⠘⠦⠜⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠂⠀⠀⠀⠀⠀⠀⠀                                                   
⠀⠀⠀⠀⠈⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠏⠀⠀⠀⠀⠀⠀⠀⠀                                                    
⠀⠀⠀⠀⠀⠀⠈⠓⠦⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡤⠴⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                
⠀⠀⠀⠀⠀⠀⢀⣀⣀⠀⣾⠉⠀⠀⠀⠀⠀⠀⠀⠈⠉⣷⠀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                  
⠀⠀⠀⠀⠀⢰⠉⠀⠉⠙⣿⠀⠀⢶⠀⠀⠀⠀⣴⠀⠀⣿⠛⠉⠀⠈⡧⠀⠀⠀⠀⠀⠀⠀⠀                                                 
⠀⠀⠀⠀⠀⠘⣧⡀⠀⠀⢿⡀⠀⠘⣇⠀⠀⢠⡏⠀⠀⣿⠀⠀⠀⣸⠇⠀⠀⠀⠀⠀⠀⠀⠀                                                
⠀⠀⠀⢀⣀⣤⣬⣿⣆⠀⠘⢷⡀⠀⢻⡀⠀⢸⠁⠀⣰⡏⠀⠀⢾⣧⣤⣤⣀⡀⠀⠀⠀⠀⠀                                                  
⠀⠀⠀⠛⠛⠛⠛⠛⠛⠛⠛⠋⠻⠟⠛⠿⠲⠿⠛⠿⠏⠙⠛⠛⠋⠉⠉⠉⠛⠋⠀⠀⠀⠀⠀                                                 

P.S. Mostly Ascii. Go to examples to find some more cute stuff

--------
## Usage

Because it's a library the usage is infinite, all you need is a documentation which is automaticly built with the doxygen. There is no online web page or pdf, you need to build your own copy. There is a little help to get you started which is called **examples**.

### Examples

In ```/examples``` directory there are 4 example programs showcasing the basic abilities of the library. To run the examples locally u need to build the project and run the command below in the build directory.
```bash 
make examples
```
The examples source code can be found in directory ```ProjectDir/examples```. The compiled examples binaries will appear in the directory ```ProjectDir/examples/bin``` after compiling. Navigate to ```/examples``` in this repository to see the result of example programs without cloning and compiling the project.

### Documentation

To use the library to it's full potential you will need the documentation which will appear in directory ```ProjectDir/doc```. To generate the documentation run the command below in the project build directory.
```bash
make doc
```
You can always clean the build documentation with command ```make clean_doc```.

To open the web based documentation find the ```index.html``` file in the ```ProjectDir/doc/html``` directory. For the pdf based documentation search for the ```ProjectDir/doc/latex/refman.pdf```. To build the documentation there is few things needed. Go to **Documentation building** section in this README.

### Binary file of the library

For now there is no easy zip to download, you need to clone the project, build it and than take the needed files which are ```AAC.h``` (the main library header) and the ```libAAClib.a``` which is the compiled binary of the library.

-------------------
## Building library

After cloning the library, go to the downloaded directory and run:

```bash
mkdir build
cd build
cmake ..
make
```

This will build the cmake project and the library. The binary of the library is found in the build directory with name ```libAAClib.a```. The header for the library is in the main project directory.

-------------------------
## Documentation building
To properly build the documentation you need to install:
 + Doxygen
 + Graphviz
 + Latex

Installation of Doxygen

```bash
sudo apt-get install doxygen
```

Installation of Graphviz

```bash
sudo apt install graphviz
```

Installation of Latex

```bash
sudo apt-get install texlive-latex-extra
```
