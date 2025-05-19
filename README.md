# 🔠 ProtocolParallel

> Master Modern C++ with Real Projects. Parallel Thinking, Productive Execution.

---

## 🚀 About This Repo

**ProtocolParallel** is a hands-on C++ learning framework designed to turn learners into **parallel computing system thinkers**.

You won’t just learn Modern C++ —
You’ll **build a macOS app**, **Lunr**, an AI agent that enforces your productivity by monitoring and restricting your distractions.

---

## 🛠️ Mission

> Learn Modern C++ through structured daily modules and build a **parallel-aware**, system-level productivity enforcer called **Lunr**.

---

## 🐽 Learning Roadmap

| Day | Focus Area                 | Concepts Covered                                                                      |
| --- | -------------------------- | ------------------------------------------------------------------------------------- |
| 1   | Modern C++ Fundamentals    | `struct`, `vector`, `auto`, `&`, `const`, I/O, RAII                                   |
| 2   | Smart Pointers & RAII      | `unique_ptr`, `shared_ptr`, `weak_ptr`, memory ownership models                       |
| 3   | STL Containers & Iterators | `vector`, `map`, `unordered_map`, `set`, raw iterators, memory layout                 |
| 4   | Lambdas & Algorithms       | `std::sort`, `std::count_if`, `std::transform`, `for_each`, functors, `std::function` |
| 5   | Memory Layout & Allocation | `stack`, `heap`, `static`, custom allocators, memory addresses, ownership             |

Each day includes:

* 📘 Concept breakdowns
* ✅ Quizzes & tests
* 🛠️ Real-world coding challenges
* 🧠 Deep dives into memory and parallel execution patterns

---

## 🔧 Final Project: Lunr – AI Productivity Agent (macOS)

### 🌟 What It Does

`Lunr` is an **AI agent that rewards and punishes you based on productivity**:

* Tracks your daily activities: GitHub contributions, VS Code usage, Netflix, YouTube, etc.
* Learns your project contribution baseline
* If productivity drops → restricts access to apps (e.g., block HBO Max)
* Designed to **enforce discipline and build consistency**

---

### ⚙️ Built With

* `C++17/20`
* STL containers, algorithms, and smart pointers
* macOS system APIs (Screen Time, Accessibility)
* GitHub API (to analyze contribution graph)
* Planned: SQLite or flat-file storage, minimal native UI

---

## 🌐 Folder Structure

```bash
ProtocolParallel/
├── D1/                          # Basic vector + struct + I/O based project
├── D2/                          # Memory-safe ContactBook using unique/shared pointers
├── D3/                          # Contact grouping with maps, sets, and iterator logic
├── D4/                          # Functional refactoring using STL algorithms & lambdas
├── D5/                          # Memory placement, stack/heap simulations
├── Lunr/                        # Real AI productivity enforcement app
│   ├── App/
│   ├── Docs/
│   └── README.mkd
└── README.md
```

---

## 💫 Who This Is For

* Self-learners preparing for advanced C++ interviews
* Engineers moving from scripting languages (Python/JS) into systems programming
* Creators building **native**, **parallel**, and **high-performance** tools
* OS-focused learners wanting to tap into **macOS APIs**

---

## 🧠 Key Learning Goals

| Concept            | Mastery Outcome                                                            |
| ------------------ | -------------------------------------------------------------------------- |
| Smart Pointers     | Understand memory ownership and auto-deletion                              |
| STL Containers     | Know what data structure to use and why                                    |
| Iterators          | Walk memory without raw pointers                                           |
| Lambdas & Functors | Pass logic inline or store for later execution                             |
| Algorithms         | Write expressive, optimized loops with `std::sort`, `std::transform`, etc. |
| Memory Model       | Control and visualize how stack, heap, and memory blocks behave            |
| Parallelism        | Learn task dispatching with `std::execution::par` and atomic-safe design   |

---

## 👩‍💻 Created By

**Lwin Oo** —
Systems Engineer • Parallel Computing Enthusiast • Productive Philosopher

---

## 🔖 License

MIT License — Feel free to build, remix, and launch.

---

## 🔠 Final Thought

> Learn to think like a system.
> Write code that respects time, memory, and user intent.
> Welcome to the Protocol of Parallelism.
