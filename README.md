# Objects Rotator: A High-Performance 3D Object Visualization and Rotation App

Objects Rotator is a handy app designed to display and rotate 3D objects efficiently. It lets you choose the size of the objects and set the rotation speed to your liking.

For better performance, Objects Rotator is written in C and uses the SDL (Simple DirectMedia Layer) library. Instead of using triangles like most applications, Objects Rotator treats each object as a collection of separate vectors. This unique approach offers a different way to handle 3D objects.

 ## How to Install and Run the Project?
In order to run the project you must first download the SDL libabry.

### MAC OS
To do so on mac you can simply use the following command. (Assuming you have homebrew installed)

 ```sh
 brew install sdl2
 ```
#
 ### LINUX
 #### For Debian-based Distributions (e.g., Ubuntu)

  ```sh
sudo apt update
sudo apt install libsdl2-dev
 ```

 #### For Red Hat-based Distributions (e.g., Fedora)

```sh
sudo dnf check-update
sudo dnf install SDL2-devel
 ```
#
 To run the project you can simply use the provided Makefile. Just navigate to the project directory in the terminal and execute
 
 ```sh
make run
 ```

## Credits
[Kacper Machaj](https://github.com/KacperMachaj1)