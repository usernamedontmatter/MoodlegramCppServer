# Moodlegram server
## Project
This project is server part of Moodlegram

API version: 1.0.0

Server API version: 1.0.0

Server version: 1.0.1


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

IOStream types:
* TCPStream. IO by pure tcp

### IOStreamCreator

IOStreamCreator class generate iostreams

IOStreamCreatorConcept - concept of class that generate streams

IOStreamCreator types:
* TCPStreamCreator. Create TCPStream

### EncryptingLayout

EncryptingLayout is iostream class which is based on other iostream and encrypts traffic

EncryptingLayoutInterface - interface of layout

EncryptingLayout types:
* NoEncryptingLayout. No encrypting

### Server

Server class is base application class that run moodlegram server
