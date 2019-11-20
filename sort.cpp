/*******************************************************************************
 * Name    : sort.cpp
 * Author  : Ryan Perretta
 * Version : 2.5
 * Date    : October 16, 2019
 * Description : Counting Sort algorithm.
 ******************************************************************************/
 
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <time.h>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int size;
long swap_count = 0, comparisons = 0;

//REVERSE
int* reverse(int* nums){
	int rightswap = size-1;
		for(int i = 0; i < size/2; i++){
			swap(nums[i], nums[rightswap]);
			rightswap--;
		}
	return nums;
}
//COUNT SORT//
int* countsort(int *nums){
	//finds max and min and passes it to the countsort function above
	int hi = nums[0], lo = nums[0];
	for(int i = 1; i < size; i++){
		if(nums[i] < lo){
			lo = nums[i];
			comparisons++;
		} else if(nums[i] > hi){
			hi = nums[i];
			comparisons+=2;
		} else {
			comparisons+=2;
		}
	}
	//creates array, size equal to range of unsorted array
	int *counts = new int[hi-lo+1];	
	//fills array with 0's
	for(int i = 0; i < hi-lo+1; i++){
		counts[i] = 0;
	}
	//counts each instance of a number in the unsorted array
	for(int i = 0; i < size; i++){
		counts[nums[i] - lo]++;
	}
	
	int index = 0;
	//fills the nums array with the original values in sorted order
	for(int i = 0; i < hi-lo+1; i++){
		//adds number to sorted array until count[i] = 0
		while(counts[i] > 0){
			nums[index] = i + lo;
			counts[i]--;
			index++;
		}
	}
	
	delete[] counts;
	
	return nums;
}
//END COUNT SORT//


//SELECTION SORT//
int* selection_sort(int *nums){
	for(int i = 0; i < size; i++){
		int lo = i;
		for(int j = i; j < size; j++){
			if(nums[j] < nums[lo]){
				lo = j;
			}
			comparisons++;
		}
		swap(nums[i], nums[lo]);
		swap_count++;
	}
	return nums;
}
//END SELECTION SORT//

//REVERSE SELECTION SORT//
int* reverse_selection_sort(int *nums){
	for(int i = 0; i < size; i++){
		int hi = i;
		for(int j = i; j < size; j++){
			if(nums[j] > nums[hi]){
				hi = j;
			}
			comparisons++;
		}
		swap(nums[i], nums[hi]);
		swap_count++;
	}
	return nums;
}
//END REVERSE SELECTION SORT//

//BUBBLE SORT//
int* bubble_sort(int *nums){
	int swaps = 1;
	for(int i = 0; i < size and swaps != 0; i++){
		swaps = 0;
		for(int j = 0; j < size-(i+1); j++){
			if(nums[j+1] < nums[j]){
				swap(nums[j+1],nums[j]);
				swaps++;
				swap_count++;
			}
			comparisons++;
		}
	}
	return nums;
}
//END BUBBLE SORT//

//BUBBLE REVERSE//
int* reverse_bubble_sort(int *nums){
	int swaps = 1;
	for(int i = 0; i < size and swaps != 0; i++){
		swaps = 0;
		for(int j = 0; j < size-(i+1); j++){
			if(nums[j+1] > nums[j]){
				swap(nums[j+1],nums[j]);
				swaps++;
				swap_count++;
			}
			comparisons++;
		}
	}
	return nums;
}
//END BUBBLE REVERSE//

//COCKTAIL SHAKER SORT//
int* cocktail_shaker_sort(int *nums){
	int swaps = 1, left = 0, right = size-1;
	for(int i = 0; i < size and swaps != 0; i++){
		swaps = 0;
		int j;
		for(j = left; j < right; j++){
			if(nums[j+1] < nums[j]){
				swap(nums[j+1],nums[j]);
				swaps++;
				swap_count++;
			}
			comparisons++;
		}
		if(swaps == 0){
			comparisons++;
			break;
		}
		right--;
		for(int k = right; k > left; k--){
			if(nums[k] < nums[k-1]){
				swap(nums[k],nums[k-1]);
				swaps++;
				swap_count++;
			}
			comparisons++;
		}
		left++;
	}
	return nums;
}
//END COCKTAIL SHAKER SORT//

//REVERSE COCKTAIL SHAKER SORT//
int* reverse_cocktail_shaker_sort(int *nums){
	int swaps = 1, left = 0, right = size-1;
	for(int i = 0; i < size and swaps != 0; i++){
		swaps = 0;
		int j;
		for(j = left; j < right; j++){
			if(nums[j+1] > nums[j]){
				swap(nums[j+1],nums[j]);
				swaps++;
				swap_count++;
			}
			comparisons++;
		}
		if(swaps == 0){
			comparisons++;
			break;
		}
		right--;
		for(int k = right; k > left; k--){
			if(nums[k] > nums[k-1]){
				swap(nums[k],nums[k-1]);
				swaps++;
				swap_count++;
			}
			comparisons++;
		}
		left++;
	}
	return nums;
}
//END REVERSE COCKTAIL SHAKER SORT//

//INSERTION SORT//
int* insertion_sort(int *nums){
	for(int i = 0; i < size-1; i++){
		for(int j = i+1; j > 0; j--){
			if(nums[j] < nums[j-1]){
				swap(nums[j], nums[j-1]);
				swap_count++;
			}
			comparisons++;
		}
	}
	return nums;
}
//END INSERTION SORT//

//REVERSE INSERTION SORT//
int* reverse_insertion_sort(int *nums){
	for(int i = 0; i < size-1; i++){
		for(int j = i+1; j > 0; j--){
			if(nums[j] > nums[j-1]){
				swap(nums[j], nums[j-1]);
				swap_count++;
			}
			comparisons++;
		}
	}
	return nums;
}
//END REVERSE INSERTION SORT//

//GNOME SORT//
int* gnome_sort(int *nums){
	int pos = 0;
	while(pos != size-1){
		if(nums[pos] > nums[pos+1]){
			swap(nums[pos], nums[pos+1]);
			swap_count++;
			if(pos != 0){
				pos--;
			}
		} else {
			pos++;
		}
		comparisons++;
	}
	return nums;
}
//END GNOME SORT//

//REVERSE GNOME SORT//
int* reverse_gnome_sort(int *nums){
	int pos = 0;
	while(pos != size-1){
		if(nums[pos] < nums[pos+1]){
			swap(nums[pos], nums[pos+1]);
			swap_count++;
			if(pos != 0){
				pos--;
			}
		} else {
			pos++;
		}
		comparisons++;
	}
	return nums;
}
//END REVERSE GNOME SORT//

//RADIX SORT//
int* radix_sort(int *nums){
	
	return nums;
}
//END RADIX SORT//

//ODD/EVEN SORT//
int* odd_even_sort(int *nums){
	bool sorted;
	
	do{
		sorted = true;
		
		for(int i = 1; i < size-1; i+=2){
			if(nums[i] > nums[i+1]){
				swap(nums[i], nums[i+1]);
				sorted = false;
				swap_count++;
			}
			comparisons++;
		}
		for(int i = 0; i < size-1; i+=2){
			if(nums[i] > nums[i+1]){
				swap(nums[i], nums[i+1]);
				sorted = false;
				swap_count++;
			}
			comparisons++;
		}
		
	}while(!sorted);
	
	return nums;
}
//END ODD/EVEN SORT//

//REVERSE ODD/EVEN SORT//
int* reverse_odd_even_sort(int *nums){
	bool sorted;
	
	do{
		sorted = true;
		
		for(int i = 1; i < size-1; i+=2){
			if(nums[i] < nums[i+1]){
				swap(nums[i], nums[i+1]);
				sorted = false;
				swap_count++;
			}
			comparisons++;
		}
		for(int i = 0; i < size-1; i+=2){
			if(nums[i] < nums[i+1]){
				swap(nums[i], nums[i+1]);
				sorted = false;
				swap_count++;
			}
			comparisons++;
		}
		
	}while(!sorted);
	
	return nums;
}
//END REVERSE ODD/EVEN SORT//

//STOOGE SORT//
int* stooge_sort(int *nums, int lo, int hi){
	
	if(lo == hi){
		comparisons++;
		return nums;
	}
	comparisons++;
	
	if(nums[lo] > nums[hi]){
		swap(nums[lo], nums[hi]);
		swap_count++;
	}
	comparisons++;
	
	if(hi-lo+1 > 2){
		int x = (hi-lo+1)/3;
		nums = stooge_sort(nums, lo, hi-x);
		nums = stooge_sort(nums, lo+x, hi);
		nums = stooge_sort(nums, lo, hi-x);
	}
	comparisons++;
	
	return nums;
}

int* reverse_stooge_sort(int *nums, int lo, int hi){
	
	if(lo == hi){
		comparisons++;
		return nums;
	}
	comparisons++;
	
	if(nums[lo] < nums[hi]){
		swap(nums[lo], nums[hi]);
		swap_count++;
	}
	comparisons++;
	
	if(hi-lo+1 > 2){
		int x = (hi-lo+1)/3;
		nums = stooge_sort(nums, lo, hi-x);
		nums = stooge_sort(nums, lo+x, hi);
		nums = stooge_sort(nums, lo, hi-x);
	}
	comparisons++;
	
	return nums;
}

int* stooge_sort(int *nums, string direction){
	if (direction.compare("a") == 0){
		return stooge_sort(nums, 0, size-1);
	} else {
		return reverse_stooge_sort(nums, 0, size-1);
	}
}
//END STOOGE SORT//

//COMB SORT//
int* comb_sort(int *nums){
	
	int comb_size = size;
	bool swaps = true;
	
	while(comb_size != 1 or swaps){
		swaps = false;
		
		comb_size = (comb_size*10)/13;
		if(comb_size < 1){
			comb_size = 1;
		}
		comparisons++;
		
		for(int i = 0; i < size-comb_size; i++){
			if(nums[i] > nums[i+comb_size]){
				swaps = true;
				swap(nums[i], nums[i+comb_size]);
				swap_count++;
			}
			comparisons++;
		}
		
	}
	
	return nums;
}
//END COMB SORT//

//REVERSE COMB SORT//
int* reverse_comb_sort(int *nums){
	
	int comb_size = size;
	bool swaps = true;
	
	while(comb_size != 1 or swaps){
		swaps = false;
		
		comb_size = (comb_size*10)/13;
		if(comb_size < 1){
			comb_size = 1;
		}
		comparisons++;
		
		for(int i = 0; i < size-comb_size; i++){
			if(nums[i] < nums[i+comb_size]){
				swaps = true;
				swap(nums[i], nums[i+comb_size]);
				swap_count++;
			}
			comparisons++;
		}
		
	}
	
	return nums;
}
//END REVERSE COMB SORT//

//GRAVITY SORT//
int* gravity_sort(int *nums){
	int max = nums[0];
	for(int i = 1; i < size; i++){
		if (nums[i] > max){
			max = nums[i];
		}
		comparisons++;
	}
	vector<vector<bool>> beads;
	for(int i = 0; i < size; i++){
		vector<bool> tempvect;
		int tempint = nums[i];
		for(int j = 0; j < max; j++){
			if(tempint > 0){
				tempvect.push_back(1);
				tempint--;
			} else {
				tempvect.push_back(0);
			}
		}
		beads.push_back(tempvect);
	}
	
	bool did_gravity = true;		//Keeps track of whether beads fell or not
	while(did_gravity){
		did_gravity = false;		//No beads have fallen at the beginning
		
		for(int i = 0; i < size-1; i++){
			for(int j = 0; j < max; j++){
				if(beads[i][j] == 0){
					comparisons++;
					break;				//Leaves inner loop if position is empty
				}else if(beads[i][j] == 1 and beads[i-1][j] == 0){	//Drops bead if there is a bead at the position
					beads[i][j] = 0;							// and position 1 down is empty
					beads[i-1][j] = 1;
					did_gravity = true;
				}
				comparisons+=2;
			}
		}
	}
	
	for(int i = 0; i < size; i++){
		int tempsum = 0;
		for(int j = 0; j < max; j++){
			if(beads[i][j] == 0){
				comparisons++;
				break;				//Leaves inner loop if position is empty
			}else if(beads[i][j] == 1){
				tempsum++;
			}
		}
		nums[i] = tempsum;
	}
	
	return nums;
}
//END GRAVITY SORT//

//BUBBLE-SELECT SORT//
int* bubble_select_sort(int *nums){
	int swaps = 1, lo = 0;
	for(int i = 0; i < size and swaps != 0; i++){
		swaps = 0, lo = i;
		for(int j = i; j < size-(i+1); j++){
			if(nums[j+1] < nums[lo]){
				lo = j+1;
			}
			comparisons++;
			if(nums[j+1] < nums[j]){
				if(j+1 == lo){
					lo = j;
				}
				comparisons++;
				swap(nums[j+1],nums[j]);
				swaps++;
				swap_count++;
			}
			comparisons++;
		}
		swap(nums[lo], nums[i]);
		swap_count++;
	}
	return nums;
}
//END BUBBLE-SELECT SORT//

//DOUBLE SELECTION SORT//
int* double_selection_sort(int *nums) {
	int max, min;

	for (int i = 0; i < size/2 + 1; i++) {
		max = i;
		min = i;
		for (int j = i; j < size - i; j++) {
			if (nums[max] < nums[j]) {
				max = j;
				comparisons--;
			}
			else if (nums[min] > nums[j]) {
				min = j;
			}
			comparisons += 2;
		}
		swap(nums[i], nums[min]);
		swap(nums[size-i-1], nums[max]);
		swap_count += 2;
	}
	
	return nums;
}
//END DOUBLE SELECTION SORT//

//REVERSE DOUBLE SELECTION SORT//
int* reverse_double_selection_sort(int *nums) {
	int max, min;

	for (int i = 0; i < size / 2 + 1; i++) {
		max = i;
		min = i;
		for (int j = i; j < size - i; j++) {
			if (nums[max] < nums[j]) {
				max = j;
				comparisons--;
			}
			else if (nums[min] > nums[j]) {
				min = j;
			}
			comparisons += 2;
		}
		swap(nums[i], nums[max]);
		swap(nums[size - i - 1], nums[min]);
		swap_count += 2;
	}

	return nums;
}
//END REVERSE DOUBLE SELECTION SORT//

//MERGE SORT//
int* mergesort(int nums[], int scratch[], int lo, int hi) {
	if(lo < hi){
		int mid = lo + (hi - lo) / 2;
		mergesort(nums, scratch, lo, mid);
		mergesort(nums, scratch, mid+1, hi);
		int left = lo, right = mid + 1;
		for (int i = lo; i <= hi; i++) {
			if (left <= mid and (right > hi or nums[left] <= nums[right])) {
				scratch[i] = nums[left];
				left++;
				comparisons++;
			}
			else {
				scratch[i] = nums[right];
				right++;
				comparisons++;
			}
		}
		for (int i = lo; i <= hi; i++) {
			if (nums[i] != scratch[i]) {
				swap_count++;
			}
			nums[i] = scratch[i];
		}
	}
	return nums;
}

int* mergesort(int nums[]) {
	int* scratch = new int[size];
	nums = mergesort(nums, scratch, 0, size-1);
	delete[] scratch;
	return nums;
}
//END MERGE SORT//

//PANCAKE SORT//
void flips() {
}
//END PANCAKE SORT//

int main(int argc, char* const argv[]){
	
	srand(time(0));
	istringstream iss;
	string sort_type, direction;
	int size_ray = 0;
	if(argc != 3){
		if(argc == 2){
			sort_type = argv[1];
			//OUTPUTS THE SORT ANALYSIS HELP PAGE
			if(sort_type.compare("?") == 0){
				cout << "*****************************************" << endl
					 << "Sorting Algorithm Analysis (v2.5)        " << endl
					 << "  by Ryan Perretta                       " << endl
					 << "*****************************************" << endl
					 << "Supported Sorts:                         " << endl
					 << "_________________________________________" << endl
					 << "                                         " << endl
					 << "  Bubble Sort   \t(bub)                  " << endl
					 << "  Bubble-Select Sort\t(bs)               " << endl
					 << "  Cocktail Shaker\t(cs)                  " << endl
					 << "  Comb Sort     \t(comb)                 " << endl
					 << "  Counting Sort \t(count)                " << endl
					 << "  Gnome Sort    \t(gnome)                " << endl
					 << "  Gravity Sort  \t(grav)	Coming Soon   " << endl
					 << "  Insertion Sort\t(ins)                  " << endl
					 << "  Merge Sort    \t(merge)                " << endl
					 << "  Odd/Even Sort \t(oe)                   " << endl
					 << "  Selection Sort\t(sel)                  " << endl
					 << "  Stooge Sort   \t(stooge)               " << endl
					 << "                                         " << endl
					 << "*****************************************" << endl
					 << "Directions:                              " << endl
					 << "_________________________________________" << endl
					 << "                                         " << endl
					 << "  Ascending\t(a)                         " << endl
					 << "  Descending\t(d)                        " << endl
					 << "                                         " << endl
					 << "*****************************************" << endl
					 << "Preset Array Types:                      " << endl
					 << "_________________________________________" << endl
					 << "                                         " << endl
					 << "  **If array size is entered user is**   " << endl
					 << "     prompted to enter preset type       " << endl
					 << "_________________________________________" << endl
					 << "                                         " << endl
					 << "  Sorted        \t(s)                    " << endl
					 << "  Almost Sorted \t(as)                   " << endl
					 << "  Reverse Sorted\t(rs)                   " << endl
					 << "  Random        \t(r)                    " << endl
					 << "                                         " << endl
					 << "*****************************************" << endl
					 << "Notes:                                   " << endl
					 << "_________________________________________" << endl
					 << "                                         " << endl
					 << "  -To enter your own array, type 'custom'" << endl
					 << "   in the # of elements place            " << endl
					 << "  -Sorted array will not be outputted    " << endl
					 << "   for size greater than 1000.           " << endl
					 << "  -Array generated with random numbers   " << endl
					 << "   ranging from 0 to # of elements.      " << endl
					 << "  -Time is only displayed in seconds in  " << endl
					 << "   the current build.  				  " << endl
					 << "                                         " << endl
					 << "*****************************************" << endl;
			return 0;
			}
			//IF SORT IS MISUSED USAGE IS DISPLAYED
			cerr << " ___________________________________________________" << endl
				 << "|                                                   |" << endl
				 << "| Usage: ./sort <type> <direction> <# of elements>  |" << endl
				 << "|___________________________________________________|" << endl
				 << "|                                                   |" << endl
				 << "|          NOTE: Enter './sort ?' for help.         |" << endl
				 << "|___________________________________________________|" << endl;
			return 1;
		} else if (argc == 4){
			string custom;
			istringstream issint, issstring;
			issint.str(argv[3]);
			issstring.str(argv[3]);
			issstring >> custom;
			if (custom.compare("custom")==0) {
				size_ray = -1;
			}
			else if(!(issint >> size_ray) or size_ray  < 1){
				//ERROR PRODUCED WHEN ARRAY SIZE IS NOT A POSITIVE INTEGER
				cerr << "Error: Invalid array size " << argv[3] << ". (Must be positive integer)" << endl;
				return 1;
			}
		} else{
			//USAGE DISPLAYED
			cerr << " ___________________________________________________" << endl
				 << "|                                                   |" << endl
				 << "| Usage: ./sort <type> <direction> <# of elements>  |" << endl
				 << "|___________________________________________________|" << endl
				 << "|                                                   |" << endl
				 << "|          NOTE: Enter './sort ?' for help.         |" << endl
				 << "|___________________________________________________|" << endl;
			return 1;
		}
	}
	
	sort_type = argv[1];
	
	//MAKES SURE THE DESIRED SORTING ALGORITHM IS SUPPORTED
	string types[] = {"bub", "cs", "count", "sel", "ins", "gnome", "oe", "stooge", "comb", "grav", "bs", "ds", "merge"};
	for(int i = 0; i < (int) sizeof(types)/32+1; i++){
		if(i == (int) sizeof(types)/32){
			//PRODUCES ERROR WHEN ALGORITHM CODE IS NOT PART OF THE APPLICATION
			cerr << "Error: Invalid sort type: " << sort_type << "." << endl;
			return 1;
		} else if(types[i].compare(sort_type)==0){
			break;
		}
	}
	direction = argv[2];
	if(direction.compare("a") + direction.compare("d") == 2){
		//MAKES SURE THE DIRECTION IS EITHER ASCENDING('a') OR DESCENDING('b')
		cerr << "Error: Invalid direction: " << direction << "." << endl;
		return 1;
	}
	
	
	vector<int> values;
	if(size_ray == -1){
		cout << "Enter sequence of integers, each followed by a space: " << flush;
		int value, index = 0;
		string str;
		str.reserve(11);
		char c;
		iss.clear();
		while (true) {
			c = getchar();
			const bool eoln = c == '\r' || c == '\n';
			if (isspace(c) || eoln) {
				if (str.length() > 0) {
					iss.str(str);
					if (iss >> value) {
						values.push_back(value);
					} else {
						cerr << "Error: Non-integer value '" << str
							 << "' received for Item " << index + 1 << "." << endl;
						return 1;
					}
					iss.clear();
					++index;
				}
				if (eoln) {
					break;
				}
				str.clear();
			} else {
				str += c;
			}
		}
	} else {
		vector<string> preset_arrays = {"s", "as", "rs", "r"};
		string preset_type;
		cout << "Enter the type of array you would like to be generated: ";
		cin >> preset_type;
		cout << endl;
		if(preset_type.compare(preset_arrays[0]) == 0){
			for(int i = 1; i < size_ray+1; i++){
				values.push_back(i);
			}
		} else if(preset_type.compare(preset_arrays[1]) == 0) {
			int i, partition1 = size_ray*4/9, partition2 = size_ray*5/9;
			if (partition1 == partition2) {
				partition2++;
			}
			for(i = 0; i < partition1; i++){
				values.push_back(i);
			}
			for(i = partition2-1; i >= partition1; i--){
				values.push_back(i);
			}
			for(i = partition2; i < size_ray; i++){
				values.push_back(i);
			}
		} else if(preset_type.compare(preset_arrays[2]) == 0) {
			for(int i = size_ray; i > 0; i--){
				values.push_back(i);
			}
		} else {
			for(int i = 0; i < size_ray; i++){
				values.push_back(rand() % size_ray);
			}
		}
	}

    size = values.size();
    if (size == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
	
	int *temp = new int[size];
	copy(values.begin(), values.end(), temp);
	
	time_t start = time(0);
	
	if(sort_type.compare(types[2]) == 0){
		temp = countsort(temp);							//COUNT
		if (direction.compare("d") == 0){
			temp = reverse(temp);						//REVERSES COUNT
		}
	} else if(sort_type.compare(types[3]) == 0){
		if(direction.compare("a") == 0){
			temp = selection_sort(temp);				//SELECTION
		} else {
			temp = reverse_selection_sort(temp);		//REVERSE SELECTION SORT
		}
	} else if(sort_type.compare(types[0]) == 0){
		if(direction.compare("a") == 0){
			temp = bubble_sort(temp);					//BUBBLE
		} else {
			temp = reverse_bubble_sort(temp);			//REVERSE BUBBLE
		}
	} else if(sort_type.compare(types[1]) == 0){
		if(direction.compare("a") == 0){
			temp = cocktail_shaker_sort(temp);			//COCKTAIL SHAKER
		} else{
			temp = reverse_cocktail_shaker_sort(temp);	//REVERSE COCKTAIL SHAKER SORT
		}
	} else if(sort_type.compare(types[4]) == 0){
		if(direction.compare("a") == 0){
			temp = insertion_sort(temp);				//INSERTION
		} else {
			temp = reverse_insertion_sort(temp);		//REVERSE INSERTION SORT
		}
	} else if(sort_type.compare(types[5]) == 0){
		if(direction.compare("a") == 0){
			temp = gnome_sort(temp);					//GNOME
		} else {
			temp = reverse_gnome_sort(temp);			//REVERSE GNOME
		}
	} else if(sort_type.compare(types[6]) == 0){
		if(direction.compare("a") == 0){
			temp = odd_even_sort(temp);					//ODD/EVEN
		} else {
			temp = reverse_odd_even_sort(temp);			//REVERSE ODD/EVEN
		}
	} else if(sort_type.compare(types[7]) == 0){
		temp = stooge_sort(temp, direction);			//STOOGE + REVERSE STOOGE
	} else if(sort_type.compare(types[8]) == 0){
		if(direction.compare("a") == 0){
			temp = comb_sort(temp);						//COMB
		} else {
			temp = reverse_comb_sort(temp);				//REVERSE COMB SORT
		}
	} else if (sort_type.compare(types[9]) == 0){
		//temp = gravity_sort(temp);						//GRAVITY SORT
		cout << "This algorithm is not yet complete." << endl;
		return 0;
	} else if (sort_type.compare(types[10]) == 0){
		temp = bubble_select_sort(temp);				//BUBBLE-SELECT SORT
	} else if (sort_type.compare(types[11]) == 0) {
		if (direction.compare("a") == 0) {
			temp = double_selection_sort(temp);			//DOUBLE SELECTION SORT
		} else {
			temp = reverse_double_selection_sort(temp); //REVERSE DOUBLE SELECTION SORT
		}
	} else if (sort_type.compare(types[12]) == 0) {
		temp = mergesort(temp);
	}
	
	double time_elapsed = difftime(time(0), start);
	
	//outputs sorted array
	if(size <= 1000){
		cout << "Sorted Array:	" << "[";
		for(int i = 0; i < size; i++){
			cout << temp[i];
			if(!(i == size-1)){
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}
	
	cout << endl << "*****************************************************************************" << endl
		 << "\tSwaps: " << swap_count << "     Comparisons: " << comparisons << "     Time Elapsed: " << time_elapsed << endl
		 << "*****************************************************************************" << endl;
	
	delete[] temp;
}