# 🖥️ CPU Scheduling Algorithms in C++ (C++98 Compatible)

This project implements four classic CPU scheduling algorithms — First-Come First-Served (FCFS), Shortest Job First (SJF), Priority Scheduling, and Round Robin (RR) — entirely in C++98 for maximum compatibility.

What is C++98?
C++98 is the first standardized version of the C++ programming language, released in 1998. It does not include newer features like auto, range-based loops, or lambdas, making it ideal for environments where only older compilers are available

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

g++ -std=c++98 main.cpp -o scheduling<br>
./scheduling


### *Windows*

g++ -std=c++98 main.cpp -o scheduling.exe<br>
scheduling.exe<br>

📥 Sample Input

4<br>
0 8 2<br>
1 4 1<br>
2 9 3<br>
3 5 2<br>
2<br>

Explanation:

First line: 4 → Number of processes

Next 4 lines: ArrivalTime BurstTime Priority

Last line: Quantum for Round Robin (2 in this example)

📤 Sample Output

--- First-Come First-Served (FCFS) Results ---<br>
Process 1 | Arrival: 0 | Burst: 8 | Priority: 2 | Completion: 8 | Turnaround: 8 | Waiting: 0<br>
Process 2 | Arrival: 1 | Burst: 4 | Priority: 1 | Completion: 12 | Turnaroun: 11 | Waiting: 7<br>
Process 3 | Arrival: 2 | Burst: 9 | Priority: 3 | Completion: 21 | Turnaround: 19 | Waiting: 10<br>
Process 4 | Arrival: 3 | Burst: 5 | Priority: 2 | Completion: 26 | Turnaround: 23 | Waiting: 18<br>

Average Turnaround Time: 15.25
Average Waiting Time: 8.75
CPU Utilization: 100%

Best suited algorithm based on Average Turnaround Time: Shortest Job First (SJF) 

...

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

