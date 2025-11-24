#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // 1. Open the input file
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input.txt" << endl;
        return 1;
    }

    int n, m; // n = processes, m = resources
    inputFile >> n >> m;

    // Vectors to store the matrices
    vector<int> available(m);
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    // 2. Read Available Resources
    for (int i = 0; i < m; i++) {
        inputFile >> available[i];
    }

    // 3. Read Allocation Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inputFile >> allocation[i][j];
        }
    }

    // 4. Read Max Matrix and Calculate Need
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inputFile >> max[i][j];
            // Calculation: Need = Max - Allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    inputFile.close();

    // 5. Banker's Algorithm Implementation
    vector<int> f(n, 0); // Finish flags (0=false, 1=true)
    vector<int> ans(n, 0); // Stores the safe sequence
    int ind = 0; 
    
    // Work vector is initialized to Available
    vector<int> work = available; 

    // Loop until all processes are finished or deadlock occurs
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) { // If process is not finished
                int flag = 0;
                
                // Check if Need <= Work for all resources
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1; // Cannot execute, need is too high
                        break;
                    }
                }

                if (flag == 0) { // Safe to execute
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        work[y] += allocation[i][y]; // Release resources
                    }
                    f[i] = 1; // Mark as finished
                }
            }
        }
    }

    // 6. Output Result
    bool safe = true;
    for(int i=0; i<n; i++) {
        if(f[i] == 0) {
            safe = false;
            cout << "The system is NOT in a safe state." << endl;
            break;
        }
    }

    if(safe) {
        cout << "The system is in a safe state." << endl;
        cout << "Safe Sequence is: ";
        for (int i = 0; i < n - 1; i++)
            cout << "P" << ans[i] << " -> ";
        cout << "P" << ans[n - 1] << endl;
    }

    return 0;
}