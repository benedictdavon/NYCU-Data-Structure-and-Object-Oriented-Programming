#include "sort.h"

void sort::process(const char* fileName) {
	// read file
	ifstream FileInput;
	FileInput.open(fileName);

	if (!FileInput) {
		cout << "File open fail!!" << endl;
	}
	char c;
	string line;
	while ((c = FileInput.get()) != EOF) {
		FileInput.get();
		if (c == '0') {  //Do the insertion sort
			getline(FileInput, line, ' ');
			bool isBinary = (stoi(line) == 0) ? false : true;
			getline(FileInput, line, ' ');
			int length_ins = stoi(line);
			getline(FileInput, line);
			int target = stoi(line);

			for (int i = 0; i < length_ins; i++) {
				if (i == length_ins - 1)
					getline(FileInput, line);
				else
					getline(FileInput, line, ' ');
				insertion.push_back(stoi(line)); //Insert the number to the insertion vector
			}
			InsertionSort(); //Run the insertion sort
			if (isBinary) BinarySearch(0, target); //Whether do the binary search
			else cout << endl;
			insertion.clear();
		}
		else if (c == '1') { //Do the bucket sort
			getline(FileInput, line, ' ');
			bool isBinary = (stoi(line) == 0) ? false : true;
			getline(FileInput, line, ' ');
			int length_buc = stoi(line);
			getline(FileInput, line);
			int target = stoi(line);

			for (int i = 0; i < length_buc; i++) {
				if (i == length_buc - 1)
					getline(FileInput, line);
				else
					getline(FileInput, line, ' ');
				bucket.push_back(stoi(line)); //Insert the number to the bucket vector
			}
			BucketSort();  //Run the bucket sort
			if (isBinary) BinarySearch(1, target);  //Whether do the binary search
			else cout << endl;
			bucket.clear();
		}
	}
	FileInput.close();
}

void sort::InsertionSort() {
	//TODO:
	//Use the insert vector to perform insertion sort.
	int index = 0, key = 0;
	for (int i = 1; i < insertion.size(); i++) {
		key = insertion[i];
		index = i - 1;

		while (index >= 0 && insertion[index] > key) {
			insertion[index + 1] = insertion[index];
			index--;
		}

		insertion[index + 1] = key;
	}
	output(0, 0); //print the result after the insertion sort
}

void sort::BucketSort() {
	//TODO:
	//Use the bucket vector to perform bucket sort.
	//Note: Don't forget to print the result at each round end.
	int largest = 0;

	for (int i = 0; i < bucket.size(); i++) {
		if (bucket[i] > largest)
			largest = bucket[i];
	}

	int length = 0;
	while (largest > 0) {
		length++;
		largest /= 10;
	}
	
	vector< vector< int > > ans(length+1, vector<int>(0, 0));
	reverse(bucket.begin(), bucket.end());
	ans[0] = bucket;
	int num, fill = 0;
	for (int i = 1; i <= length; i++) {
		cout << i << " : ";
		for (int j = 0; j < 10; j++) {
			//cout <<"bucket[j]: " << bucket[j] << " num: " << num << endl;
			for (int k = 0; k < bucket.size(); k++) {
				num = ans[i-1][k] / (int)pow(10, i-1) % 10;
				if (j == num) {
					ans[i].push_back(ans[i-1][k]);
				}
			}
		}

		for (auto element : ans[i]) {
				cout << element << " ";
		}
		cout << endl;
	}
	bucket = ans[length];
}

int getBinarySearch(vector <int> num, int start, int end, int target) {
	int mid = start + (end - start) / 2;

	if (end >= 1){
		cout << num[mid] << " ";
		if (num[mid] == target) {
			
			return mid;
		}

		if (num[mid] > target)
			return getBinarySearch(num, start, mid - 1, target);

		return getBinarySearch(num, mid + 1, end, target);
	}

	return -1;
}
	
}

void sort::BinarySearch(int number, int target) {
	//TODO:
	//number = 0 means that use the insertion vector to find the target
	//number = 1 means that use the bucket vector to find the target
	//target means that we want to find the number.
	vector <int> temp;
	temp = number == 0 ? insertion : bucket;
	int start = 0, end = temp.size();

	cout << "Searching: ";
	
	if (getBinarySearch(temp, start, end, target) != -1) {
		cout << "Found" << endl;
		return;
	}
	cout << "Not Found" << endl;
}

void sort::output(int number, int round) {
	if (number == 0) {
		cout << "Insertion Sort : ";
		//TODO:  output the insertion sort result
		for (int i = 0; i < insertion.size(); i++) {
			cout << insertion[i] << " ";
		}
		cout << endl;
	}
	else {
		if (round == 1) cout << "Bucket Sort" << endl;
		cout << round << " : ";
		//TODO: output the bucket sort result each round
		for (int i = 0; i < bucket.size(); i++) {
			cout << bucket[i] << " ";
		}
		cout << endl;
	}
}
