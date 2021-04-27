// Tether
// (C) 2021 Christopher Digno under GNU GPL v3
#include "../include/stdinc.h"
using namespace std;

void cleanProgramMemory(OrganizationTree &param1) {
    param1.clear();
}

// Initializes splash screen
char *initSplashScreen() {
    fstream splashes_stream;
    char *welcome_sps = new char[1168];
    splashes_stream.open("../docs/splash.tthr", ios::in);
    splashes_stream.read(welcome_sps, 1168 * sizeof(char));
    splashes_stream.close();
    return welcome_sps;
}

// Easier ForEach for printing chars
void putForEach(char object, size_t width = 84) {
    for (size_t i = 0; i < width; i++) {
        cout << '=';
    }
    cout << '\n';
}

int main() {
    string opchstr;
    OrganizationTree orgtree;
    eventProgram evprog;
    bool running = true;
    char *welcome_sps = initSplashScreen();
    cout << welcome_sps << '\n';
    delete welcome_sps;

    while (running) {
        int opchoice;
        cout << ">> Please enter a menu <<\n"
            << "=[1]= Organization Member\n"
            << "=[2]= Program and Events\n"
            << "=[3]= Exit Program\n";

        cout << "Your choice: ";
        opchoice = input<int>(1, 3);

        if (opchoice == 1) {
            while (true) {
                cout << "== Organization Member Menu ==\n"
                    << "[1] Print Organization Member Tree\n"
                    << "[2] Add a Member\n"
                    << "[3] Modify a Member\n"
                    << "[4] Go Back to Main Menu\n";
                cout << "Your choice: ";
                opchoice = input<int>(1, 4);
                if (opchoice == 1) {
                    cout << "========\n";
                    orgtree.print();
                    cout << "========\n";
                }
                else if (opchoice == 2) {
                    while (true) {
                        string memberName;
                        long unsigned int precedence;
                        cout << "Choose Hierarchy Type\n"
                            << "1) Branch Group Coordinator\n"
                            << "2) Branch Manager\n"
                            << "3) Branch Member\n"
                            << "4) Cancel\n";
                        cout << "Your choice: ";
                        opchoice = input<int>(1, 4);
                        if (opchoice == 4) {
                            break;
                        }
                        cout << "Please insert the person's name\n> ";
                        cin.ignore();
                        getline(cin, memberName);
                        if (opchoice == 1) {
                            orgtree.insertBranchCoordinator(memberName);
                        }
                        else if (opchoice == 2) {
                            if (orgtree.getSizeOf(posname::branch_coordinator) == 0) {
                                cout << "There are no Branch Groups existed, can't create a branch\n";
                            }
                            else {
                                cout << "In which group this member is going to reside?\n"
                                    << "(1-" << orgtree.getSizeOf(posname::branch_coordinator) << "): ";
                                precedence = input<int>(1, orgtree.getSizeOf(posname::branch_coordinator));
                                orgtree.insertBranchManager(memberName, precedence);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                        else if (opchoice == 3) {
                            if (orgtree.getSizeOf(posname::branch_manager) == 0) {
                                cout << "There are no Branches existed, can't insert a new member.\n";
                            }
                            else {
                                cout << "In which branch this member is going to reside?\n"
                                    << "(1-" << orgtree.getSizeOf(posname::branch_manager) << "): ";
                                precedence = input<int>(1, orgtree.getSizeOf(posname::branch_manager));
                                orgtree.insertBranchMember(memberName, precedence);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                        cout << "========\n";
                        orgtree.print();
                        cout << "========\n";
                        cout << "Do you want to add a member again? (y/n)\nYour choice: ";
                        getline(cin, opchstr);
                        if (opchstr == "n") {
                            break;
                        }
                    }
                }
                else if (opchoice == 3) {
                    while (true) {
                        cout << "Select the hierarchy type of the member you're going to edit\n"
                            << "1) Branch Group Coordinator\n"
                            << "2) Branch Manager\n"
                            << "3) Branch Member\n"
                            << "4) Cancel\nYour choice: ";
                        opchoice = input<int>(1, 4);
                        if (opchoice == 4) {
                            break;
                        }
                        else {
                            orgtree.modify(opchoice);
                        }
                        cout << "========\n";
                        orgtree.print();
                        cout << "========\n";
                        cout << "Do you want to modify a member again? (y/n)\nYour choice: ";
                        getline(cin, opchstr);
                        if (opchstr == "n") {
                            break;
                        }
                    }
                }
                else if (opchoice == 4) {
                    break;
                }
            }
        }
        else if (opchoice == 2) {
            while (true) {
                cout << "== Programs and Events Menu ==\n"
                    << "[1] Print Event List\n"
                    << "[2] Print Detailed Event List\n"
                    << "[3] Add Events\n"
                    << "[4] Update Event Licensing\n"
                    << "[5] Delete an Event\n"
                    << "[6] Go Back to Main Menu\n";
                cout << "Your choice: ";
                opchoice = input<int>(1, 6);

                if (opchoice == 1) {
                    cout << "======\nEvent List:\n";
                    evprog.print(false);
                    cout << "======\n";
                }
                else if (opchoice == 2) {
                    cout << "======\nDetailed Event List:\n";
                    evprog.print(true);
                    cout << "======\n";
                }
                else if (opchoice == 3) {
                    cin.ignore();
                    while (true) {
                        event evbuf;
                        cout << "Please enter the event's name: ";
                        getline(cin, evbuf.eventName);
                        cout << "How much funds are allocated?: USD";
                        evbuf.allocatedFunds = input<double>();
                        evprog.insert(evbuf);
                        cout << "Your event has been inserted succesfully!\n";

                        cout << "======\nEvent List:\n";
                        evprog.print(false);
                        cout << "======\n";

                        cout << "Do you want to add another event? (y/n)\nYour choice: ";
                        cin.ignore();
                        getline(cin, opchstr);
                        if (opchstr == "n") {
                            break;
                        }
                    }
                }
                else if (opchoice == 4) {
                    int evnum;
                    cout << "Please enter the event number you want to modify\n"
                        << "(1-" << evprog.size() << ")> ";
                    evnum = input<int>(1, evprog.size());
                    evprog.editLicense(evnum);
                }
                else if (opchoice == 5) {
                    int evnum;
                    cout << "Please enter the event number you want to delete\n"
                        << "(1-" << evprog.size() << ")> ";
                    evnum = input<int>(1, evprog.size());
                    evprog.deleteEntry(evnum);

                    cout << "======\nEvent List:\n";
                    evprog.print(false);
                    cout << "======\n";
                }
                else if (opchoice == 6) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }
    cleanProgramMemory(orgtree); // TODO put every memsave here
    return 0;
}