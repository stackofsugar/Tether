#include "../include/stdinc.h"

OrganizationTree::OrganizationTree() {
    head = new Tnode;
    head->name = "Christopher Digno";
    num_branch = 0;
    num_branch_member = 0;
}

void OrganizationTree::insertBranchCoordinator(std::string name) {
    Tnode *objbuf = head,
        *objbuf2;
    objbuf2 = new Tnode;
    objbuf->children.push_back(objbuf2);
    objbuf2->name = name;
}

void OrganizationTree::insertBranchManager(std::string name, long unsigned int precedence) {
    Tnode *objbuf1 = head,
        *objbuf2;
    if (objbuf1->children.size() < precedence) {
        std::cout << "Can't find the specified Branch Group Coordinator\n";
        return;
    }
    objbuf1 = objbuf1->children[precedence - 1];
    objbuf2 = new Tnode;
    objbuf1->children.push_back(objbuf2);
    objbuf2->name = name;
    num_branch++;
}

void OrganizationTree::insertBranchMember(std::string name, long unsigned int precedence) {
    Tnode *objbuf1 = head,
        *objbuf2;
    if (num_branch < precedence || precedence < 0) {
        std::cout << "Branch number " << precedence << " did not exist.\n";
        return;
    }
    long unsigned int traverse_count = 0;
    for (long unsigned int i = 0; i < objbuf1->children.size(); i++) {
        for (long unsigned int j = 0; j < objbuf1->children[i]->children.size(); j++) {
            traverse_count++;
            if (traverse_count == precedence) {
                objbuf2 = new Tnode;
                objbuf1->children[i]->children[j]->children.push_back(objbuf2);
                objbuf2->name = name;
                num_branch_member++;
            }
        }
    }
}

int OrganizationTree::getSizeOf(posname pos) {
    Tnode *objbuf1 = head;
    if (pos == posname::branch_coordinator) {
        return objbuf1->children.size();
    }
    else if (pos == posname::branch_manager) {
        return num_branch;
    }
    else {
        return num_branch_member;
    }
}

// TODO: This thing.
void OrganizationTree::modify(int posint) {
    int intbuf;
    std::string strbuf;
    Tnode *objbuf1 = head;
    int traverse_count = 0;
    if (posint == 1) {
        if (getSizeOf(posname::branch_coordinator) == 0) {
            std::cout << "There are no Branch Groups existed\n";
            std::cin.ignore();
            return;
        }
        std::cout << "Enter the Branch Group number\n"
            << "(1-" << getSizeOf(posname::branch_coordinator) << "): ";
        intbuf = input<int>(1, getSizeOf(posname::branch_coordinator));
        std::cout << "Please enter a new name: ";
        std::cin.ignore();
        std::getline(std::cin, strbuf);
        objbuf1->children[intbuf - 1]->name = strbuf;
    }
    else if (posint == 2) {
        if (getSizeOf(posname::branch_manager) == 0) {
            std::cout << "There are no Branches existed\n";
            std::cin.ignore();
            return;
        }
        std::cout << "Enter the Branch number\n"
            << "(1-" << getSizeOf(posname::branch_manager) << "): ";
        intbuf = input<int>(1, getSizeOf(posname::branch_manager));
        for (long unsigned int i = 0; i < objbuf1->children.size(); i++) {
            traverse_count = objbuf1->children[i]->children.size();
            if (traverse_count >= intbuf) {
                std::cout << "Please enter a new name: ";
                std::cin.ignore();
                std::getline(std::cin, strbuf);
                objbuf1->children[i]->children[intbuf - 1]->name = strbuf;
                return;
            }
            else {
                intbuf -= traverse_count;
                traverse_count = 0;
            }
        }
    }
    else if (posint == 3) {
        if (getSizeOf(posname::branch_member) == 0) {
            std::cout << "There are no Branch Members existed\n";
            std::cin.ignore();
            return;
        }
        std::cout << "Enter the Branch member number\n"
            << "(1-" << getSizeOf(posname::branch_member) << "): ";
        intbuf = input<int>(1, getSizeOf(posname::branch_member));
        for (long unsigned int i = 0; i < objbuf1->children.size(); i++) {
            for (long unsigned int j = 0; j < objbuf1->children[i]->children.size(); j++) {
                traverse_count = objbuf1->children[i]->children[j]->children.size();
                if (traverse_count >= intbuf) {
                    std::cout << "Please enter a new name: ";
                    std::cin.ignore();
                    std::getline(std::cin, strbuf);
                    objbuf1->children[i]->children[j]->children[intbuf - 1]->name = strbuf;
                }
                else {
                    intbuf -= traverse_count;
                    traverse_count = 0;
                }
            }
        }
    }
}


void OrganizationTree::clear() {
    Tnode *objbuf = head;
    std::vector<Tnode *> nodes;
    for (long unsigned int i = 0; i < objbuf->children.size(); i++) {
        nodes.push_back(objbuf->children[i]);
        for (long unsigned int j = 0; j < objbuf->children[i]->children.size(); j++) {
            nodes.push_back(objbuf->children[i]->children[j]);
            for (long unsigned int k = 0; k < objbuf->children[i]->children[j]->children.size(); k++) {
                nodes.push_back(objbuf->children[i]->children[j]->children[k]);
            }
        }
    }
    for (long long unsigned int i = 0; i < nodes.size(); i++) {
        delete nodes[i];
        nodes[i] = nullptr;
    }
}

void OrganizationTree::print() {
    Tnode *objbuf = head;
    int branch_ommited = 0,
        branchmem_ommited = 0;
    std::cout << "» President: " << head->name << '\n';
    for (long unsigned int i = 0; i < objbuf->children.size(); i++) {
        std::cout << "├──» Branch Group " << i + 1 << " Coordinator: " << objbuf->children[i]->name << '\n';
        for (long unsigned int j = 0; j < objbuf->children[i]->children.size(); j++) {
            std::cout << "│\t├──» Branch " << ++branch_ommited << " Manager: " << objbuf->children[i]->children[j]->name << '\n';
            for (long unsigned int k = 0; k < objbuf->children[i]->children[j]->children.size(); k++) {
                std::cout << "│\t│\t├──» Member " << ++branchmem_ommited << ": " << objbuf->children[i]->children[j]->children[k]->name << '\n';
            }
        }
    }
}