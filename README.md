# 🖥️ CPU Scheduling Algorithms in C++ (C++98 Compatible)

This project implements **four classic CPU scheduling algorithms** in C++, designed to work even with **C++98 compilers** (no modern C++11+ features required).  
It also automatically **compares performance** and suggests the **best scheduling method** based on **average turnaround time**.

---

## 📌 Features
- **First-Come, First-Served (FCFS)**
- **Shortest Job First (SJF)** – Non-preemptive
- **Priority Scheduling** – Non-preemptive
- **Round Robin (RR)** – User-defined quantum
- **Performance Analysis**:
  - Average Turnaround Time
  - Average Waiting Time
  - CPU Utilization
- **Best Algorithm Recommendation** based on results



---

## ⚙️ Compilation & Execution

### **Linux / macOS**

g++ -std=c++98 main.cpp -o scheduling
./scheduling


### **Windows*

g++ -std=c++98 main.cpp -o scheduling.exe
scheduling.exe
📥 Sample Input

4
0 8 2
1 4 1
2 9 3
3 5 2
2
Explanation:

First line: 4 → Number of processes

Next 4 lines: ArrivalTime BurstTime Priority

Last line: Quantum for Round Robin (2 in this example)

📤 Sample Output

--- First-Come First-Served (FCFS) Results ---
Process 1 | Arrival: 0 | Burst: 8 | Priority: 2 | Completion: 8 | Turnaround: 8 | Waiting: 0<br>
Process 2 | Arrival: 1 | Burst: 4 | Priority: 1 | Completion: 12 | Turnaroun: 11 | Waiting: 7<br>
Process 3 | Arrival: 2 | Burst: 9 | Priority: 3 | Completion: 21 | Turnaround: 19 | Waiting: 10<br>
Process 4 | Arrival: 3 | Burst: 5 | Priority: 2 | Completion: 26 | Turnaround: 23 | Waiting: 18<br>

Average Turnaround Time: 15.25
Average Waiting Time: 8.75
CPU Utilization: 100%

...

>>> Best suited algorithm based on Average Turnaround Time: Shortest Job First (SJF) <<<

🏆 Best Algorithm Recommendation
After running all four algorithms, the program selects the one with the lowest average turnaround time and displays it.

🛠️ Requirements
C++ Compiler (GCC, Clang, MinGW)

Works with C++98 standard (no need for -std=c++11)

📜 License
This project is open-source under the MIT License.

🤝 Contributing
Pull requests are welcome!
If you have suggestions for additional features (e.g., preemptive SJF or Priority), feel free to open an issue.

