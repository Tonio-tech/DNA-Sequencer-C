#include "Sequencer.h"

enum {ONE = 1, TWO, THREE, FOUR};

Sequencer::Sequencer(string fileName) {
    m_fileName = fileName;
    ReadFile();
    MainMenu();

}

Sequencer::~Sequencer() {
    for(unsigned int i = 0; i < m_suspects.size(); i++) {
        delete m_suspects.at(i); //delete m_head;
    }

    for(unsigned int i = 0; i < m_evidence.size(); i++) {
        delete m_evidence.at(i); //delete m_head;
    }
    
}

void Sequencer::DisplayStrands() {
    for(unsigned int i = 0; i < m_suspects.size(); i++) {
        cout << endl;
        cout << m_suspects.at(i)->GetName() << endl;
        // using ostream
        cout << *m_suspects.at(i);
    }
    cout << endl;

    for(unsigned int i = 0; i < m_evidence.size(); i++) {
        cout << endl;
        cout << m_evidence.at(i)->GetName() << endl;
        cout << *m_evidence.at(i);
    }
}

void Sequencer::ReadFile() {
    fstream caseFile;

    string name;
    string data;
    DNA *dna_ptr;

    caseFile.open(m_fileName);

    if(caseFile.is_open()) { 
        // when file is open, take in the first line as a name, and the following line as data
        // use the name as a DNA name (suspect or evidence)
        // then iterate through the string data, putting each one into dna_ptr
        // then put dna_ptr into suspects (if the name is suspects) ad evidence (if the name is evidence)
        
        while(getline(caseFile, name)) {
            getline(caseFile, data);
            dna_ptr = new DNA(name);
            for(unsigned int i = 0; i < data.length(); i++) {
                if(data[i] != ',' && data[i] != '\n') {
                    dna_ptr->InsertEnd(data[i]);
                }
            }
            if(name[0] == 'S') {
                m_suspects.push_back(dna_ptr);
            } else {
                m_evidence.push_back(dna_ptr);
            }
            
        }
    }

    caseFile.close();
}

void Sequencer::MainMenu() {
    int choice;

    do {
        cout << endl;
        cout << "What would you like to do? " << endl;
        cout << "1. Display Strand" << endl << "2. Reverse Sequence" << endl << "3. Check Suspects" << endl << "4. Exit" << endl;
        cin >> choice;

        if(choice == ONE) {
            DisplayStrands();
        }

        if(choice == TWO) {
            ReverseSequence();
        }

        if(choice == THREE) {
            CheckSuspects();
        }

    } while(choice != FOUR); 

}

void Sequencer::CheckSuspects() { 
    cout << "Check all Suspects vs Evidence..." << endl;
    for(unsigned int i = 0; i < m_suspects.size(); i++) {
        cout << endl;
        // boolean flag to check if its a match
        bool isEqual = true;

        for(unsigned int j = 0; j < m_evidence.size(); j++) {
            if(m_suspects.at(i)->CompareSequence(*m_evidence.at(j))) {
                cout << m_suspects.at(i)->GetName() << " matches Evidence" << j + 1 << endl;
            } else {
                cout << m_suspects.at(i)->GetName() << " does NOT match Evidence" << j + 1 << endl;
                isEqual = false;
            }
        }
        if(isEqual) {
            cout << m_suspects.at(i)->GetName() << " matches ALL Evidence!" << endl;
        }
    }
}

void Sequencer::ReverseSequence() {
    int choice;
    int whichOne;

    // ask user for which type of sequence
    cout << "Which type of sequence would you like to reverse?" << endl << "1. Suspect" << endl << "2. Evidence" << endl;
    cin >> choice;

    while(choice != ONE && choice != TWO) {
        cout << "Which type of sequence would you like to reverse?" << endl << "1. Suspect" << endl << "2. Evidence" << endl;
        cin >> choice;
    }

    // if they chose suspect, asks which susepct by using the number
    if(choice == ONE) {
        cout << endl;
        cout << "Which suspect sequence would you like to reverse? (Enter the number)" << endl;
        for(unsigned int i = 0; i < m_suspects.size(); i++) {
            cout << m_suspects.at(i)->GetName() << endl;
            cout << *m_suspects.at(i);
            cout << endl;
        }
        cin >> whichOne;

        // if they chose an invalid number, reprompt and show their options
        while(unsigned(whichOne) > m_suspects.size()) {
            cout << "Which suspect sequence would you like to reverse? (Enter the number)" << endl;
            for(unsigned int i = 0; i < m_suspects.size(); i++) {
                cout << m_suspects.at(i)->GetName() << endl;
                cout << *m_suspects.at(i);
                cout << endl;
            }
            cin >> whichOne;
        }

        // reverse the desired sequence
        if(unsigned(whichOne) <= m_suspects.size()) {
            m_suspects.at(whichOne - 1)->ReverseSequence();
            cout << "Suspect" << whichOne << endl;
            cout << *m_suspects.at(whichOne - 1);
        }
    }

    // if they chose evidence, asks which strand by using the number
    if(choice == TWO) {
        cout << endl;
        cout << "Which evidence sequence would you like to reverse? (Enter the number)" << endl;
        for(unsigned int i = 0; i < m_evidence.size(); i++) {
            cout << m_evidence.at(i)->GetName() << endl;
            cout << *m_evidence.at(i);
            cout << endl;
        }
        cin >> whichOne;

        // if they chose an invalid number, reprompt and show their options
        while(unsigned(whichOne) > m_evidence.size()) {
            cout << "Which evidence sequence would you like to reverse? (Enter the number)" << endl;
            for(unsigned int i = 0; i < m_evidence.size(); i++) {
                cout << m_evidence.at(i)->GetName() << endl;
                cout << *m_evidence.at(i);
                cout << endl;
            }
            cin >> whichOne;
        }

        // reverse the desired sequence
        if(unsigned(whichOne) <= m_suspects.size()) {
            m_evidence.at(whichOne - 1)->ReverseSequence();
            cout << "Evidence" << whichOne << endl;
            cout << *m_evidence.at(whichOne - 1);
        }
        
    }
}

