# BES_IAS [![UPVD Logo](https://upload.wikimedia.org/wikipedia/fr/e/e6/UPVD_logo.svg)](https://www.univ-perp.fr)

> BES_IAS is a IAS Simulator.

Project carried out during my first year of Master CHPS under the supervision of D.Defour Teacher / researcher at the Mathematics and Physics laboratory (LAMPS) at the University of Perpignan Via Domitia.

This simulator take an assembly ias file in source and simulate it.

## Project overview

### File tree

Project  
|  
├─ doc/  
│  └─ Projet_2021_edited.pdf  
├─ include/  
│  ├─ iastype.h  
│  ├─ io.h  
│  ├─ macro.h  
│  ├─ main.h  
│  ├─ memory.h  
│  ├─ translator.h  
│  ├─ ual.h  
│  └─ uc.h  
├─ output/  
│  ├─ instruction_test/  
│  └─ validation/  
├─ scripts/  
│  ├─ instruction_test/  
│  ├─ validation/  
│  ├─ execute_all_test.sh  
│  └─ execute_all_validation_script.sh  
├─ src/  
│  ├─ io.c  
│  ├─ main.c  
│  ├─ memory.c  
│  ├─ translator.c  
│  ├─ ual.c  
│  └─ uc.c  
├─ .gitignore  
├─ CMakeLists.txt  
├─ LICENSE  
├─ Makefile  
└─ README.md  

### Module

In include folder you can find :
 - iastype : contain abstract type of data.
 - macro : contain preprocessor macros;

And in src :
 - io : contain output functions, used to show internal simulator state.
 - memory : contain main memory and functions associated.
 - translator : contain function and struct for translate the input file.
 - ual : contain arithmetic and logic registers and ual function.
 - uc : contain program control unit registers and uc function.

### Other folders

 - doc : document(s) related to the project.
 - scripts : contain all the instructions and validations tests. And 2 bash scripts to execute all the ias file.
 - output : folder generated after run the bash script, it contain all the tests output.

## Building

### Dependencies

Nothing

### Compiling

To build the Makefile run the provided CMake file:

```shell
cmake .
```

To build the project run the generated Makefile:

```shell
make
```

## Running

Run the `bes_ias` executable.

```shell
./bes_ias [OPTION] INPUT_FILE
```

You can use the following options :

 - Option `-h` or `--help` to have information on all the options available.

 - Option `-n` or `--no-debug` to not show the register at each step of execution.

 - Option `-o` or `--output-to-file` to block the interrupt func.

 - Option `-m` or `--max-cycle` with a number to specify how many cycles is the limit before the simulation stop (by default 1000).

Example: 

```shell
./bes_ias -m 2000 ./scripts/validation/fact.ias
```
## Execute all tests

To execute all tests in row :

```shell
bash ./scripts/execute_all_test.sh && bash ./scripts/execute_all_validation_script.sh 
```
You find the output in `output/`

## Licensing

BES_IAS is under the MIT Licence, specified in `LICENCE`.
The copyright notice in `LICENCE` must be included in all projects using BES_IAS as well as binaries of BES_IAS or projects using BES_IAS.

## Contact

You can contact me at :

Sofiane Bessaï (sofiane.bessai66@gmail.com)
