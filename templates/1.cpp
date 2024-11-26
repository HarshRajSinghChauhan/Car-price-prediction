#include <iostream>
using namespace std;

void queueUpdation(int queue[], int timer, int arrival[], int n, int &maxProccessIndex) {
    for (int i = maxProccessIndex + 1; i < n; i++) {
        if (arrival[i] <= timer) {
            queue[maxProccessIndex] = i + 1;  // Add process to queue
            maxProccessIndex = i;
            break;
        }
    }
}

void queueMaintainence(int queue[], int n) {
    int temp = queue[0];
    for (int i = 0; i < n - 1; i++) {
        queue[i] = queue[i + 1];
    }
    queue[n - 1] = temp;
}

// Driver Code
int main() {
    int n = 5, tq = 1, timer = 0, maxProccessIndex = 0;
    float avgWait = 0, avgTT = 0;

    int arrival[] = {2, 5, 1, 0, 4};
    int burst[] = {6, 2, 8, 3, 4};
    int wait[n], turn[n], queue[n], temp_burst[n];
    bool complete[n] = {false};

    for (int i = 0; i < n; i++) {
        queue[i] = 0;
        temp_burst[i] = burst[i];
    }

    // Initialize the timer to the arrival time of the first process
    while (timer < arrival[0]) {
        timer++;
    }

    queue[0] = 1; // Start with the first process
    maxProccessIndex = 0;

    while (true) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (temp_burst[i] > 0) {
                flag = false;
                break;
            }
        }
        if (flag) break;

        // Round Robin processing
        for (int i = 0; i < n && queue[i] != 0; i++) {
            int ctr = 0;
            while ((ctr < tq) && (temp_burst[queue[0] - 1] > 0)) {
                temp_burst[queue[0] - 1] -= 1;
                timer += 1;
                ctr++;

                // Check for new arrivals and update the queue
                queueUpdation(queue, timer, arrival, n, maxProccessIndex);
            }

            // If a process is completed, store its exit time
            if ((temp_burst[queue[0] - 1] == 0) && !complete[queue[0] - 1]) {
                turn[queue[0] - 1] = timer;
                complete[queue[0] - 1] = true;
            }

            // If CPU is idle, increment the timer and check for new arrivals
            bool idle = true;
            for (int i = 0; i < n && queue[i] != 0; i++) {
                if (!complete[queue[i] - 1]) {
                    idle = false;
                    break;
                }
            }
            if (idle) {
                timer++;
                queueUpdation(queue, timer, arrival, n, maxProccessIndex);
            }

            // Maintain the queue order after each process completion
            queueMaintainence(queue, n);
        }
    }

    // Calculate wait and turn around times
    for (int i = 0; i < n; i++) {
        turn[i] = turn[i] - arrival[i];
        wait[i] = turn[i] - burst[i];
    }

    // Display results
    cout << "\nProgram No.\tArrival Time\tBurst Time\tWait Time\tTurnAround Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << arrival[i] << "\t\t" << burst[i] << "\t\t" << wait[i] << "\t\t" << turn[i] << endl;
    }

    for (int i = 0; i < n; i++) {
        avgWait += wait[i];
        avgTT += turn[i];
    }

    cout << "\nAverage wait time : " << (avgWait / n)
         << "\nAverage Turn Around Time : " << (avgTT / n);

    return 0;
}
