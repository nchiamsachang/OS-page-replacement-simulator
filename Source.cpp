//Nathan Chiamsachang
//Trey Rajsombath
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// checks if a page is already in a frame
bool isInFrames(int frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// prints one column of the output table
void printColumn(int frames[], int numFrames, bool fault) {
    if (!fault) {
        for (int i = 0; i < numFrames; i++) { //print blank spaces for each row
            cout << "\t";
        }
    }
    else {
        for (int i = 0; i < numFrames; i++) {
            if (frames[i] == -1) { //frame is empty
                cout << "\t";
            }
            else {
                cout << frames[i] << "\t";
            }
        }
    }
}

// FIFO page replacement algorithm
int fifo(int ref[], int refLen, int numFrames) {
    int frames[100];
    int faults = 0; // fault count
    int oldest = 0; // track which frames to replace next 

    for (int i = 0; i < numFrames; i++) { // set all frames to empty
        frames[i] = -1;
    }

    //print the ref string across the top
    cout << "Reference String:\t";
    for (int i = 0; i < refLen; i++) {
        cout << ref[i] << "\t";
    }
    cout << endl;

    // print a dashed line 
    cout << "----";
    for (int i = 0; i < refLen; i++) {
        cout << "--------";
    }
    cout << endl;

    // store each columns frame state for printing row by row
    int history[100][100];
    bool faultHistory[100];

    for (int i = 0; i < refLen; i++) { //go through each page in ref string
        if (isInFrames(frames, numFrames, ref[i])) {
            faultHistory[i] = false;
        }
        else { // page fault
            frames[oldest] = ref[i];
            oldest = (oldest + 1) % numFrames; //move to next spot in order
            faults++;
            faultHistory[i] = true;
        }

        for (int j = 0; j < numFrames; j++) { //save current frame state
            history[i][j] = frames[j];
        }
    }

    // print table row by row
    for (int row = 0; row < numFrames; row++) {
        cout << "Frame " << row + 1 << ":\t\t";
        for (int col = 0; col < refLen; col++) { //each column is one step
            if (!faultHistory[col]) { //no fault so print blank
                cout << "\t";
            }
            else if (history[col][row] == -1) {
                cout << "\t";
            }
            else {
                cout << history[col][row] << "\t"; //else print the page in frame 
            }
        }
        cout << endl;
    }

    return faults;
}

// OPT page replacement algorithm
int opt(int ref[], int refLen, int numFrames) {
    int frames[100];
    int faults = 0; // fault count
    int count = 0; 

    for (int i = 0; i < numFrames; i++) { //set all frames to empty
        frames[i] = -1;
    }

    // store history for printing later
    int history[100][100]; //create 2D array
    bool faultHistory[100]; 

    for (int i = 0; i < refLen; i++) {
        if (isInFrames(frames, numFrames, ref[i])) {
            faultHistory[i] = false;
        }
        else { // page fault
            if (count < numFrames) { // empty frame available
                frames[count] = ref[i];
                count++;
            }
            else { // all frames full, need to replace
                int farthest = -1;
                int replaceIndex = 0;

                for (int j = 0; j < numFrames; j++) {
                    int nextUse = -1;

                    for (int k = i + 1; k < refLen; k++) { // look ahead
                        if (frames[j] == ref[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if (nextUse == -1) { // never used again
                        replaceIndex = j;
                        break;
                    }

                    if (nextUse > farthest) { // this page is used farther in future 
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = ref[i]; //replace chosen frame
            }
            faults++;
            faultHistory[i] = true;
        }

        for (int j = 0; j < numFrames; j++) {
            history[i][j] = frames[j];
        }
    }

    // print ref string
    cout << "Reference String:\t";
    for (int i = 0; i < refLen; i++) {
        cout << ref[i] << "\t";
    }
    cout << endl;

    //print lines
    cout << "----";
    for (int i = 0; i < refLen; i++) {
        cout << "--------";
    }
    cout << endl;

    // print table row by row
    for (int row = 0; row < numFrames; row++) {
        cout << "Frame " << row + 1 << ":\t\t";
        for (int col = 0; col < refLen; col++) {
            if (!faultHistory[col]) {
                cout << "\t";
            }
            else if (history[col][row] == -1) {
                cout << "\t";
            }
            else {
                cout << history[col][row] << "\t";
            }
        }
        cout << endl;
    }

    return faults;
}

int main() { // main 
    char filename[100];
    char line[500];

    cout << "Enter the input file name: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error: could not open file " << filename << endl;
        return 1;
    }

    infile.getline(line, 500);
    infile.close();

    char algo = line[0];

    //parse the numbers after the first comma 
    int numbers[100];
    int numCount = 0;
    int pos = 2; // start after the first two char and comma 
    int len = strlen(line);

    while (pos < len) {
        int num = 0; //build number digit by digit 
        bool foundDigit = false;

        while (pos < len && line[pos] >= '0' && line[pos] <= '9') { //read digit 
            num = num * 10 + (line[pos] - '0'); // convert char into int 
            pos++;
            foundDigit = true;
        }

        if (foundDigit) {
            numbers[numCount] = num;
            numCount++;
        }

        if (pos < len && line[pos] == ',') {
            pos++;
        }
        else {
            pos++;
        }
    }

    int numFrames = numbers[0]; 

    int ref[100];
    int refLen = numCount - 1;

    for (int i = 0; i < refLen; i++) { // copy ref string from num array    
        ref[i] = numbers[i + 1];
    }

    int faults = 0;

    //checks ref string for FIFO
    if (algo == 'F' || algo == 'f') {
        cout << "\n=== FIFO Page Replacement ===" << endl;
        cout << "Number of frames: " << numFrames << endl << endl;
        faults = fifo(ref, refLen, numFrames);
    }
    // check ref string for OPT
    else if (algo == 'O' || algo == 'o') {
        cout << "\n=== OPT Page Replacement ===" << endl;
        cout << "Number of frames: " << numFrames << endl << endl;
        faults = opt(ref, refLen, numFrames);
    }
    // if nothing return 
    else {
        cout << "Unknown algorithm type: " << algo << endl;
        return 1;
    }
    // pring page fault
    cout << "\nTotal page faults: " << faults << endl;

    return 0;
}
