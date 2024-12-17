#include <iostream>
#include <queue>
#include <vector>
#include <string>

// Custom structure
struct Person {
    std::string name;
    int age;

    Person(std::string n, int a) : name(n), age(a) {}
};

// Custom comparator (older person has higher priority)
struct CompareAge {
    bool operator()(const Person& p1, const Person& p2) {
        return p1.age < p2.age; // Larger age has higher priority
    }
};

int main() {
    // Priority queue with custom comparator
    std::priority_queue<Person, std::vector<Person>, CompareAge> pq;

    // Adding elements
    pq.push(Person("Alice", 30));
    pq.push(Person("Bob", 25));
    pq.push(Person("Charlie", 35));

    // Displaying elements
    while (!pq.empty()) {
        Person p = pq.top();
        std::cout << p.name << " (" << p.age << ")" << std::endl;
        pq.pop();
    }

    return 0;
}
