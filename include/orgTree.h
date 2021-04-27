#pragma once
#include "../include/stdinc.h"

enum class posname {
    executive,
    branch_coordinator,
    branch_manager,
    branch_member
};

struct Tnode {
    std::string name;
    std::vector<Tnode *> children;
};

class OrganizationTree {
private:
    Tnode *head;
    long unsigned int num_branch;
    long unsigned int num_branch_member;

public:
    OrganizationTree();
    void insertBranchCoordinator(std::string name);
    void insertBranchManager(std::string name, long unsigned int precedence);
    void insertBranchMember(std::string name, long unsigned int precedence);
    int getSizeOf(posname pos);
    void modify(int posint);
    void print();
    void clear();
};