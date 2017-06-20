//	
//	Created by:	Sujit Ahirrao
//

#include "k-means.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Checking the number of arguments
    if(argc != 3)
	{
		cout << "\nIncorrect number of arguments!" << endl;
		cout << "Usage:\t" << argv[0] << " <input_file_path> <number_of_clusters>" << endl;
		return 1;
	}

	KMeans *kMeans = new KMeans();

	// Example of Getter and Setter - to update the private member through public member
	kMeans->setNumberOfClusters(stoi(argv[2]));

	// Start k-means clustering for input data
	kMeans->process(argv);

	return 0;
}