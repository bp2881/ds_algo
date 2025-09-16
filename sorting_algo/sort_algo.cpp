#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::atoi;

class Sort {
private:
    vector<int> minmax(vector<int> arr) {
        int min = INT_MAX, max = INT_MIN;
        for (auto i : arr) {
            if (i < min) min = i;
            if (i > max) max = i;
        }
        return {min, max};
    }
    
    vector<int> counting_sort_subroutine(vector<int> arr, int exp, int base) {
        int n = arr.size();
        vector<int> frequency(base, 0);
        vector<int> sorted(n);

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
    
    vector<int> insertion_sort_subroutine(vector<int> arr) {
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

public:
    vector<int> counting_sort(vector<int> arr) {
        vector<int> mima = minmax(arr);
        int min = mima[0], max = mima[1];
        int k = max - min, n = arr.size();
        vector<int> frequency(k + 1, 0);
        vector<int> sorted_list(n);

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
    
    vector<int> radix_sort(vector<int> arr, int base = 10, char sub_routine = 'c') {
        if (arr.empty()) return arr;

        vector<int> mima = minmax(arr);
        int maxVal = mima[1], minVal = mima[0];
        
        if (minVal < 0) {
            cout << "Elements should be positive!" << endl;
            return {};
        }

        int digits = (maxVal == 0) ? 1 : (std::floor(std::log(maxVal) / std::log(base)) + 1);

        vector<int> sorted_arr = arr;
        int exp = 1;
        for (int i = 0; i < digits; i++) {
            sorted_arr = counting_sort_subroutine(sorted_arr, exp, base);
            exp *= base;
        }

        return sorted_arr;
    }
    
    vector<int> bucket_sort(vector<int> arr) {
		int n = arr.size();
		if (arr.empty()) return arr;

        vector<int> mima = minmax(arr);
        int maxVal = mima[1], minVal = mima[0];
        vector<int> sorted_arr;
        
        if (minVal < 0) {
            cout << "Elements should be positive!" << endl;
            return {};
        }
        
        vector<vector<int>> bucket(n);
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
};

int main(int argc, char** argv) {
    Sort sort;
    vector<int> arr;
    
    if (argc <= 1) {
        cout << "This Program accepts command line args (give array elements)" << endl;
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        arr.push_back(atoi(argv[i]));
    }
    
    vector<int> sorted_arr = sort.bucket_sort(arr);
    cout << "Sorted Array: ";
    for (auto i : sorted_arr) {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
