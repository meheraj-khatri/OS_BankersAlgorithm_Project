/*
 * Banker's Algorithm Implementation
 *
 * Author: Meheraj Khatri
 * Date: Nov 23 2025
 * 
 * * Description:
 *
 * This program implements the Banker's Algorithm to avoid deadlocks. 
 * It reads process and resource data from a file (input.txt) and determines 
 * if the system is in a safe state. If safe, it prints the execution sequence.
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    
    // --- Step 1: Open the Input File ---
    ifstream inputFile("input.txt");

    // Check if the file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input.txt. Please make sure the file exists." << endl;
        return 1;
    }

    int n; // Number of processes
    int m; // Number of resources

    // Read the first two lines for dimensions
    inputFile >> n >> m;

    // --- Step 2: Initialize Data Structures ---
    // We use vectors of vectors to represent the 2D matrices
    vector<int> available(m);
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    // Read the 'Available' resources line
    for (int i = 0; i < m; i++) {
        inputFile >> available[i];
    }

    // Read the 'Allocation' matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inputFile >> allocation[i][j];
        }
    }

    // Read the 'Max' matrix and calculate the 'Need' matrix simultaneously
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inputFile >> max[i][j];
            
            // Calculate Need: Need = Max - Allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Close the file as we are done reading data
    inputFile.close();


    // --- Step 3: Banker's Algorithm Logic ---

    vector<int> f(n, 0);       // Finish array: 0 = not finished, 1 = finished
    vector<int> ans(n, 0);     // Stores the resulting safe sequence
    int ind = 0;               // Index for the safe sequence
    
    // Create a temporary 'work' vector to track available resources during simulation
    vector<int> work = available; 

    // We loop 'n' times to ensure we check every process enough times
    for (int k = 0; k < n; k++) {
        
        // Iterate through all processes
        for (int i = 0; i < n; i++) {
            
            // If the process has NOT been finished yet
            if (f[i] == 0) { 
                
                int flag = 0;

                // Check if the process's Needs can be met by the current Work resources
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1; // Need is too high, cannot execute right now
                        break;
                    }
                }

                // If flag is still 0, it means the process can safely execute
                if (flag == 0) { 
                    
                    // Add this process to our safe sequence
                    ans[ind++] = i;

                    // Simulate returning resources: Work = Work + Allocation
                    for (int y = 0; y < m; y++) {
                        work[y] += allocation[i][y];
                    }

                    // Mark the process as finished
                    f[i] = 1; 
                }
            }
        }
    }

    // --- Step 4: Check Results and Print Output ---
    
    bool safe = true;

    // Check if any process was left unfinished
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            safe = false;
            cout << "The system is NOT in a safe state." << endl;
            break;
        }
    }

    // If all processes finished, print the sequence
    if (safe) {
        cout << "The system is in a safe state." << endl;
        cout << "Safe Sequence is: ";
        
        for (int i = 0; i < n - 1; i++) {
            cout << "P" << ans[i] << " -> ";
        }
        cout << "P" << ans[n - 1] << endl;
    }

    return 0;
}