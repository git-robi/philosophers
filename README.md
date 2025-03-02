# 🍝 Philosophers - A Thread Synchronization Project

Hey there! 👋 Welcome to my Philosophers project, where I built my solution for the classic dining philosophers problem - a fascinating challenge in concurrent programming and thread synchronization!

## 🎯 What's This Project About?

Imagine a group of philosophers sitting at a round table, doing one of three things:
- 🤔 Thinking
- 🍴 Eating
- 😴 Sleeping

But here's the catch:
- There's a large bowl of spaghetti in the middle
- There's a fork between each philosopher
- They need TWO forks to eat
- If they don't eat for too long, they die
- They can't talk to each other
- They can't know if another philosopher is about to die

The challenge? Keep them all alive by properly managing their actions and resource sharing!

## 🛠️ How I Built It

I implemented this project using threads and mutexes in C, with a focus on preventing deadlocks and race conditions:

1. **Thread Management**:
   - Each philosopher is a thread
   - Used pthread library for thread creation and management
   - Implemented mutex locks for forks and shared resources
   - Added colorful output for better visualization of states

2. **Data Structures**:
   - Created a main data structure (`t_data`) for shared information:
     - Number of philosophers
     - Time limits for eating, sleeping, and dying
     - Mutex arrays for forks
     - Status flags for simulation control
   - Individual philosopher structure (`t_philo`) containing:
     - Personal data (ID, meals eaten, last meal time)
     - Pointers to left and right forks
     - Thread and mutex information

3. **Synchronization Strategy**:
   - Implemented even/odd philosopher timing to prevent deadlocks
   - Used mutex locks for critical sections
   - Added monitoring system to check philosopher states
   - Implemented clean termination when conditions are met

## 🤔 The Tricky Parts

This project came with some interesting challenges:

1. **Race Conditions**:
   - Protecting shared resources
   - Ensuring accurate timing for death checks
   - Managing multiple threads accessing same data

2. **Deadlock Prevention**:
   - Avoiding situations where philosophers all grab one fork
   - Implementing proper fork allocation strategy
   - Managing resource release properly

3. **Performance Optimization**:
   - Balancing check frequencies
   - Minimizing mutex lock time
   - Ensuring smooth thread operation

## 🎓 What I Learned

This project was an amazing learning experience:

1. **Concurrent Programming**:
   - Deep understanding of thread synchronization
   - Practical experience with mutex locks
   - Real-world application of deadlock prevention

2. **System Programming**:
   - Working with POSIX threads
   - Managing system resources
   - Understanding timing and scheduling

3. **Problem Solving**:
   - Breaking down complex synchronization issues
   - Implementing efficient monitoring systems
   - Debugging multi-threaded applications

## 💡 How to Use It

```bash
# Compile the program
make

# Run with parameters:
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Example:
./philo 5 800 200 200 7
```

### 📊 Parameters Explained:
- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time (ms) a philosopher can survive without eating
- `time_to_eat`: Time (ms) it takes to eat
- `time_to_sleep`: Time (ms) spent sleeping
- `[number_of_times_each_philosopher_must_eat]`: Optional, simulation stops when all philosophers eat this many times

## 🎨 Visuals

I added color coding to make it easier to follow what's happening:
- 🔵 BLUE: Thinking
- 🟢 GREEN: Eating
- 🟡 YELLOW: Taking forks
- 🟣 CYAN: Sleeping
- 🔴 RED: Death (hopefully you won't see this much!)

### 🐛 Error Handling

The program handles various error cases:
- Invalid arguments
- Memory allocation failures
- Thread creation failures
- Mutex initialization errors
- Edge cases (single philosopher, zero meals, etc.)
## 🔍 Final Thoughts

This project was a fantastic dive into concurrent programming! It really showed me how complex managing shared resources can be, and how important proper synchronization is in multi-threaded applications.

The skills I learned here - especially about thread management and race condition prevention - have been invaluable for understanding real-world concurrent programming challenges. Plus, watching the philosophers successfully share their forks without dying is pretty satisfying! 🎉

---
*Built with ❤️ and lots of coffee at 42 School*
