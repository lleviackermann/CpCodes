#include <iostream>
using namespace std;

struct ProcessNode {
    int id;
    ProcessNode* next;

    ProcessNode(int id) : id(id), next(nullptr) {}
};

bool hasCycle(ProcessNode* head) {
    ProcessNode* slow = head;
    ProcessNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

int main() {
    ProcessNode* head = new ProcessNode(1);
    head->next = new ProcessNode(2);
    head->next->next = new ProcessNode(3);
    head->next->next->next = nullptr;

    if (hasCycle(head)) {
        cout << "Cycle detected\n";
    } else {
        cout << "No cycle detected\n";
    }

    return 0;
}
