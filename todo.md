# TODO

# testing changes

would like to build out a test suite library that's not actually coupled to the cpp library to test
these changes

### user tests

essentially testing the full state of the game engine by ensuring everything from the ground up
is working:
    - game start up
    - resource loading
    - user inputs

### module tests

test each module by creating some sort of per-module-test suite that will build / run the module
sources and any dependencies
    - will likely mean i need to decouple include dependencies
    - right now modules are really thin, may want to combine them into logical categories

current modules:
    - components
    - context
    - controllers (or 'managers')
    - resource factory
    - scenes
    - gui
    - user input
    - game objects
    - utils
    - system objects
    - event network

### feature tests

testing each code "feature". this will look very different across the different modules.
    - window functions
    - component functionality
    - object display / interaction
    - gui widgets
    - etc

# when bored or unsure what to do next...

 - clean up everything
    - remove comments
    - clear out dead code
    - make everything consistent like: `_func()/_obj`, `__func()/__obj`, etc and hpp/cpp declaration/implementation ordering
    - add/remove `const` where necessary/possible
 - explicit resource loading -> implicit by glob searching res/
 - states need work...
    - heirarchy/inherited funcs/etc
    - better separation by what type of thing is 'stateful'
 - window properties / set up
 - namespace consistency/meaning
