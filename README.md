# Theremin

This is a project I worked on for a university course called "Audio-Programming".  
It aims to loosely resemble the musical instrument Theremin, whose sound amplitude and frequency can be modulated by the musician's hands' proximity to two antennas. My digital Theremin is similarly controlled by the proximity to two ultrasonic distance sensors.

It's an ongoing effort, which I hope I will be working on from time to time.  
Help and feedback is greatly appreciated :D

## Design

The Theremin instrument itself utilizes an ESP8266 micro controller and two ultrasonic sensors for distance measurement. These distance values are then send via Wi-Fi, Bluetooth or USB (BT and USB to be implemented) to a device running a SuperCollider server, which synthesizes the sound. For the transport currently an OSC library is used.

## To-dos

The system's basic functionality works, but it's not much. Some things to work on:

- Nicer hardware design:

  - The controller and sensors are just stuck on a breadboard at the moment, so a better solution would be nice, maybe even a 3D-printed case.

  - Maybe add a display for entering IP-address and displaying current synth or last played note.

  - A battery (and solar panel) might also be convenient for powering the Theremin on the go. You could take it with you to a park, connect it to SC on a laptop or PinePhone, connect a nice Speaker and you're good to go :)


- USB. Connecting via Wi-Fi is currently pretty bad, because the IP-address needs to be hard coded into the firmware. Just plugging in a USB cable to the device with the SC server would be much more convenient.


- Better Wi-Fi. Maybe it's possible somehow to input the IP-address without reflashing the firmware. A display would be necessary here.


- Way better synths. The current synth is pretty terrible.


- A web interface for control. Even the Pinecil has a GUI now, so maybe this could be a nice addition. Plugging the Theremin in via USB and entering the IP-Address so one can use it wirelessly thereafter could be pretty convenient.


- Onboard sound:

  - Maybe a micro controller can be made to do some basic sound synthesis by itself and power onboard speakers, so you could play the Theremin standalone.

  - If the first point isn't possible, maybe create another version with a beefier SBC that runs Linux and SC itself.


- Maybe use a better micro controller. My ESP8266 was just lying around, so I just used it, as it was enough for what I needed. Maybe the project could benefit from a more recent micro controller for implementing the planned features.


As you can see, I still have some work to do here :)  
If anyone stumbles across this repo and is interested in helping me, giving feedback or basing their own version off my work, do feel free to reach out to me :)
