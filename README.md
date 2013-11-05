OS X MASTER App for Innovid Multiscreen Display Project
============================
This readme includes details and instructions for the Innovid Multiscreen Display OS X MASTER app. 

Version
----
1.0

This project uses Openframeworks 0.8.0 for OS X

Instructions
----
This is always being updated as we work out the simplest way to get this working.

### Setting up a local network
In order to synchronize video across all screens, we need to get them onto the same network. 

In order to do this in the easiest way possible, without having to rely on wifi or a private network,
we can use our Master computer to create our own computer-to-computer network for us. To do this, follow these instructions:

* Click on the Wifi icon in your menu bar at the top of the screen and select Create Network from the drop-down menu 

* Give your network a name (innovid-multiscreen is a nice name). Set a password if you're feeling insecure :)

* Wait a sec and your network should be setup. 

* On your other devices, have them connect to this network, either throught the wifi drop-down on a Macbook or through Settings > Wi-Fi > Devices on an iOS device

### Loading Apps
* Once your iOS device has connected, click on the info icon to get your devices IP address. You will need this info when loading the master app for sending/receiving OSC messages

* On the master computer, load the innovidVideoPlayerMasterDebug app with that IP address (for now you need to recompile the app...could be done in a settings file or set up static IP or something you enter on the screen. either way there needs a solution for this!)

* On the iOS devices, load their respective innovidVideoPlayerClient app

* If everything is working correctly, you should have temporally synched video!

### Gracefully exiting apps
* To think about...

Resources
----
[Innovid Dropbox]

Links to related repositories
----
[iPhone CLIENT]

[iPhone CLIENT]: https://github.com/jdiedrick/innovidMultiscreenDisplayAppiPhoneClient

[Innovid Dropbox]: https://www.dropbox.com/home/Innovid
