# Lit_Frames 
A software/hardware project I did to learn more about microcontrollers. The idea is to have a pair of photo frames, one for each person, that can be used to communicate to each other via lights and an LCD screen. Although one could simply use their phone to text the other, this was meant for a more simple gesture of, "I'm thinking about you.", alongside a simple message. 
# Hardware 
Used two ESP8266 controllers as the main part of the project. I picked these since they have a WiFi chip built-in, making it easier to use for a beginner. I coded the microcontrollers using C++ in the Arduino IDE. 
# Software 
As mentioned, I using C++ to write code for the ESP controllers to communicate with each other. The controllers use the MQTT protocol to communicate with each other, which I picked because it was lightweight. I also created Python scripts to test the communication between these controllers. Finally, I made a simple React website that a user could use to select a microcontroller and type out a message to send. 
# Future plans 
Currently I have only two microcontrollers communicating with each other, since the initial intent was for it to be used by only two people. In the future, I would like the ability to add more controllers for more people. 
Additionally, I would like to improve the website and possibly port it to an phone app using ReactNative to make it more convenient. 
One challenge I ran into during this project was having to manually input and update the WiFi SSID and Password. In the future, I want to figure out a way for the user to do this themselves. 
