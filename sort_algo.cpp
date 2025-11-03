#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using std::cout;
using std::endl;
using std::atoi;
using std::cin;

class Sort {
private:
    std::vector<int> minmax(std::vector<int> arr) {
        int min = INT_MAX, max = INT_MIN;
        for (auto i : arr) {
            if (i < min) min = i;
            if (i > max) max = i;
        }
        return {min, max};
    }
    
    std::vector<int> counting_sort_subroutine(std::vector<int> arr, int exp, int base) {
        int n = arr.size();
        std::vector<int> frequency(base, 0);
        std::vector<int> sorted(n);

        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % base;
            frequency[digit]++;
        }

        for (int i = 1; i < base; i++) {
            frequency[i] += frequency[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % base;
            sorted[frequency[digit] - 1] = arr[i];
            frequency[digit]--;
        }

        return sorted;
    }
    
    std::vector<int> insertion_sort_subroutine(std::vector<int> arr) {
		int n = arr.size();
		for (int i = 1; i < n; i++) {
			int key = arr[i];
			int j = i - 1;
			
			while (j >= 0 && key < arr[j]) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
		return arr;
	}
	
	void merge(std::vector<int>& arr, int start, int middle, int end) {
		int n1 = middle - start + 1;
		int n2 = end - middle;
		
		std::vector<int> V1(arr.begin() + start, arr.begin() + middle + 1);
		std::vector<int> V2(arr.begin() + middle + 1, arr.begin() + end + 2);
	
		
		
		int i = 0, j = 0, k = start;
		while (i < n1 && j < n2) {
			if (V1[i] <= V2[j]) {
				arr[k] = V1[i];
				i++;
			}
			else {
				arr[k] = V2[j];
				j++;
			}
			k++;
		}
		while (i < n1) {
			arr[k] = V1[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = V2[j];
			j++;
			k++;
		}
	}
	
	void heapify(std::vector<int>& arr, int n, int i, bool min) {
		int keyNode = i;
		
		int leftChild = 2 * i + 1;
		int rightChild = 2 * i + 2;
		
		if (min) {
			if (leftChild < n && arr[leftChild] < arr[keyNode]) {
				keyNode = leftChild;
			}
		
			if (rightChild < n && arr[rightChild] < arr[keyNode]) {
				keyNode = rightChild;
			}
		}
		else {
			if (leftChild < n && arr[leftChild] > arr[keyNode]) {
				keyNode = leftChild;
			}
		
			if (rightChild < n && arr[rightChild] > arr[keyNode]) {
				keyNode = rightChild;
			}
		}
		
		if (keyNode != i) {
			int temp = arr[i];
			arr[i] = arr[keyNode];
			arr[keyNode] = temp;
			
			heapify(arr, n, keyNode, min);
		}
	}
	int partition(std::vector<int>& arr, int start, int end) {
		int pivot = arr[end];
		int i = start - 1;
		
		for (int j = start; j < end; j++) {
			if (arr[j] < pivot) {
				std::swap(arr[j], arr[++i]);
			}
		} 
		std::swap(arr[++i], arr[end]);
		return i;
	}

public:
	// Constructor to choose algo based on elements
	Sort(std::vector<int> arr) {
		// Use couting sort when data is "cramped" and "range is small" 
		// Will do soon
	}
    
    std::vector<int> counting_sort(std::vector<int> arr) {
        std::vector<int> mima = minmax(arr);
        int min = mima[0], max = mima[1];
        int k = max - min, n = arr.size();
        std::vector<int> frequency(k + 1, 0);
        std::vector<int> sorted_list(n);

        for (auto i : arr) {
            frequency[i - min]++;
        }

        for (int i = 1; i <= k; i++) {
            frequency[i] += frequency[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int pos = arr[i] - min;
            sorted_list[frequency[pos] - 1] = arr[i];
            frequency[pos]--;
        }

        return sorted_list;
    }
    
    std::vector<int> radix_sort(std::vector<int> arr, int base = 10) {
        if (arr.empty()) return arr;

        std::vector<int> mima = minmax(arr);
        int maxVal = mima[1], minVal = mima[0];
        
        if (minVal < 0) {
            cout << "Elements should be positive!" << endl;
            return {};
        }

        int digits = (maxVal == 0) ? 1 : (std::floor(std::log(maxVal) / std::log(base)) + 1);

        std::vector<int> sorted_arr = arr;
        int exp = 1;
        for (int i = 0; i < digits; i++) {
            sorted_arr = counting_sort_subroutine(sorted_arr, exp, base);
            exp *= base;
        }

        return sorted_arr;
    }
    
    std::vector<int> bucket_sort(std::vector<int> arr) {
		int n = arr.size();
		if (arr.empty()) return arr;

        std::vector<int> mima = minmax(arr);
        int maxVal = mima[1], minVal = mima[0];
        std::vector<int> sorted_arr;
        
        if (minVal < 0) {
            cout << "Elements should be positive!" << endl;
            return {};
        }
        
        std::vector<std::vector<int>> bucket(n);
        for (auto i: arr) {
			double normalized = (double)i / (maxVal + 1);
			int bucket_no = n*normalized;
			bucket[bucket_no].push_back(i);
		}
		
		for (int i = 0; i < n; i++) {
			bucket[i] = insertion_sort_subroutine(bucket[i]);
			sorted_arr.insert(sorted_arr.end(), bucket[i].begin(), bucket[i].end());
		}
		return sorted_arr;
	}
	
	void merge_sort(std::vector<int>& arr, int start, int end) {
		if (start >= end) {
			return;
		}
		
		int middle = (start + end)/2;
		
		merge_sort(arr, start, middle);
		merge_sort(arr, middle + 1, end);
		merge(arr, start, middle, end);
	}
	
	std::vector<int> heapSort(std::vector<int> arr, int n, bool min = true) {
		std::vector<int> sorted;
		sorted.reserve(n);
		for (int i = n / 2 - 1; i >= 0; i--) {
			heapify(arr, n, i, min);
		}
	
		for (int i = n - 1; i >= 0; i--) {
			sorted.push_back(arr[0]);
			arr[0] = arr[i];
			arr[i] = min ? INT_MAX : INT_MIN;
		
			heapify(arr, i, 0, min);
		}
	
		return sorted;
	}
	void quickSort(std::vector<int>& arr, int start, int end) {
		if (end <= start) return;
		int pivot = partition(arr, start, end);
		quickSort(arr, start, pivot - 1);
		quickSort(arr, pivot + 1, end);
	}
};


int main(int argc, char** argv) {
    Sort sort;
    std::vector<int> arr;
    
    if (argc <= 1) {
        cout << "This Program accepts command line args (give array elements)" << endl;
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        arr.push_back(atoi(argv[i]));
    }
    
    // Choose which algo is suitable based on data -- TODO
	
    cout << "Sorted Array: ";
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
