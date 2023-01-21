compile:
	g++ -std=c++11 -pthread Knn.cpp Server.cpp StreamFiles.cpp VectorDistance.cpp CLI.cpp Command.cpp DefaultIO.cpp -o server.out
	g++ -std=c++11 newclient.cpp -o client.out