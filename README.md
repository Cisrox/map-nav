# map-nav

![to_run](https://github.com/Cisrox/map-nav/assets/11482753/a7daf552-746f-4fc9-9bde-aba8140136fc)

Running this project is very simple, dependencies are pulled in automatically using Clion. 
To start the program, simply select Main, and hit run.

LATE NOTE: Simulation speed is set by a sleep(1) call on lines 399 and 422 of gui.hpp. Changing these lines to something like usleep(100) [extremely fast but hard to keep up with; can solve a 500x500 in around 3 - 5 minutes]. or usleep(200000) [fast, but can be kept up with visually].
