#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <csignal>

std::atomic<double> cpu_load(50.0);
std::atomic<bool> running(true);

// Worker simulating adjustable CPU load
void burn_cpu(std::atomic<bool>& running, int duration_seconds) {
    using namespace std::chrono;
    const int cycle_ms = 100;

    auto end_time = steady_clock::now() + seconds(duration_seconds);

    while (running && steady_clock::now() < end_time) {
        double current_load = cpu_load.load();
        int busy_time = static_cast<int>(cycle_ms * current_load / 100.0);
        int sleep_time = cycle_ms - busy_time;

        auto start = steady_clock::now();
        while (duration_cast<milliseconds>(steady_clock::now() - start).count() < busy_time) {
            // burn CPU
        }

        std::this_thread::sleep_for(milliseconds(sleep_time));
    }
}

// Control thread for live updates via stdin
void load_input_listener() {
    double new_load;
    while (running) {
        std::cout << "Enter new CPU load %: ";
        std::cin >> new_load;
        if (new_load < 0 || new_load > 100) {
            std::cout << "Invalid load %. Must be 0–100.\n";
            continue;
        }
        cpu_load.store(new_load);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <initial CPU load %> <seconds>\n";
        return 1;
    }

    cpu_load = std::stod(argv[1]);
    int duration = std::stoi(argv[2]);

    int num_threads = std::thread::hardware_concurrency(); // or hardcode

    std::vector<std::thread> workers;
    for (int i = 0; i < num_threads; ++i) {
        workers.emplace_back(burn_cpu, std::ref(running), duration);
    }

    std::thread input_thread(load_input_listener);

    for (auto& t : workers) t.join();
    running = false;
    input_thread.join();

    std::cout << "CPU load simulation complete.\n";
    return 0;
}
