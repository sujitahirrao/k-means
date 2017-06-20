//	
//	Created by:	Sujit S Ahirrao
//

#include "k-means.h"

using namespace std;

KMeans::KMeans()
{
	dataPointDim = 0;
	numberOfClusters = 0;
	foundDataPointDim = false;
}

void KMeans::setNumberOfClusters(int numberOfClusters)
{
	// Use of 'this' keyword
	this->numberOfClusters = numberOfClusters;
	return;
}

int KMeans::getNumberOfClusters()
{
	return numberOfClusters;
}

void KMeans::initCentroids()
{
	int step = inputData.size()/numberOfClusters;
	for(int i = 0; i < numberOfClusters; i++)
		centroids.push_back(inputData[i*step]);

	/*cout << endl << "Initialized centroids: " << endl;
	for(int i = 0; i < numberOfClusters; i++)
	{
		for(int j = 0; j < dataPointDim; j++)
			cout << centroids[i][j] << " ";
		cout << endl;
	}*/

	return;
}

float KMeans::getEuclideanDistance(std::vector<float> sample, std::vector<float> centroid)
{
	float euclideanDistance = 0.0;
	for(int i = 0; i < dataPointDim; i++)
		euclideanDistance += pow(centroid[i] - sample[i], 2);

	return sqrt(euclideanDistance);
}

void KMeans::assignClusters()
{
	std::vector<int> assignedClustersPrev = assignedClusters;
	do
	{
		assignedClustersPrev = assignedClusters;
		for(int i = 0; i < inputData.size(); i++)
		{
			float minDistance = std::numeric_limits<float>::max();
			for(int j = 0; j < numberOfClusters; j++)
			{
				float euclideanDistance = getEuclideanDistance(inputData[i], centroids[j]);
				if(euclideanDistance < minDistance)
				{
					assignedClusters[i] = j;
					minDistance = euclideanDistance;
				}
			}
		}

		/*cout << endl << "assignedClusters: " << endl;
		for(int j = 0; j < assignedClusters.size(); j++)
			cout << assignedClusters[j] << " ";
		cout << endl;*/

		updateCentroids();

	// Keep updating until assignedClusters is not updating
	} while(assignedClustersPrev != assignedClusters);

	return;
}

void KMeans::updateCentroids()
{
	for(int i = 0; i < numberOfClusters; i++)
	{
		int clusterPointsCount = 0;
		vector<vector<float> > clusterPoints;

		// Counting the number of data-points assigned to current cluster
		for(int j = 0; j < assignedClusters.size(); j++)
		{
			if(assignedClusters[j] == i)
			{
				++clusterPointsCount;
				clusterPoints.push_back(inputData[j]);
			}
		}

		// Calculating the mean as new centroid
		for(int j = 0; j < dataPointDim; j++)
		{
			float sum = 0.0;
			for(int k = 0; k < clusterPoints.size(); k++)
				sum += clusterPoints[k][j];
			centroids[i][j] = sum/clusterPointsCount;
		}
	}

	/*cout << endl << "Updated Clusters: " << endl;
	for(int i = 0; i < numberOfClusters; i++)
	{
		for(int j = 0; j < dataPointDim; j++)
			cout << centroids[i][j] << " ";
		cout << endl;
	}*/

	return;
}

void KMeans::process(char* argv[])
{
	// Opening the input file for reading input data
	ifstream inputFile;
	inputFile.open(argv[1]);

	// Opening the output file for writing centroids
	ofstream outputFile;
	outputFile.open("clusters.txt");

	// Leaving output file empty for 0 number of clusters
	if(numberOfClusters == 0)
	{
		cout << endl << "Number of clusters provided is 0." << endl;
		cout << "Created empty output file." << endl;
	}
	else if(inputFile.is_open())
	{
		string line;
		// Reading input file line by line
		while(getline(inputFile, line))
		{
			//cout << line << endl;
			istringstream iss(line);

			// To find the size of single input data-point (vector)
			int counter = 0;
			float value;

			// Single input data-point (vector)
			vector<float> inputDataPoint;
			while(iss >> value)
			{
				//cout << value << endl;
				inputDataPoint.push_back(value);
				++counter;
			}

			// Skipping the empty lines
			if(counter == 0)	
				continue;

			if(!foundDataPointDim)
			{
				dataPointDim = counter;
				foundDataPointDim = true;
			}
			else if(counter != dataPointDim)
			{
				cout << "\nInput data size is not same throughout the data." << endl;
				inputFile.close();
				outputFile.close();
				return;
			}
			inputData.push_back(inputDataPoint);
		}

		/*cout << endl << "Input data:" << endl;
		for(int i = 0; i < inputData.size(); i++)
		{
			for(int j = 0; j < dataPointDim; j++)
				cout << inputData[i][j] << " ";
			cout << endl;
		}*/

		// Setting the size of assignedClusters vector same as number of input data-points
		assignedClusters.resize(inputData.size(), 0);

		if(inputData.size() < numberOfClusters)
		{
			cout << "\nInput data size can not be less than the number of clusters." << endl;
			inputFile.close();
			outputFile.close();
			return;
		}
		// Copying input data to output if number of clusters expected is same as size of input data
		else if(inputData.size() == getNumberOfClusters())
		{
			inputFile.clear();
			inputFile.seekg(0, ios::beg);
			string line;
			while(getline(inputFile, line))
				outputFile << line << endl;
		}
		else
		{
			initCentroids();
			assignClusters();
			for(int i = 0; i < numberOfClusters; i++)
			{
				for(int j = 0; j < dataPointDim; j++)
					outputFile << setprecision(2) << fixed << centroids[i][j] << " ";
				outputFile << endl;
			}
		}
	}
	else
		cout << "\nError in opening the file." << endl;
	
	inputFile.close();
	outputFile.close();

	return;
}
