# Automatic Path Search

## Relevance of the problem

Planning is one of the fundamental abilities of any intelligent agent. They are found everywhere and in different forms. For example, a robot that must independently circumvent obstacles, a computer game character, a drone, or even just a mechanical arm, whose task is to grab an object. Obviously, people cannot control all of them from the console. People and time is not enough. Therefore, the creation of effective scheduling algorithms is very important in the age of modern technology.
Automatic planning is a broad concept that includes many particular tasks. One of these, considered in this project, is trajectory planning. In this case, the task of the intelligent agent, being in the initial state, is to reach the target state, bypassing the obstacles, having information about the environment in which it is located. And according to this information, the agent must plan the optimal trajectory. Often, it is algorithmically possible to accurately find the best solution, but at the cost of this can be a long search and the amount of resources spent. Naturally, I want the intelligent agent to act optimally, quickly, using as few resources as possible. Thus, the task of modern researchers in this area is to develop and improve algorithms that combine three properties: optimality, time efficiency, and memory efficiency.



## Review of existing solutions

A frequently used representation of an instance of a problem, reflecting the peculiarities of the environment in which the agent operates, is a metric topological graph. Informally, this is a matrix of 0 and 1, which is a map, where 0 and 1 means that the cell is passable and not correspondingly.
This kind of environment is used in this project. There are different trajectory planning algorithms on such graphs. One of the progenitors of a very important class is such a basic algorithm as A \ *.
His main paradigm is to look for a way along the most promising directions. The concept of perspectivity of a vertex of a graph is defined by heuristics, which the programmer is laying. The essence of the algorithm A \ *: the vertices of the graph are sequentially considered in a certain order, where in priority are those vertices to which the distance from the vertex-start (the path found up to the present moment) in total with the estimated distance from this vertex to the finish is the smallest.

There are quite a few improvements A \ *. In this project, for example, JPS and Theta will be considered. The peculiarity of JPS in comparison with the classical A \ * is that when searching, not single steps are taken, but “jumps” to visible vertices according to a certain rule.


## Technological solutions used
1) C ++ programming language, since It is effective and convenient for OOP.

2) Qt creator development environment, since it is convenient to program in C ++, and also it is freely distributed.

3) The input format is XML, because it is well suited for storing maps, and it is also reasonable to have a certain standard of input data.

4) TinyXML library for processing XML files.

## Work Plan

1) January 20: Correct reading of correct input files. If not correct - a message to the user about the error with the type of error. The implementation of the generation of the output file.

2) February 20: A general program architecture should be written: with the necessary classes and a modular partition of the entire program source code into logical units.

3) March 20: The algorithm A \ * must be implemented with various heuristics and modifications.

4) End of May: The implementation of improved search algorithms for the class A \ *. Instructions for the user how to use the program: how to compile, how to run, as well as a description of the requirements for input data.

## Program description
Console program.
The program searches for the optimal path between two points on the map indicated in the input file. The algorithm is guaranteed to find it if the path exists, otherwise it reports to the standard output stream that the path was not found. If the input file is incorrect (see the description of the input file), then the program reports this and the output file does not generate.

## Implemented functionality
The program looks for the best path between two points on the map, is guaranteed to find it, if it exists. If not, a corresponding message is written to the standard output stream.

To achieve this goal was implemented:
- reading the input data of a special type (see the description of the input file)
- heuristic algorithm for finding the best path AStar
- data output to the output file

### Structure of input XML file
** obligatory ** - mandatory tag
** default ** is an optional tag. If not specified, the default value will be
Note that the structure of the XML file is important, not just the presence of tags.

* ``<root>``  - obligatory
  * ``<map>``    - obligatory
    * ``<width>``    - obligatory
    * ``<height>``   - obligatory
    * ``<cellsize>`` - default: 1
    * ``<startx>``   - default: "0"
    * ``<starty>``   - default: "0"
    * ``<finishx>``  - default: "0"
    * ``<finishy>``  - default: "0"
    * ``<grid>``     - obligatory
      * ``<row>``       - obligatory

  * ``<algorithm>``  - obligatory
    * ``<searchtype>``    - default: "astar"
    * ``<metrictype>``    - default: "euclid"
    * ``<linecost>``      - default: "1"
    * ``<diagonalcost>``  - default: "1.414"
    * ``<allowdiagonal>`` - default: "0"
    * ``<allowsqueeze>``  - default: "0"
    * ``<cutcorners>``    - default: "0"

*For an example of input XML, see the input folder in the repository.*

## Compilation
The project supports building with the cmake and make tools.

## running
In the terminal, run the compiled program with one argument - the name of the input XML-file.
The output XML file is generated by the path in which the input is located. "_Log.xml" is added to the file name.
If the .xml extension is not specified in the name of the input file, then _log is added to the output name.
