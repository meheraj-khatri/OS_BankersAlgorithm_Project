#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class BankersAlgorithm {
private:
    int num_processes;
    int num_resources;
    vector<vector<int>> allocation;
    vector<vector<int>> max;
    vector<vector<int>> need;
    vector<int> available;
    vector<int> total_resources;

public:
    BankersAlgorithm(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open input file!" << endl;
            exit(1);
        }

        // Read number of processes and resources
        file >> num_processes >> num_resources;

        // Read total resources
        total_resources.resize(num_resources);
        for (int i = 0; i < num_resources; i++) {
            file >> total_resources[i];
        }

        // Initialize matrices
        allocation.resize(num_processes, vector<int>(num_resources));
        max.resize(num_processes, vector<int>(num_resources));
        need.resize(num_processes, vector<int>(num_resources));
        available.resize(num_resources);

        // Read allocation and max for each process
        for (int i = 0; i < num_processes; i++) {
            for (int j = 0; j < num_resources; j++) {
                file >> allocation[i][j];
            }
            for (int j = 0; j < num_resources; j++) {
                file >> max[i][j];
            }
        }

        // Read available resources
        for (int i = 0; i < num_resources; i++) {
            file >> available[i];
        }

        file.close();

        // Calculate need matrix
        calculateNeed();
    }

    void calculateNeed() {
        for (int i = 0; i < num_processes; i++) {
            for (int j = 0; j < num_resources; j++) {
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }
    }

    bool isSafeSequence(vector<int>& safe_sequence) {
        vector<int> work = available;
        vector<bool> finish(num_processes, false);
        safe_sequence.clear();

        bool found;
        do {
            found = false;
            for (int i = 0; i < num_processes; i++) {
                if (!finish[i]) {
                    bool can_allocate = true;
                    for (int j = 0; j < num_resources; j++) {
                        if (need[i][j] > work[j]) {
                            can_allocate = false;
                            break;
                        }
                    }

                    if (can_allocate) {
                        // Process can be allocated resources
                        for (int j = 0; j < num_resources; j++) {
                            work[j] += allocation[i][j];
                        }
                        finish[i] = true;
                        safe_sequence.push_back(i);
                        found = true;
                    }
                }
            }
        } while (found);

        // Check if all processes finished
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                return false;
            }
        }
        return true;
    }

    void printState() {
        cout << "Banker's Algorithm - System State" << endl;
        cout << "=================================" << endl;
        cout << "Number of processes: " << num_processes << endl;
        cout << "Number of resource types: " << num_resources << endl;
        
        cout << "\nTotal resources: ";
        for (int res : total_resources) {
            cout << res << " ";
        }
        cout << endl;

        cout << "\nCurrent Allocation Matrix:" << endl;
        cout << "Process\tAllocation (ABC)" << endl;
        for (int i = 0; i < num_processes; i++) {
            cout << "P" << i << "\t";
            for (int j = 0; j < num_resources; j++) {
                cout << allocation[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nMax Matrix:" << endl;
        cout << "Process\tMax (ABC)" << endl;
        for (int i = 0; i < num_processes; i++) {
            cout << "P" << i << "\t";
            for (int j = 0; j < num_resources; j++) {
                cout << max[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nNeed Matrix (Max - Allocation):" << endl;
        cout << "Process\tNeed (ABC)" << endl;
        for (int i = 0; i < num_processes; i++) {
            cout << "P" << i << "\t";
            for (int j = 0; j < num_resources; j++) {
                cout << need[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nAvailable resources: ";
        for (int res : available) {
            cout << res << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "Banker's Algorithm Implementation" << endl;
    cout << "=================================" << endl;

    BankersAlgorithm banker("input/system_state.txt");
    banker.printState();

    vector<int> safe_sequence;
    bool is_safe = banker.isSafeSequence(safe_sequence);

    cout << "\nSafety Check Results:" << endl;
    cout << "====================" << endl;
    if (is_safe) {
        cout << "✓ System is in a SAFE state!" << endl;
        cout << "Safe sequence: ";
        for (size_t i = 0; i < safe_sequence.size(); i++) {
            cout << "P" << safe_sequence[i];
            if (i != safe_sequence.size() - 1) {
                cout << " → ";
            }
        }
        cout << endl;
    } else {
        cout << "✗ System is in an UNSAFE state! Deadlock may occur." << endl;
    }

    return 0;
}