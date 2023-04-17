<h1>CPP TCP server and client<</h1>
<br />
Compile command:            make <br />
For running the server use: ./server.out [port] <br />
For running the client use: ./client.out [ip] [port] <br />

The menu and function of the project: <br />
<br />
1. upload an uncalssified csv data file <br />
2. algorithm settings <br />
3. classify data <br />
4. display results <br />
5. download results <br />
8. exit <br />
<br />
this project create server and client using TCP. <br />
the server can serve multiple user at the same time by using thread <br />
Project Design pattern: CLI <br />
using command for each option <br />
using SocketIO send and write messege  <br />

flow:
server get port as a argument and bind the ip address and port to a socket. <br />
For each new client the server create new thread and CLI for this client.  <br />
The CLI create the 6 commands of the menu and save them in vector of commands  <br />
CLI.start run the menu and get from the user input and execute the user input index in the vector<command>  <br />


