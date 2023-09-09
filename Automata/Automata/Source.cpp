#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using std::cout;
using std::cout; using std::endl;
using std::string; using std::reverse;
using namespace std;

// Define a struct to represent an automaton
struct Automaton {
    int id; // Unique ID for each automaton
    int dfa; // Current state of the DFA
    string string;
};

// Define a variable to keep track of the number of automata in the array
int numAutomata = 0;

// Function to add a new automaton to the array
void addAutomaton(int id, Automaton a[], string str) {
   
    a[numAutomata].id = id;
    a[numAutomata].dfa = 0;
    a[numAutomata].string = str;
    numAutomata++;
}

// Function to delete an automaton from the array
void deleteAutomaton(int id, Automaton automata[]) {
    // Find the automaton with the given ID
    int index = -1;
    for (int i = 0; i < numAutomata; i++) {
        if (automata[i].id == id) {
            index = i;
            break;
        }
    }

    // If the automaton is found, delete it by shifting all the elements after it one position to the left
    if (index != -1) {
        for (int i = index; i < numAutomata - 1; i++) {
            automata[i] = automata[i + 1];
        }
        numAutomata--;
        cout << "Automaton with ID " << id << " deleted." << endl;
    }
    else {
        cout << "Automaton with ID " << id << " not found." << endl;
    }
}

// Function to search for an automaton by ID
Automaton* searchAutomaton(int id,Automaton automata[]) {
    for (int i = 0; i < numAutomata; i++) {
        if (automata[i].id == id) {
            return &automata[i];
        }
    }
    cout << "Automaton with ID " << id << " not found." << endl;
    return nullptr;
}

std::string Check(const std::string& input_string) {
    std::string output_string;
    for (char c : input_string) {
        if (c == 'a' || c == 'b') {
            output_string += c;
        }
    }
    return output_string;
}
// This function is for the starting state (Q0) of DFA
void start(Automaton& automaton, char c) {
    if (c == 'a') {
        automaton.dfa = 1;
    }
    else if (c == 'b') {
        automaton.dfa = 3;
    }
    else {
        automaton.dfa = -1;
    }
}

// This function is for the first state (Q1) of DFA
void state1(Automaton& automaton, char c) {
    if (c == 'a') {
        automaton.dfa = 2;
    }
    else if (c == 'b') {
        automaton.dfa = 4;
    }
    else {
        automaton.dfa = -1;
    }
}

// This function is for the second state (Q2) of DFA
void state2(Automaton& automaton, char c) {
    if (c == 'b') {
        automaton.dfa = 3;
    }
    else if (c == 'a') {
        automaton.dfa = 1;
    }
    else {
        automaton.dfa = -1;
    }
}

// This function is for the third state (Q3) of DFA
void state3(Automaton& automaton, char c) {
    if (c == 'b') {
        automaton.dfa = 3;
    }
    else if (c == 'a') {
        automaton.dfa = 4;
    }
    else {
        automaton.dfa = -1; // Invalid input
    }
}
// This function is for the fourth state (Q4) of DFA
void state4(Automaton& automaton, char c) {
   automaton.dfa = -1;
}

// Function to check if a given string is accepted by the DFA
bool acceptString(Automaton& automaton, string str) {
    for (char c : str) {
        switch (automaton.dfa) {
        case 0:
            start(automaton, c);
            break;
        case 1:
            state1(automaton, c);
            break;
        case 2:
            state2(automaton, c);
            break;
        case 3:
            state3(automaton, c);
            break;
        case 4:
            state4(automaton, c);
            break;
        default:
            return false;
        }
    }
    // The string is accepted if the final state is Q2 or Q4 (even number of a's)
    return automaton.dfa == 3;
}

int main() {
    // Prompt the user to enter a string
    Automaton a[1000];
    int n;
    int id = 1;
    cout << "how much string do you want to enter and test: ";
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {

        cout << "Enter a string: ";
        std::string str;
        std::getline(std::cin, str);
        std::string s;
        s = Check(str);
        addAutomaton(id, a, s);
        if (acceptString(a[id - 1], s))
            cout << "accepted" << endl;
        else cout << "unaccepted" << endl;
        id = id + 1;
    }

    while (1) {
        cout << "1:delete" << endl;
        cout << "2:search" << endl;
        cout << "3:quit" << endl;
        int j = 0;
        std::cin >> j;
        if (j == 1) {
            int dID = 0;
            cout << "enter ID to delete:";
            std::cin >> dID;
            deleteAutomaton(dID,a);
            cout << "1:continue  2:quit" << endl;
            int p;
            std::cin >> p;
            if (p != 1)
                return 0;
        }
        if (j == 2) {
            int k;
            cout << "enter ID to search: ";
            std::cin >> k;
            Automaton* res = searchAutomaton(k, a);
            cout << res->string << endl;
            cout << "1:continue  2:quit" << endl;
            int q;
            std::cin >> q;
            if (q != 1)
                return 0;
        }
        else if (j != 1 && j != 2)
            return 0;
    }
}