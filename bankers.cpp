// Domenic Santoli
// Operating Systems
// Professor Guan
// Project 2

#include <iostream>
#include <fstream>

// number of processes in a system
// P0, P1, P2, P3, P4
const int n = 5;

// number of resource types
// 3 resource types
const int m = 3;

// Avaliable 
// array of size m - indicating the number of available resources of each type.
int avalibale[m];

// Max
// 2d array of size n*m - indicating maximum demand of each process
int max[n][m];

// Allocation 
// 2d array of size n*m -  defines the number of resources of each type currently allocated to each process.
int allocation[n][m];

// Need
// 2d array of size n*m that indicates the remaining resource need of each process
// need [i,j] = max[i,j] - allocation[i,j]
int need[n][m];

// Finish 
// Not safe = 0. Safe = 1.
// Initialize to not safe
int finish[n] = {0,0,0,0,0};

// SS 
// for storing the safe sequence
int ss[n];

int main(int argc, char* argv[]) {
    int allocation_index = 0, max_index = 0;
    // Error if there is not an input file on command line
    if (argc < 2) {
        std::cerr << "Error, need file to read from" << std::endl;
        // Exit with error
        exit(1);            
    }
    // initialize input file stream
    // Open in file stream
    std::ifstream in(argv[1]);
    // if in cannot open
    if (!in) {
        std::cerr << "Error: Can not open file to read from" << argv[1] << std::endl;
        // Exit with error
        exit(2);
    }
    // if in opened correctly
    else if (in) {
         // to read file character by character
         char character;
         // for columns in int 2d array
         int i = 0;
         // READ IN ALLOCATION
         // while input files takes in a character 
         while (in >> character) {
            // if it is a ';' break and move onto next set of numbers
            if (character == ';') {
                break;
            }
            else {
                // put character in allocation array
                allocation[allocation_index][i] = character - '0';
                // increment i
                i++;
                // if i is equal to max number for row
                if (i == m) {
                    // reset column
                    i = 0;
                    // increment row
                    allocation_index++;
                }
            }
        }
        // reset i 
        i = 0;
        // READ IN MAX
        // while input files takes in a character 
         while (in >> character) {
            // if it is a ';' break and move onto next set of numbers
            if (character == ';') {
                break;
            }
            else {
                // put character in max array
                max[max_index][i] = character - '0';
                // increment i
                i++;
                // if i is equal to max number for row
                if (i == m) {
                    // reset column
                    i = 0;
                    // increment row
                    max_index++;
                }
            }
        }
        // reset i
        i = 0;
        // READ IN AVALIABLE
        // while input files takes in a character 
         while (in >> character) {
            // if it is a ';' break and move onto next set of numbers
            if (character == ';') {
                break;
            }
            else {
                // put character in max array
                avalibale[i] = character - '0';
                // increment i
                i++;
                // if i is equal to max number for row
                if (i == m) {
                    // reset column
                    i = 0;
                }
            }
        }
    } 

    int index = 0;

    // Initialize elements of Need
    // Remember need[i,j] = max[i,j] - allocation[i,j]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }

    // loop through 5 processes rows
    int i , j , k;
    int y;
    for (k = 0; k < n; k++) {
        // loop through need matrix of each process
        for (i = 0; i < n; i++) {
            // if finish at index is 0 , check if the resources needed greater than or less than resources avaliable
            if (finish[i] == 0) {
                // flag for if process can be added to safe sequence
                int flag = 0;
                // loop through need matrix and check if it is less than avaliable resources (work)
                for (j = 0; j < m; j++) {
                    // check if need of each process is greater than avaliable resources (work)
                    if (need[i][j] > avalibale[j]) {
                        // process can not be added to safe sequence , set flag to 1, check next process
                        flag = 1;
                        // break - go to next process
                        break;
                    }
                }
                // if process is safe to add to safe sequence
                if (flag == 0) {
                    // process enters safe sequence
                    // safe sequence at index is set to to process 0,1,2,3 or 4, then increment index
                    ss[index++] = i;
                    // new avalibale resources (work) becomes avaliable resources (work) + allocation
                    for (y = 0; y < m; y++) {
                        avalibale[y] += allocation[i][y];
                    }
                    // process entered safe sequence, update finish
                    finish[i] = 1;
                }
            }
        }
    }
    // reset flag to check is sequence is safe or not
    int flag = 1;

    // loop through finish array
    for(int i = 0; i < n; i++) {
        // if system is not safe
        if (finish[i] == 0) {
            // set flag to 0 - so next if does not execute
            flag = 0;
            // print the system is not safe
            std::cout << "system not safe" << std::endl;
            // break
            break;
      }
    }
  
    // if flag is still 1 the system is safe , finish had all 1s, print out safe sequence
    if(flag==1) {
        std::cout << "The system is safe, the safe sequence is: " << std::endl;
        std::cout << "< ";
        // loop through safe sequence array and print processes in order 
        for (i = 0; i < n; i++) {
            if (i == n - 1) {
                std::cout << " P" << ss[i] << " >";
            }
            else {
                std::cout << " P" << ss[i] << ",";
            }
        }
    }
    return 0;
}
