compile:
	g++ -std=c++11 -pthread Knn.cpp StreamFiles.cpp VectorDistance.cpp CLI.cpp Command.cpp DefaultIO.cpp Server.cpp -o server.out
	g++ -std=c++11 -pthread newclient.cpp -o client.out