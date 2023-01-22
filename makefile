compile:
	g++ -std=c++11 -fdiagnostics-color=always -g -pthread Knn.cpp StreamFiles.cpp VectorDistance.cpp CLI.cpp Command.cpp DefaultIO.cpp Server.cpp -o server.out
	g++ -std=c++11 -fdiagnostics-color=always -g newclient.cpp -o client.out