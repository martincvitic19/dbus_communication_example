# DBUS DISPATCHER
The goal of this repository is to implement a client-server communication by utilizing the ```sdbus-cpp library```.

## NOTE
Regarding the naming convention, I have used the ```snake_case``` instead of ```camelCase```/```PascalCase``` ,which is more common in object-oriented programming, since I deem it more readable. This is, of course, only a matter of preference.

## BUILDING THE CODE
To build the code, create a ```build``` folder at the root level of the project and navigate to it. Then, run ```cmake ..``` to generate the build system and then ```cmake --build .``` to actually compile and link the obbject files and libraries to the executable.

To run the applications, run ```./DbusClient``` and ```./DbusClient``` from the ```build``` folder respectively. 