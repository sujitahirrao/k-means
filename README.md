# k-means
Implementation of k-means clustering algorithm in C++ on Linux and Windows

It takes input file (e.g. src/points.txt) containing samples to be clusters and the number of clusters to be created.
It results the output file (e.g. clusters.txt) containing centroids of the clusters created.

	Instructions to run:
	Windows:
		Requirements:
			g++/gcc >= 4.8.4
		commands: 
			cd <this_repository>\src\
			g++ -std=c++11 main.cpp k-means.cpp -o ..\build\k-means.exe
			cd ..\build\
			k-means.exe <input_file> <number_of_clusters>

	Linux:
		Requirements:
			g++/gcc >= 4.8.4
		Commands:
			cd <this_repository>/src/
			g++ -std=c++11 main.cpp k-means.cpp -o ..\build\k-means
			cd ../build/
			./k-means <input_file> <number_of_clusters>

		OR
		Requirements:
			g++/gcc >= 4.8.4, cmake >= 2.8
		Commands:
			cd <this_repository>/build
			cmake ..
			make
			./k-means <input_file> <number_of_clusters>
    
