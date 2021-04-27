#include "../include/stdinc.h"

void eventProgram::insert(event evbuf) {
    events.push_back(evbuf);
}

int eventProgram::size() {
    return events.size();
}

void eventProgram::deleteEntry(int i) {
    i--;
    std::cout << events[i].eventName << " is successfully removed!\n";
    events.erase(events.begin() + i);
}


void eventProgram::editLicense(int i) {
    int intbuf;
    i--;
    std::cout << "Do you want to toggle the Event Approval to " << std::boolalpha << !events[i].isApproved << "? (1/0)\n> ";
    intbuf = input<int>(0, 1);
    events[i].isApproved = ((intbuf == 0) ? events[i].isApproved : !events[i].isApproved);
    std::cout << "Do you want to toggle the Funding Approval to " << std::boolalpha << !events[i].isFundingApproved << "? (1/0)\n> ";
    intbuf = input<int>(0, 1);
    if (intbuf == 1 && !events[i].isApproved) {
        std::cout << "Funding modification is not allowed until the event is approved.\n";
        return;
    }
    events[i].isFundingApproved = ((intbuf == 0) ? events[i].isFundingApproved : !events[i].isFundingApproved);
    if (!events[i].isApproved) {
        events[i].isFundingApproved = false;
    }
}

void eventProgram::print(bool is_verbose) {
    if (events.empty()) {
        std::cout << "= There are no events added =\n";
    }
    if (is_verbose == false) {
        for (long unsigned int i = 0; i < events.size(); i++) {
            std::cout << "│ [" << i + 1 << "] " << events[i].eventName << '\n';
        }
    }
    else {
        for (long unsigned int i = 0; i < events.size(); i++) {
            std::cout << "│ [" << i + 1 << "] " << events[i].eventName << '\n'
                << "│  │-› Allocated Funds : USD" << events[i].allocatedFunds << '\n'
                << "│  │-› Approval Status : " << (events[i].isApproved ? "Approved" : "Not (yet) Approved") << '\n'
                << "│  │-› Funds Approval  : " << (events[i].isFundingApproved ? "Approved" : "Not (yet) Approved") << '\n';
        }
    }
}
