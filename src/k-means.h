//	
//	Created by:	Sujit S Ahirrao
//

#ifndef K_MEANS_H
#define K_MEANS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <limits>

class KMeans
{
// private members
	// Dimension of each data-point/sample/observation from the input data
	int dataPointDim;

	// Number of clusters to be created - provided by the user
	int numberOfClusters;

	// Flag to check if the dimension of each data-point is found or not
	bool foundDataPointDim;

	// Input data provided by the user
	std::vector<std::vector<float> > inputData;

	// Centroids of cluster
	std::vector<std::vector<float> > centroids;

	// Array repesenting which data-point is assigned to which cluster
	std::vector<int> assignedClusters;

	// To initialize the centroids of the clusters to different data-points from the input data
	// using the number of data-points and clusers provided by the user
	void initCentroids();

	// To Calculate the Euclidean distance between centroid vector and data-point vector
	float getEuclideanDistance(std::vector<float> sample, std::vector<float> centroid);

	// To assign the data-point to one of the clusters 
	// based on minimum distance between centroid and the data-point
	void assignClusters();

	// To calculate the means as centroids of the new clusters
	void updateCentroids();

	// Destructor
	~KMeans();

// public members
public:
	// Constructor
	KMeans();

	// To start k-means clustering for input data
	void process(char* argv[]);

	// Setter example
	void setNumberOfClusters(int numberOfClusters);
	
	// Getter example
	int getNumberOfClusters();
};

#endif K_MEANS_H
