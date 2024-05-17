
# Programming project

## Group elements

Identify all group elements (numbers and names).

- up202307177 Diogo Sousa Campeão
- up202305008 José Augusto Pereira Mogrão Teixeira
- up202008423 António Miguel Miller Aguiar Tavares


## Accomplished tasks

This project consists in the implementation of a program that converts SVG arquives to PNG arquives.

### Task 4.1

In this task, we implemented the reading logic in readSVG.cpp, that consists in, for each XML node, we identify and treat the element, based on the name of the node.

Then, after creating the element, the algorithm puts it in svg_elements vector.

### Task 4.2

Here, we created classes for each element to consider. Ellipse, Circle (subclass of Ellipse), Polyline, Line (subclass of Polyline), Polygon and Rectangle (subclass of Polygon).

Each one of them contains a Constructor and a draw function. More functionalities for each class are implemented later in the project.

Note that subclasses do not have attributes of their own. They all use the attributes of the upper class.

### Task 4.3

For element transformations, we implemented abstract functions on all classes to apply the transformations given:
- Translate
- Rotate
- Scale
- 
Each one is treated differently, depending on the class where it is applied to.

We also implemented the reading logic in readSVG that checks the transformations and applies them to the objects.

### Task 4.4

We created the class Group and a new read function, parseGroup, that sends recursively a node containing a group, processes all the objects in the group, and returns a vector of SVGElements.

### Task 4.5

For uses, we created a vector pair of a string and a SVGElement. We added a reading logic with id processing, using the vector to associate the id with the element.

We also created a duplicate function, to duplicate an element, and copy constructors for every class.

For the specific case of groups, we used a getter in the class, to get the vector of elements, in order to do the duplication.




