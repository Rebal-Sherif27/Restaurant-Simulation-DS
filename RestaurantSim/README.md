# Restaurant-Simulation-DS
A C++ simulation of restaurant workflows demonstrating applied data structures and algorithms.

## 📋 Phase 2 Workload & Feature Distribution
The project is strictly divided based on Phase 2 Workload Features to minimize overlap. Each member is responsible for the implementation of their specific classes and functions. Integration is handled via the central `RunSimulation()` engine.

### Quick Summary
| Team Member | Domain | Features |
| :--- | :--- | :--- |
| **Shahd** | Chef / Cooking / Ready / Takeaway | 8, 9, 12 |
| **Rebal** | Core Engine / Assign Table / UI / Output | 1, 10, 13 |
| **Jody** | Input / Actions / Pending / Finished Dine-In / Tests | 2, 3, 7, 14 |
| **Ali** | Scooters / Delivery / Cancellation | 4, 5, 6, 11 |

---

### 1. Shahd — Chef & Cooking Management
**Features:** 8, 9, 12
* **Assignment:** Assign pending orders to the appropriate chefs (`FreeCS`, `FreeCN`).
* **State Management:** Move orders from pending to `Cooking_Orders`. Calculate completion times based on order size and chef speed. Link orders to specific chefs.
* **Completion:** Move orders from cooking to the appropriate ready list upon completion and return chefs to the free list.
* **Takeaway:** Finalize takeaway orders and move them to the finished queue.
* **UI Integration:** Prepare print counts for chefs, cooking orders, ready orders, and takeaway/finished orders.

### 2. Rebal — Core Simulation, Table Assignment & Output
**Features:** 1, 10, 13
* **Core Engine:** Implement the `Restaurant::RunSimulation()` main loop. Hook up the UI (`UI.h`, `UI.cpp`) and orchestrate function calls for all team members.
* **Table Logic:** Execute table assignments for dine-in orders. Manage table states (free, busy sharable, busy no-share). Move dine-in orders to in-service.
* **Tracking:** Record exact `table ID`, `service start time`, and `service finish time`.
* **Output & UI:** Manage the simulation modes (Interactive, Step-by-Step, Silent). Handle screen printing, calculate final statistics (Wait Time, Turnaround Time), and generate the final `output.txt`.

### 3. Jody — Input Processing, Actions & Testing
**Features:** 2, 3, 7, 14
* **File Parsing:** Read the input file to load initial restaurant data (chefs, scooters, tables, settings).
* **Actions:** Parse the number of actions. Generate `RequestAction` and `CancelAction` objects and load them into `ACTIONS_LIST`.
* **Queueing:** Execute request actions at the correct timestep. Route orders to the correct pending lists (`ODG`, `ODN`, `OT`, `OVG`, `OVC`, `OVN`).
* **Dine-In Cleanup:** Check finished dine-in orders, move them to the finished queue, and free up their respective tables.
* **QA:** Prepare 6 non-trivial input test files and verify their expected outputs.

### 4. Ali — Delivery, Scooters & Cancellations
**Features:** 4, 5, 6, 11
* **Cancellations:** Execute cancellation actions. Search and remove targets from pending, cooking, or ready queues. Move canceled orders to the canceled list and free the chef (if applicable).
* **Scooter Logic:** Assign available scooters to delivery orders. Move delivery orders from ready to in-service.
* **State Management:** Manage scooter transitions between free, back, and maintenance lists. Handle finished delivery orders.
* **Tracking:** Calculate delivery finish time, scooter return time, and maintenance end time.

---

### ⚙️ Organizational Guidelines
* **Central Integration:** `RunSimulation()` serves as the master timeline. All feature functions are called from within this loop.
* **Strict Boundaries:** Members only write functions within their assigned domain. Modifying another member's logic requires explicit coordination.
* **Encapsulation:** Every feature must be implemented as a distinct, clear function within its appropriate class.