#pragma once
#include "stdinc.h"

struct event {
    std::string eventName;
    double allocatedFunds;
    bool isApproved;
    bool isFundingApproved;

    event() {
        isApproved = false;
        isFundingApproved = false;
    }
};

class eventProgram {
private:
    std::vector<event> events;

public:
    void insert(event);
    void print(bool is_verbose);
    int size();
    void editLicense(int index);
    void deleteEntry(int index);
};