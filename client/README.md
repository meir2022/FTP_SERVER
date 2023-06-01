********** To compile and run it just run the make command ***************

The purpose of the client-side is to establish a connection with a server,
and allow users to perform various actions such as:
listing files, uploading files, and downloading files.

The code prompts the user for input their name and password (which define in users.txt few tests),
then allows them to select an action:
list, upload, download, (also works for capital letters).

the program performs the corresponding operation by sending/receiving data to/from the server.
The client-side code uses sockets for network communication and interacts 
with the server based on the user's input.

The main (client.c) uses file_handler module for sending/ receiving files.

(for functions documentation, see in the header file)

