#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

/* function to convert a character into its digit; 'A' converts into 10; 'B' into 11, etc.
*/
unsigned int hexa_to_number(char ch) {
    unsigned int temp = 0;
    // TODO: implement this function
    if(ch >= '0' && ch <= '9') temp = ch - '0';
    if (ch >= 'A' && ch <= 'F') temp = ch - 'A' + 10;
    return temp;
}
    

// function to return the hash value based on the first digit
unsigned int hashfct1(string nic) {
  // TODO: implement this function, then delete the return statement below
  // std::cout << "hashfct1 output: " + hexa_to_number(nic[0]) << endl;  // debug
  return hexa_to_number(nic[0]);
}

// function to return the hash value based on the second digit
unsigned int hashfct2(string nic) {
   // TODO: implement this function, then delete the return statement below
    return hexa_to_number(nic[1]);
}

// function to return the hash value based on the third digit
unsigned int hashfct3(string nic) {
   // TODO: implement this function, then delete the return statement below
	return hexa_to_number(nic[2]);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(string nic) {
   // TODO: implement this function, then delete the return statement below
	return hexa_to_number(nic[3]);
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(string nic) {
    // TODO: implement this function, then delete the return statement below
	return hexa_to_number(nic[4]);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(string nic) {
    // TODO: implement this function, then delete the return statement below
	return hexa_to_number(nic[5]);
}

// Constructor for struct Item
Item::Item(string itemName, string nic):itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    string nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

// function that adds the specified NIC to the sensor network (i.e., to all hash tables)
void SensorNIC::addItem(string itemName, string nic) {
  // TO DO: implement this function, then delete the return statement below
  struct Item itemToAdd = {itemName, nic};
  hT1.insert({nic, itemToAdd});
  hT2.insert({nic, itemToAdd});
  hT3.insert({nic, itemToAdd});
  hT4.insert({nic, itemToAdd});
  hT5.insert({nic, itemToAdd});
  hT6.insert({nic, itemToAdd});
  // return;
}

// function that removes the sensor specified by the nic value from the network
// if sensor is found, then it is removed and the function returns true
// else returns false
bool SensorNIC::removeItem(string nic) {
  // TODO: implement this function, then delete the return statement below
  hT1.erase(nic);
  hT2.erase(nic);
  hT3.erase(nic);
  hT4.erase(nic);
  hT5.erase(nic);
  hT6.erase(nic);
  return true;
}

// function that decides the best hash function, i.e. the ones among
// fct1-fct6 that creates the most balanced sensor network for the current
// set of NIC addresses, i.e. data member allItems

// Hints:
// Calculate the balance of each hashtable, one by one.
unsigned int SensorNIC::bestHashing() {
  // TODO: implement this function, then delete the return statement below
  unsigned int arr[6];

  // Hash table 1
  unsigned int low = hT1.bucket_size(0);
  unsigned int high = hT1.bucket_size(0);
  for (unsigned int i=0; i<16; ++i) {
    if (hT1.bucket_size(i) > high) high = hT1.bucket_size(i);
    if (hT1.bucket_size(i) < low) low = hT1.bucket_size(i);
    // cout << hT1.bucket_size(i); // Call bucket_size() to get the size of each bucket
  }
  arr[0] = high - low;
	
  low = hT2.bucket_size(0);
  high = hT2.bucket_size(0);
  for (unsigned int i=0; i<16; ++i) {
    if (hT2.bucket_size(i) > high) high = hT2.bucket_size(i);
    if (hT2.bucket_size(i) < low) low = hT2.bucket_size(i);
    // cout << hT1.bucket_size(i); // Call bucket_size() to get the size of each bucket
  }
  arr[1] = high - low;

  low = hT3.bucket_size(0);
  high = hT3.bucket_size(0);
  for (unsigned int i=0; i<16; ++i) {
    if (hT3.bucket_size(i) > high) high = hT3.bucket_size(i);
    if (hT3.bucket_size(i) < low) low = hT3.bucket_size(i);
  }
  arr[2] = high - low;

  low = hT4.bucket_size(0);
  high = hT4.bucket_size(0);
  for (unsigned int i=0; i<16; ++i) {
    if (hT4.bucket_size(i) > high) high = hT4.bucket_size(i);
    if (hT4.bucket_size(i) < low) low = hT4.bucket_size(i);
  }
  arr[3] = high - low;

  low = hT5.bucket_size(0);
  high = hT5.bucket_size(0);
  for (unsigned int i=0; i<16; ++i) {
    if (hT5.bucket_size(i) > high) high = hT5.bucket_size(i);
    if (hT5.bucket_size(i) < low) low = hT5.bucket_size(i);
  }
  arr[4] = high - low;

  low = hT6.bucket_size(0);
  high = hT6.bucket_size(0);
  for (unsigned int i=0; i<16; ++i) {
    if (hT6.bucket_size(i) > high) high = hT6.bucket_size(i);
    if (hT6.bucket_size(i) < low) low = hT6.bucket_size(i);
  }
  arr[5] = high - low;

	// Then, calculate the lowest balance
    
  unsigned int bestHashTblIndx = 0;
  unsigned int bestHashTblVal = arr[0];

  for(unsigned int i = 0; i < 6; i++){
    if(arr[i] < bestHashTblVal){
      bestHashTblVal = arr[i]; 
      bestHashTblIndx = i;
    } 
  }

    return bestHashTblIndx + 1;
}

// ALREADY COMPLETED
size_t SensorNIC::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size()) || (hT1.size() != hT6.size()) )
  	  throw std::length_error("Hash table sizes are not the same");
    
	return hT1.size();
}
