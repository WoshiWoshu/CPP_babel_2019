# CPP_babel_2019
3rd year project in C++ in which the goal is to implement a software server/client Voice Over IP protocole similar to skype or  TeamSpeak. More precisely it is a chatting voice software that can be use for any purpose between colleagues, friends and teammates.
The software is usable over the internet and uses a binary protocole for voice transport from client to client. The server is the core, it process and allocate informations between clients.
The server network side is implemented using "Boost Asio",  uses "PortAudio3 for sound + voice processing and "Opus" for compression codec.
The client side uses "Qt Network" and "Qt" respectively for the network and graphical implementation. In addition there is a list of contacts (to add and delete people), and there are call, hang up and mute functionalities. However it is not possible to make a group call, there no id/register portal and thus the DataBase using "sqlite3" doesn't work properly for storing client + contact list.
The project is OS independent, and compile using "Cmake" on linux + windows. The dependencies are handled using "Conan".

PREREQUISITES :

Conan, Qt, Opus, PortAudio3, sqlite3 must be installed.

USAGE : 

1) mkdir build && cd build && conan install .. && cmake .. -G “Unix Makefiles” && cmake –build .

2) ./babel_client, + ./babel_server
