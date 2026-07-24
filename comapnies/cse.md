# CS Fundamentals Preparation — Part 2 (OS | CN | DBMS | OOP | Computer Architecture)
### Target Companies: Visa | Arista Networks | Qualcomm | Samsung R&D Noida | C-DOT

> This is **Part 2** of your prep series. These 5 companies lean heavily on CS fundamentals because of what they build: Arista (networking hardware/software), Qualcomm (chips/embedded), Samsung R&D (systems software, telecom, mobile), C-DOT (telecom R&D for the government). Expect **at least 1-2 fundamentals questions in every technical round**, sometimes as a "explain X" conversation, sometimes as a scenario ("what happens when you type a URL in the browser").

## How to use this
1. Don't just read — for every concept, try to **explain it out loud in under 90 seconds** as if to an interviewer. If you can't, you don't know it yet.
2. Where a "Company Emphasis" is marked, that topic has been reported frequently in interview experiences for that company — weight your time accordingly.
3. Practice the **follow-up questions** listed — interviewers almost always drill one level deeper than the base definition.
4. This is dense — treat it as a 3-4 week module running in parallel with your DSA weeks 9-12 (revise CS fundamentals in the evenings while doing DSA problems in the morning, for example).

## Company emphasis map
- **Visa**: DBMS (transactions/ACID, indexing) is heavily emphasized — they're a financial company processing transactions at scale. Also OS basics (process/thread, deadlock) and basic networking (HTTP/HTTPS, encryption basics).
- **Arista Networks**: **Computer Networks is the single most important section for you.** Deep OSI/TCP-IP model, routing, switching, TCP internals, congestion control. They will go deeper into CN than the other 4 companies.
- **Qualcomm**: OS (memory management, scheduling, interrupts) and Computer Architecture (cache, pipelining, number systems) are critical — this is a chip/embedded systems company. Basic CN (sockets) also expected.
- **Samsung R&D Noida**: Balanced — OS, CN, DBMS all roughly equal weight, plus strong OOP fundamentals since a lot of their work is systems + application software.
- **C-DOT**: Strong CN emphasis (they're a telecom R&D body) plus OS fundamentals; DBMS is asked but usually lighter.

---

## Table of Contents
1. [Operating Systems](#1-operating-systems)
2. [Computer Networks](#2-computer-networks)
3. [DBMS](#3-dbms)
4. [Object-Oriented Programming](#4-object-oriented-programming)
5. [Computer Architecture & Digital Electronics Basics](#5-computer-architecture--digital-electronics-basics)
6. [Common Scenario-Based Questions](#6-common-scenario-based-questions)
7. [Quick Revision Cheat Sheet](#7-quick-revision-cheat-sheet)

---

## 1. Operating Systems
*(High emphasis: Qualcomm, C-DOT, Visa)*

### 1.1 Process vs Thread
- **Concept**: A process is an independent program in execution with its own memory space; a thread is a lightweight unit of execution within a process that shares memory (code, data, heap) with other threads of the same process but has its own stack, registers, and program counter.
- **Follow-up**: Why are threads faster to create/switch than processes? → Because context switching a thread doesn't require switching the full memory address space (page tables), just the CPU registers/stack — much cheaper.
- **Follow-up**: What is a race condition, and how would you fix one? → Two or more threads accessing shared data concurrently where at least one modifies it, with the outcome depending on timing. Fix with mutex locks, semaphores, or atomic operations.

### 1.2 Process States & Scheduling
- **States**: New → Ready → Running → Waiting/Blocked → Terminated.
- **Scheduling algorithms to know cold**: FCFS, SJF (Shortest Job First), Priority Scheduling, Round Robin, Multilevel Queue.
- **Follow-up**: Why is Round Robin good for time-sharing systems but bad if the time quantum is too small/large? → Too small → excessive context-switching overhead; too large → degenerates to FCFS, hurting responsiveness.
- **Follow-up**: What is Priority Inversion and how is it solved? → A lower-priority task holds a resource needed by a higher-priority task, while a medium-priority task runs freely, effectively inverting priorities. Solved via Priority Inheritance Protocol (temporarily boost the low-priority task's priority).

### 1.3 Process Synchronization
- **Concept**: Coordinating access to shared resources among concurrent processes/threads to avoid race conditions.
- **Tools**: Mutex (binary lock, ownership matters), Semaphore (counting, no ownership — can signal from a different thread), Monitors, Condition Variables.
- **Classic problems to be able to explain**: Producer-Consumer, Readers-Writers, Dining Philosophers.
- **Follow-up**: Difference between mutex and binary semaphore? → Mutex has ownership (only the thread that locked it can unlock it) and is meant for mutual exclusion; a binary semaphore has no ownership concept and is more general-purpose (can be used for signaling between threads).

### 1.4 Deadlock ⭐
- **4 Necessary Conditions**: Mutual Exclusion, Hold and Wait, No Preemption, Circular Wait — deadlock can only occur if ALL 4 hold simultaneously.
- **Handling strategies**: Prevention (break one of the 4 conditions), Avoidance (Banker's Algorithm — know how to explain this one, it comes up a lot), Detection & Recovery, Ignorance (Ostrich algorithm, used by most real OSes since deadlocks are rare).
- **Follow-up**: Explain the Banker's Algorithm in your own words. → Before granting a resource request, simulate whether the system would remain in a "safe state" (i.e., there exists some order in which all processes can finish); only grant the request if it does.
- **Follow-up**: How does a real OS like Linux handle deadlocks? → Mostly ignores them (Ostrich algorithm) since it's expensive to prevent/detect in general-purpose systems; relies on well-designed applications and occasional watchdog/timeout mechanisms.

### 1.5 Memory Management
- **Concepts**: Contiguous allocation (fixed/variable partitioning), Paging, Segmentation, Paging vs Segmentation trade-offs.
- **Paging**: Divides memory into fixed-size frames/pages — eliminates external fragmentation but can cause internal fragmentation.
- **Virtual Memory & Demand Paging**: Programs use virtual addresses translated to physical addresses via page tables; pages loaded into RAM only when needed (demand paging), reducing memory usage.
- **Page Replacement Algorithms**: FIFO, LRU, Optimal (theoretical best, used as a benchmark), Clock/Second-Chance.
- **Follow-up**: What is thrashing? → When the system spends more time swapping pages in/out than doing actual useful work, usually due to too many processes competing for too little physical memory.
- **Follow-up**: Explain TLB (Translation Lookaside Buffer). → A small, fast cache that stores recent virtual-to-physical address translations to avoid walking the page table on every memory access.

### 1.6 File Systems
- **Concepts**: File allocation methods (contiguous, linked, indexed), inodes, directory structures.
- **Follow-up**: What's an inode? → A data structure storing metadata about a file (permissions, owner, size, pointers to data blocks) — but NOT the filename, which is stored in the directory entry.

### 1.7 Interrupts & System Calls
*(Critical for Qualcomm — embedded/chip company)*
- **Concept**: An interrupt is a signal to the CPU indicating an event needs immediate attention (hardware interrupt from a device, or software interrupt/trap for system calls).
- **Follow-up**: Difference between a system call and a function call? → A system call causes a context switch from user mode to kernel mode (privileged) to access OS services, whereas a function call stays within the same privilege level.
- **Follow-up**: What happens during an interrupt? → CPU finishes current instruction, saves current context (registers, PC) onto the stack, jumps to the Interrupt Service Routine (ISR) via the interrupt vector table, executes it, then restores context and resumes.

### 1.8 Concurrency Primitives in Practice
- Know how to explain, at a code level, how you'd implement a producer-consumer queue using a mutex + condition variable, or how you'd use semaphores to limit concurrent access to a resource pool.

---

## 2. Computer Networks
*(Highest emphasis: Arista Networks, C-DOT. Also asked at all others.)*

### 2.1 OSI Model vs TCP/IP Model ⭐
- **OSI (7 layers)**: Physical → Data Link → Network → Transport → Session → Presentation → Application.
- **TCP/IP (4-5 layers)**: Network Interface/Link → Internet → Transport → Application.
- **Follow-up**: Why does the industry use TCP/IP instead of OSI in practice? → TCP/IP was implemented first and is simpler/more practical; OSI is mostly used as a conceptual/teaching reference model.
- **Follow-up**: At which layer do routers, switches, and hubs operate? → Hub: Physical layer (no intelligence, just repeats signal). Switch: Data Link layer (uses MAC addresses). Router: Network layer (uses IP addresses).

### 2.2 TCP vs UDP ⭐
| | TCP | UDP |
|---|-----|-----|
| Connection | Connection-oriented (handshake) | Connectionless |
| Reliability | Reliable (ACKs, retransmission) | Unreliable (best-effort) |
| Ordering | Guaranteed in-order delivery | No ordering guarantee |
| Speed | Slower (overhead) | Faster (minimal overhead) |
| Use case | HTTP, File transfer, Email | DNS, Video streaming, Gaming, VoIP |

- **Follow-up**: Why does DNS use UDP but sometimes fall back to TCP? → DNS queries are small and need to be fast (UDP's low overhead is ideal); it falls back to TCP when the response is too large for a single UDP packet (e.g., zone transfers, DNSSEC) or when reliability is critical.

### 2.3 TCP 3-Way Handshake & Connection Termination ⭐
- **Handshake**: SYN (client) → SYN-ACK (server) → ACK (client). Establishes sequence numbers for reliable, ordered delivery.
- **Termination**: FIN → ACK → FIN → ACK (4-way, since each side must close independently) — this is why TCP is described as "full-duplex" (both directions closed separately).
- **Follow-up**: What is the TIME_WAIT state and why does it exist? → After closing, the side that sent the last ACK waits (typically 2×MSL) before fully releasing the connection, to make sure any delayed/duplicate packets from the old connection don't interfere with a new connection reusing the same port.

### 2.4 Congestion Control & Flow Control ⭐
*(Arista will likely go deep here — this is core to networking hardware)*
- **Flow control**: Receiver-driven, prevents a fast sender from overwhelming a slow receiver (sliding window with the receiver's advertised window size).
- **Congestion control**: Sender-driven, prevents overwhelming the network itself. Key algorithms: Slow Start (exponential growth of congestion window until a threshold), Congestion Avoidance (linear/additive growth after threshold), Fast Retransmit & Fast Recovery (on 3 duplicate ACKs, assume packet loss without waiting for a full timeout).
- **Follow-up**: What's the difference between flow control and congestion control? → Flow control protects the receiver from being overwhelmed; congestion control protects the network itself from being overwhelmed.

### 2.5 IP Addressing & Subnetting
- **IPv4**: 32-bit address, dotted decimal, classes A/B/C historically, now CIDR (Classless Inter-Domain Routing) notation like `192.168.1.0/24`.
- **Subnet mask**: Determines network portion vs host portion of an address.
- **Follow-up**: Given `192.168.1.0/26`, how many usable hosts per subnet? → /26 leaves 6 bits for hosts → 2^6 = 64 addresses, minus 2 (network + broadcast) = 62 usable hosts. Practice a few of these — subnetting math questions show up often at Arista/C-DOT.
- **Private vs Public IP**: Private ranges (10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16) aren't routable on the public internet — this is where NAT comes in.

### 2.6 NAT (Network Address Translation)
- **Concept**: Translates private IP addresses to a single (or few) public IP address(es) so multiple devices on a LAN can share one public IP for internet access.
- **Follow-up**: How does NAT keep track of which internal device a response belongs to? → It maintains a translation table mapping (private IP, private port) ↔ (public IP, public port) for each active connection.

### 2.7 DNS
- **Concept**: Translates human-readable domain names into IP addresses via a distributed, hierarchical system (Root servers → TLD servers → Authoritative servers).
- **Follow-up**: Walk through what happens when you type a URL and hit enter (classic question, see Section 6).
- **Follow-up**: What is DNS caching and where does it happen? → At multiple levels — browser cache, OS resolver cache, ISP resolver cache — to reduce repeated lookups and latency.

### 2.8 HTTP/HTTPS
- **HTTP**: Stateless, request-response protocol. Know the common methods (GET, POST, PUT, DELETE, PATCH) and status code categories (1xx info, 2xx success, 3xx redirect, 4xx client error, 5xx server error).
- **HTTPS**: HTTP over TLS/SSL — encrypts data in transit, provides authentication (via certificates) and integrity.
- **Follow-up**: Explain the TLS handshake at a high level. → Client Hello (supported ciphers) → Server Hello (chosen cipher + certificate) → Client verifies certificate against a trusted CA → Key exchange (often via Diffie-Hellman) to derive a shared symmetric session key → Both sides switch to encrypted communication using that symmetric key (asymmetric crypto is used only to establish the shared key, since it's computationally expensive for bulk data).
- **Follow-up**: Why not use asymmetric encryption for the whole session? → It's much slower computationally than symmetric encryption; asymmetric is used only briefly for secure key exchange/authentication, then a fast symmetric cipher (like AES) handles bulk data.

### 2.9 Switching & Routing
*(Core Arista territory)*
- **Switch**: Operates at Layer 2, forwards frames based on MAC address table (learned by observing source MAC addresses of incoming frames), builds this table dynamically.
- **Router**: Operates at Layer 3, forwards packets based on IP routing tables, connects different networks/subnets.
- **Routing protocols to know at a conceptual level**: Distance Vector (RIP — each router shares its routing table with neighbors) vs Link State (OSPF — each router builds a full map of the network topology and computes shortest paths, e.g., via Dijkstra's algorithm).
- **Follow-up**: What is ARP (Address Resolution Protocol)? → Resolves an IP address to a MAC address within a local network segment, via broadcast request and unicast reply.
- **Follow-up**: What's a VLAN and why use one? → A Virtual LAN logically segments a physical network into multiple broadcast domains for security/organization/traffic management, without needing separate physical switches.

### 2.10 Sockets (practical, expect a coding-adjacent question at Qualcomm/Arista)
- Know the basic client-server socket lifecycle: `socket()` → `bind()` → `listen()` → `accept()` (server) and `socket()` → `connect()` (client), then `send()`/`recv()` on both sides.

---

## 3. DBMS
*(Highest emphasis: Visa — financial transaction processing company)*

### 3.1 ACID Properties ⭐
- **Atomicity**: A transaction is all-or-nothing — either all operations complete or none do.
- **Consistency**: A transaction brings the database from one valid state to another, preserving all defined rules/constraints.
- **Isolation**: Concurrent transactions don't interfere with each other's intermediate states.
- **Durability**: Once committed, a transaction's changes persist even after a system crash (typically via write-ahead logging).
- **Follow-up (Visa-specific)**: Why is Atomicity critical for a payment system? → If a transfer debits one account but a crash happens before crediting the other, you'd lose money — atomicity ensures the whole operation rolls back if any part fails.

### 3.2 Isolation Levels & Concurrency Issues
- **Levels (weakest to strongest)**: Read Uncommitted → Read Committed → Repeatable Read → Serializable.
- **Anomalies they prevent**: Dirty Read (reading uncommitted data), Non-Repeatable Read (re-reading a row gives different values within the same transaction), Phantom Read (a query run twice returns a different set of rows due to another transaction's insert/delete).
- **Follow-up**: Which isolation level would you use for a banking system and why? → Usually Serializable or Repeatable Read for critical financial operations, trading off some concurrency/performance for strict correctness.

### 3.3 Indexing ⭐
- **Concept**: A data structure (commonly a B-Tree or B+ Tree) that speeds up data retrieval at the cost of extra storage and slower writes (since indexes must be updated too).
- **B-Tree vs B+ Tree**: B+ Tree stores all actual data in leaf nodes (internal nodes only store keys for navigation) and leaf nodes are linked together — making range queries and full scans efficient; this is why most databases use B+ Trees for indexes.
- **Follow-up**: When would an index hurt performance instead of help? → On tables with heavy write/insert/update load, since every index must be updated on every write, and on columns with low cardinality (few distinct values) where the index doesn't narrow down rows much.
- **Follow-up**: What is a clustered vs non-clustered index? → Clustered index determines the physical storage order of the table data itself (only one per table); non-clustered index is a separate structure with pointers back to the actual rows (can have many per table).

### 3.4 Normalization ⭐
- **1NF**: Atomic values, no repeating groups.
- **2NF**: 1NF + no partial dependency (non-key attributes depend on the WHOLE primary key, relevant for composite keys).
- **3NF**: 2NF + no transitive dependency (non-key attributes depend only on the primary key, not on other non-key attributes).
- **BCNF**: Stronger version of 3NF — every determinant must be a candidate key.
- **Follow-up**: Why would you deliberately denormalize a database? → To improve read performance for reporting/analytics workloads by reducing the number of joins needed, at the cost of some data redundancy and write complexity.

### 3.5 Keys
- **Primary Key**: Uniquely identifies each row, cannot be null.
- **Foreign Key**: References a primary key in another table, enforces referential integrity.
- **Candidate Key**: Any column (or combination) that could qualify as a primary key.
- **Composite Key**: A primary key made of multiple columns together.

### 3.6 Joins ⭐
- **INNER JOIN**: Only matching rows from both tables.
- **LEFT JOIN**: All rows from left table + matching rows from right (nulls if no match).
- **RIGHT JOIN**: All rows from right table + matching rows from left.
- **FULL OUTER JOIN**: All rows from both tables, matched where possible.
- **SELF JOIN**: A table joined with itself (e.g., finding an employee's manager who is also in the same employee table).
- Practice writing SQL for these — some interviewers ask you to write a query live (e.g., "find the second highest salary", "find duplicate rows").

### 3.7 Transactions & Locking
- **Concept**: A transaction is a sequence of operations executed as a single logical unit of work.
- **Locking**: Shared (read) locks vs Exclusive (write) locks; Two-Phase Locking (2PL) protocol — a transaction acquires all locks it needs before releasing any (growing phase, then shrinking phase) to guarantee serializability.
- **Follow-up**: What is a deadlock in the context of a database, and how is it typically resolved? → Two transactions each holding a lock the other needs; the DBMS typically detects this via a wait-for graph and resolves it by aborting one transaction (the "victim").

### 3.8 SQL vs NoSQL (conceptual, likely to come up)
- **SQL**: Structured schema, ACID guarantees, relational (joins), vertical scaling primarily.
- **NoSQL**: Flexible/schema-less, often eventual consistency (BASE model instead of ACID), horizontal scaling, better for unstructured/high-volume data (document stores like MongoDB, key-value stores like Redis, column stores like Cassandra).
- **Follow-up**: When would you choose NoSQL over SQL? → When you need horizontal scalability for massive volumes of semi-structured data with flexible schemas and can tolerate eventual consistency (e.g., a social media feed) — versus SQL when you need strict consistency and complex relational queries (e.g., a banking ledger).

---

## 4. Object-Oriented Programming
*(Emphasis: Samsung R&D, Visa — asked as a quick conceptual round almost everywhere)*

### 4.1 The Four Pillars
- **Encapsulation**: Bundling data and methods that operate on it, restricting direct access via access modifiers (private/protected/public).
- **Abstraction**: Hiding implementation details, exposing only necessary functionality (e.g., an abstract class or interface).
- **Inheritance**: A class acquiring properties/behaviors of a parent class, enabling code reuse.
- **Polymorphism**: One interface, many implementations — Compile-time (method overloading) vs Runtime (method overriding via virtual functions/dynamic dispatch).

### 4.2 Common Follow-ups
- **Follow-up**: Difference between abstraction and encapsulation? → Abstraction is about hiding complexity/showing only what's necessary (a design-level concept — "what" is exposed); encapsulation is about bundling data with methods and controlling access (an implementation-level concept — "how" access is restricted).
- **Follow-up**: What is Virtual Function / Dynamic Dispatch (C++ specific, common at Qualcomm)? → A function declared in a base class that can be overridden in a derived class, resolved at runtime based on the actual object type (not the pointer/reference type) — implemented via a vtable (virtual table) mechanism.
- **Follow-up**: Diamond problem in multiple inheritance — what is it and how is it solved? → When a class inherits from two classes that both inherit from a common base, causing ambiguity about which base's members to use. Solved in C++ via virtual inheritance.
- **Follow-up**: Difference between an abstract class and an interface? → An abstract class can have both implemented and unimplemented methods plus state (member variables); an interface (traditionally) only declares method signatures with no implementation or state — though modern languages (Java 8+) blur this with default methods.

### 4.3 SOLID Principles (good to mention if asked about design)
- **S**ingle Responsibility, **O**pen/Closed, **L**iskov Substitution, **I**nterface Segregation, **D**ependency Inversion — know one-line definitions and a simple example for each.

---

## 5. Computer Architecture & Digital Electronics Basics
*(High emphasis: Qualcomm — this is a chip design company)*

### 5.1 Number Systems & Conversions
- Be fast and error-free converting between binary, decimal, octal, hexadecimal — and know 1's complement vs 2's complement representation for negative numbers.
- **Follow-up**: Why does 2's complement dominate over 1's complement in modern hardware? → 2's complement has a single representation for zero (1's complement has +0 and -0), and arithmetic (addition/subtraction) works uniformly without special-casing signs.

### 5.2 Cache Memory & Memory Hierarchy ⭐
- **Hierarchy**: Registers → L1 Cache → L2 Cache → L3 Cache → RAM → Disk/SSD (increasing size, increasing latency, decreasing cost per byte, as you go down).
- **Concepts**: Cache hit/miss, spatial locality (nearby memory likely to be accessed soon) vs temporal locality (recently accessed memory likely to be accessed again), cache mapping (direct-mapped, set-associative, fully associative), write policies (write-through vs write-back).
- **Follow-up**: What is cache coherence and why does it matter in multi-core systems? → When multiple cores each have their own cache, they might have different (stale) copies of the same memory location; coherence protocols (e.g., MESI) ensure all cores see a consistent view of shared memory.

### 5.3 Pipelining
- **Concept**: Overlapping execution of multiple instructions (Fetch, Decode, Execute, Memory access, Write-back stages) to improve throughput, similar to an assembly line.
- **Hazards**: Structural (resource conflict), Data (an instruction depends on the result of a prior one still in the pipeline), Control (branch instructions cause uncertainty about the next instruction to fetch).
- **Follow-up**: How does branch prediction help pipelining? → It guesses the outcome of a conditional branch before it's resolved, allowing the pipeline to keep fetching/executing speculatively instead of stalling — a misprediction requires flushing the pipeline and starting over from the correct path.

### 5.4 Interrupts vs Polling
- **Polling**: CPU repeatedly checks a device's status — wastes CPU cycles if the device is rarely ready.
- **Interrupts**: Device signals the CPU only when it needs attention — more efficient, especially for infrequent events.

---

## 6. Common Scenario-Based Questions
*(These integrate multiple topics — a favorite style for Samsung/Arista final rounds)*

1. **"What happens when you type a URL into a browser and press Enter?"** — Practice this end-to-end: DNS resolution (browser cache → OS cache → resolver → root/TLD/authoritative servers) → TCP 3-way handshake with the resolved IP → TLS handshake if HTTPS → HTTP GET request sent → Server processes request (may hit app server → DB) → HTTP response sent back → Browser parses HTML, fetches additional resources (CSS/JS/images, often in parallel over multiple connections) → Renders the page.
2. **"How would you design a system to handle 10,000 concurrent requests?"** — Touches load balancing, horizontal scaling, connection pooling, caching, async I/O vs thread-per-request models.
3. **"A transaction is deducting money from one account and adding to another — how do you ensure it's never inconsistent even if the server crashes mid-way?"** — ACID atomicity, write-ahead logging, rollback on failure.
4. **"Two devices on the same network want to communicate — walk through what happens at each layer."** — Good chance to demonstrate OSI model fluency end-to-end with ARP, MAC addressing, IP routing.
5. **"How does your OS decide which process runs next?"** — Scheduling algorithm explanation + trade-offs for interactive vs batch systems.

---

## 7. Quick Revision Cheat Sheet
*(Use this the night before an interview — one line per concept, if you can't expand on any of these, go back to that section)*

**OS**: Process≠Thread (memory sharing) · Deadlock needs all 4 conditions · Banker's Algorithm = simulate safe state before granting · Paging removes external fragmentation · TLB caches page table lookups · Thrashing = too much swapping, too little real work.

**CN**: OSI 7 layers vs TCP/IP 4 layers · TCP=reliable+ordered, UDP=fast+no guarantee · 3-way handshake (SYN, SYN-ACK, ACK) · Congestion control ≠ Flow control (network vs receiver) · NAT maps private↔public IP · DNS is hierarchical+cached at multiple levels · Switch=Layer2/MAC, Router=Layer3/IP · TLS handshake uses asymmetric crypto only to exchange a symmetric session key.

**DBMS**: ACID = Atomicity, Consistency, Isolation, Durability · Isolation levels prevent dirty/non-repeatable/phantom reads · B+ Tree indexes make range queries fast · Normalization reduces redundancy (1NF→2NF→3NF→BCNF) · 2PL guarantees serializability · SQL=structured+ACID, NoSQL=flexible+scalable.

**OOP**: Encapsulation=bundle+restrict access · Abstraction=hide complexity · Inheritance=reuse · Polymorphism=one interface many forms (overloading=compile-time, overriding=runtime via vtable).

**Architecture**: Memory hierarchy = faster+smaller+costlier as you go up · Cache hit/miss + locality (spatial/temporal) · Pipelining overlaps instruction stages · Branch prediction avoids pipeline stalls · Interrupts > Polling for efficiency.

---

## What's next
Once you've gone through this, tell me and we'll build:
- **Part 3**: Aptitude & Quant practice list (time-speed-distance, permutations/combinations, probability, logical reasoning — common in Visa/Samsung's first-round online assessments)
- **Part 4**: HR/Behavioral question bank + company-specific culture notes
- **Part 5**: Mock interview problem sets, one tailored per company, timed like a real round