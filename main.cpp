#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "./lib/term_freq.h"
#include "./lib/preprocess.h"
#include "./lib/stats.h"
#include "./lib/sorting.h"
#include "./lib/mis.h"
#include "./lib/document.h"
#include "./lib/queue.h"
#include "./lib/bst.h"

using namespace std;

typedef unordered_map<string, double> TFIDFWeights;
const string& dir = "./bin/origin";

void selectFiles(vector<int>& selectedFilesIndices,vector<string>& allFiles, Queue& queue);
void processSelectedFiles(int c1, char c2, const vector<int>& selectedFilesIndices);

int main() {
    while (true) {
        vector<int> selectedFilesIndice;
        Queue queue;
        
        vector<string> allFiles = getAllFilesInDirectory(dir);
        if (isDirectoryEmpty(dir) || allFiles.size() < 2) {
            cout << "It seems you have not imported at least two document files. This program requires two files to check for their similarity. Please import them to the directory /bin/origin before proceeding." << endl;
            exit(1);
        }
        else if (allFiles.size() == 2) {
            selectedFilesIndice.push_back(0);
            selectedFilesIndice.push_back(1);
        }
        else {
            selectFiles(selectedFilesIndice, allFiles, queue);
        }
        if(queue.get_size() > 0){
          int count = queue.get_size(), p = 0;
          while(queue.get_size() > 0){
            p++;
            cout << "-=" << p << "/" << count << "=-" << endl; 
            selectedFilesIndice = queue.dequeue();
            displaySort();
            cout << ">> ";
            int choice;
            do{
              cin >> choice;
            }while(!isSortChoiceValid(choice, 3));
            if(choice == 3){
              exit(0);
            }
            displaySortOptions();
                char option;
                cout << ">> ";
                cin >> option;
                if (testSortOptions(option, 3)) {
                    if (!(option == 'c')) {
                        processSelectedFiles(choice, option, selectedFilesIndice);
                    }
                    else {
                        clearConsole();
                    }
                }
                clearConsole();
            
          }
        }else{
displaySort();
            cout << ">> ";
            int choice;
            do{
              cin >> choice;
            }while(!isSortChoiceValid(choice, 3));
            if(choice == 3){
              exit(0);
            }
            displaySortOptions();
                char option;
                cout << ">> ";
                cin >> option;
                if (testSortOptions(option, 3)) {
                    if (!(option == 'c')) {
                        processSelectedFiles(choice, option, selectedFilesIndice);
                    }
                    else {
                        clearConsole();
                    }
                }
                clearConsole();
        }
        
    }

    return 0;
}

void selectFiles(vector<int>& selectedFilesIndices, vector<string>& allFiles, Queue& queue) {
    cout << "<Selection Menu>" << endl;
    char l;
    int ll = false;
    cout << "[INFO] Do you wish to select multiple files? Y/n" << endl;
    while (true) {
        cin >> l;
        if (l != 'y' && l != 'Y' && l != 'n' && l != 'N') {
            cout << "[INFO] Invalid Choice. Try Again." << endl;
        }
        else {
            if (l == 'y' || l == 'Y') {
                ll = true;
            }
            break;
        }
    }
    if (ll) {
        bool endSelection = false;
        while (!endSelection) {
            vector<int> tempVector;
            char m;
            int i = 0;
            for (auto& file : allFiles) {
                i++;
                cout << i << ". " << file.substr(file.find_last_of('/')) << endl;
            }
            int numSelected = 0;
            while (numSelected < 2) {
                int selected;
                cout << "FILE " << static_cast<char>('A' + numSelected) << ": ";
                cin >> selected;
                if (selected > i || selected <= 0) {
                    cout << "Invalid File Index. Try Again." << endl;
                }
                else {
                    int flagged = 0;
                    if (find(tempVector.begin(), tempVector.end(), selected - 1) != tempVector.end()) {
                        cout << "[INFO] You have selected the same file twice. Are you sure you want to compare a file to itself? Y/n" << endl;
                        char k;
                        while (k != 'y' && k != 'Y' && k != 'n' && k != 'N') {
                            cin >> k;
                            if (k != 'y' && k != 'Y' && k != 'n' && k != 'N') {
                                cout << "[INFO] Invalid Choice. Try Again." << (k == 'n' ? 't' : 'f') << endl;
                            }
                            else {
                                if (k == 'n' || k == 'N') {
                                    flagged = 1;
                                }
                                break;
                            }
                        }
                    }
                    if (flagged == 0) {
                        tempVector.push_back(selected - 1);
                        numSelected += 1;
                    }
                }
            }
            queue.enqueue(tempVector);
            cout << "[INFO] Continue? Y/n" << endl;
            while (true) {
                cin >> m;
                if (m != 'y' && m != 'Y' && m != 'n' && m != 'N') {
                    cout << "[INFO] Invalid Choice. Try Again." << endl;
                }
                else {
                    if (m == 'n' || m == 'N') {
                        endSelection = true;
                    }
                    break;
                }
            }
        }
    }
    else {
        int i = 0;
        for (auto& file : allFiles) {
            i++;
            cout << i << ". " << file.substr(file.find_last_of('/')) << endl;
        }
        int numSelected = 0;
        while (numSelected < 2) {
            int selected;
            cout << "FILE " << static_cast<char>('A' + numSelected) << ": ";
            cin >> selected;
            if (selected > i || selected <= 0) {
                cout << "Invalid File Index. Try Again." << endl;
            }
            else {
                int flagged = 0;
                if(find(selectedFilesIndices.begin(), selectedFilesIndices.end(), selected - 1) != selectedFilesIndices.end()) {
                    cout << "[INFO] You have selected the same file twice. Are you sure you want to compare a file to itself? Y/n" << endl;
                    char k;
                    while (k != 'y' && k != 'Y' && k != 'n' && k != 'N') {
                        cin >> k;
                        if (k != 'y' && k != 'Y' && k != 'n' && k != 'N') {
                            cout << "[INFO] Invalid Choice. Try Again." << (k == 'n' ? 't' : 'f') << endl;
                        }
                        else {
                            if (k == 'n' || k == 'N') {
                                flagged = 1;
                            }
                            break;
                        }
                    }
                }
                if (flagged == 0) {
                    selectedFilesIndices.push_back(selected - 1);
                    numSelected += 1;
                }
            }
        }
    }
}

void processSelectedFiles(int c1, char c2, const vector<int>& selectedFilesIndices) {
    vector<string> allFiles = getAllFilesInDirectory(dir);
    ifstream origin_file;
    ifstream test_file;
    string line, origin_str;
    string lineTest, test_str;
    float progress = 0;
    origin_file.open(allFiles.at(selectedFilesIndices.at(0)));
    test_file.open(allFiles.at(selectedFilesIndices.at(1)));

    Document* docA = new Document();
    Document* docB = new Document();

    docA->setPath(allFiles.at(selectedFilesIndices.at(0)));
    docB->setPath(allFiles.at(selectedFilesIndices.at(1)));

    while (getline(origin_file, line)) {
        origin_str += line;
    }

    progress += 0.1;
    loadingAnim(progress);

    while (getline(test_file, lineTest)) {
        test_str += lineTest;
    }

    docA->setWords(origin_str);
    docB->setWords(test_str);
    docA->setTotalWords(countWords(docA->getWords()));
    docB->setTotalWords(countWords(docB->getWords()));
    progress += 0.1;
    loadingAnim(progress);
    test_file.close();
    origin_file.close();

    string preprocessedTextA = removePunctuation(convertToLower(docA->getWords()));
    docA->setCleanedWords(preprocessedTextA);
    vector<string> tokensA = tokenize(*docA);
    docA->setTokens(tokensA);
    vector<string> cleanedTokensA = removeStopwords(*docA);
    unordered_map<string, int> frequenciesA = getTermFrequencies(*docA);
    progress += 0.2;
    loadingAnim(progress);

    string preprocessedTextB = removePunctuation(convertToLower(docB->getWords()));
    docB->setCleanedWords(preprocessedTextB);
    vector<string> tokensB = tokenize(*docB);
    docB->setTokens(tokensB);
    vector<string> cleanedTokensB = removeStopwords(*docB);
    unordered_map<string, int> frequenciesB = getTermFrequencies(*docB);
    vector<TermFrequency> docs;
    progress += 0.2;
    loadingAnim(progress);

    docs.push_back(frequenciesA);
    docs.push_back(frequenciesB);
    TFIDFWeights weightA = calculateTFIDFWeights(frequenciesA, docs);
    TFIDFWeights weightB = calculateTFIDFWeights(frequenciesB, docs);
    progress += 0.2;
    loadingAnim(progress);

    double sim = calculateCosineSimilarity(weightA, weightB);
    progress += 0.1;
    loadingAnim(progress);

    vector<pair<string, int>> sortedA = sortFrequencies(frequenciesA, c1, c2);
    vector<pair<string, int>> sortedB = sortFrequencies(frequenciesB, c1, c2);
   
    progress += 0.1;
    loadingAnim(progress);
    clearConsole();
    displayResults(*docA, *docB, sim);
    BST bstA, bstB;
    
    bstA.insert(sortedA);

    cout<<"Binary Search Tree of A: " << endl;
    bstA.printTree();

    cout <<"-----------------------"<< endl;

    bstB.insert(sortedB);
    cout<<"Binary Search Tree of B: " << endl;
    bstB.printTree();
    cout << endl;
    cout << "Export Results? [Y/n]: ";
    char in;
    cin >> in;
    clearConsole();
    if (in == 'y' || in == 'Y') {
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    char timestamp[80];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", currentTime);
    saveToCSV(sortedA, "./bin/export/A_" + string(timestamp) + ".csv");
    saveToCSV(sortedB, "./bin/export/B_" + string(timestamp) + ".csv");
}
    cout << "------" << endl;
}
