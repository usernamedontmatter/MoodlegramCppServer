# Moodlegram server
## Project
This project is server part of Moodlegram

## Moodlegram

Moodlegram is an opensource messanger specializing on security, privacy and fault tolerance

[Tmaou27](https://github.com/Tmaou27) is author of original Moodlegram

[MoodlegramModel](https://github.com/Tmaou27/MoodlgramModel) is original Moodlegram project

## Run

To run compile CMakeLists.txt

## Structure

### Database

Database class control data storage

DatabaseConcept - concept of database

Database types:
* TempDatabase. Database that storage data on runtime memory

### Auth

Auth class control user authentication

AuthData - types of data that must be store in database for authentication
AuthConcept - concept of Auth class

Auth types:
* NoAuth. No auth

### IOStream

IOStream class control input-output operations

IOStreamConcept - concept of iostream
IOStreamCreatorConcept - concept of class that generate streams

IOStream types:
* TCPStream. IO by pure tcp

### EncryptingLayout

EncryptingLayout is iostream class which is based on other iostream and encrypts traffic

EncryptingLayoutInterface - interface of layout

EncryptingLayout types:
* NoEncryptingLayout. No encrypting

### Server

Server class is base application class that run moodlegram server
