compile:
	g++ -std=c++11 AlgoRun.cpp Knn.cpp newserver.cpp StreamFiles.cpp VectorDistance.cpp -o server.out
	g++ -std=c++11 newclient.cpp -o client.out