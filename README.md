CPU Load Simulator
This is a C++ program that simulates CPU load across all available cores. The load can be adjusted live during runtime via standard input.

Features
Simulates configurable CPU usage (0–100%) 
Dynamically adjusts the load in real-time via console input.
Multi-threaded CPU burning using std::thread.


Usage:
./cpu_load_simulator <initial CPU load %> <duration in seconds>
<initial CPU load %>: Initial CPU usage percentage (e.g., 50)
<duration in seconds>: Total duration the simulation should run (e.g., 60)

Example:

./cpu_load_simulator 50 60
This command starts the simulator with 50% CPU load for 60 seconds.

Live CPU Load Adjustment
During the simulation, you'll be prompted to enter new CPU load percentages:

Enter new CPU load %:

Input a value between 0 and 100 to change the load dynamically. Invalid inputs will be ignored with a warning.
