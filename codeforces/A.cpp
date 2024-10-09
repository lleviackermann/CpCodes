#include <iostream>
#include <thread>

// Function to be executed by thread 1, takes an integer as a parameter
void threadFunction1(int x) {
    for (int i = 0; i < x; ++i) {
        std::cout << "Thread is running, i = " << i << "\n";
    }
}

// Function to be executed by thread 2, takes a string as a parameter
void threadFunction2(const std::string& message, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << "Thread 2: " << message << " " << i << "\n";
    }
}

int main() {
    int numIterations = 3;
    std::string msg = "Hello from Thread 2";

    // Create two threads and pass parameters to their functions
    std::thread t1(threadFunction1, numIterations);  // Passing an integer
    std::thread t2(threadFunction1, 2);         // Passing a string and an integer

    // Wait for both threads to finish execution
    t1.join();
    t2.join();

    std::cout << "Both threads have finished execution\n";

	std::cout << std::thread::hardware_concurrency() << std::endl;
    
    return 0;
}
