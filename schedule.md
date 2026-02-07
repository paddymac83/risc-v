# 6-Month Detailed Learning Schedule
## AI Compiler Engineer for RISC-V & ARM (Part-Time, Full-Time Employment Compatible)

**Target:** 12-14 hours/week sustained learning
**Your Background:** 15 years AI/ML production experience
**End Goal:** Compiler Engineer specializing in LLM optimization on RISC-V and ARM edge devices

---

## Schedule Overview

**Time Commitment:**
- **Weekday Evenings:** 2 hours × 3 days = 6 hours
- **Saturday Morning:** 4-5 hours deep work
- **Sunday Afternoon:** 2-3 hours review/lighter work
- **Total:** 12-14 hours/week

**Rest Days:** 
- 2 weekday evenings completely off
- Friday evenings always off (social life)
- 1 week off every 8 weeks (burnout prevention)

---

## 🎯 LLM Optimization Focus - Dual Architecture Approach

**This curriculum emphasizes Large Language Model (LLM) optimization on BOTH RISC-V and ARM edge devices.**

You'll learn fundamental compiler skills while comparing and contrasting two critical architectures:
- **RISC-V:** Open, extensible, growing in edge AI
- **ARM:** Dominant, mature ecosystem, established market

This dual-architecture approach makes you significantly more employable while providing deep insights into optimization trade-offs.

**Key Topics Covered:**
- **Architecture Comparison** - RISC-V vs ARM for LLM workloads
- **Vector Extensions** - RVV (RISC-V) vs NEON/SVE2 (ARM)
- **Attention Optimization** - Platform-specific strategies for transformers
- **Comparative Benchmarking** - Measure performance differences scientifically
- **Cross-Platform Skills** - Techniques that transfer between architectures
- **Quantization Strategies** - INT8/INT4 on both platforms

**Target Models:**
- GPT-2 (124M parameters) - Optimized for BOTH platforms
- TinyLlama/DistilGPT2 (1.1B) - Edge deployment comparison
- BERT-Base - Encoder architecture on both

**Real-World Application:**
By the end, you'll deliver comparative benchmarks showing:
- Performance comparison: RISC-V vs ARM for LLMs
- Optimization strategies that work on both
- When to choose each architecture
- Portfolio demonstrating expertise in BOTH ecosystems

**Career Advantage:**
- ARM skills → Immediate job market (200+ UK positions)
- RISC-V skills → Future positioning (growing market)
- Comparative analysis → Consulting differentiation
- Dual expertise → Unique, valuable skillset

---

## Month 1: Compiler Foundations & Setup

### Week 1: Environment Setup & Compiler Basics

**Monday Evening (2 hours) - Setup Day**
- [ ] Install Ubuntu 22.04 LTS or 24.04 LTS (if not already)
- [ ] Update system: `sudo apt update && sudo apt upgrade`
- [ ] Install build essentials: `sudo apt install build-essential git cmake ninja-build`
- [ ] Install Python 3.10+: `sudo apt install python3 python3-pip`
- [ ] Setup VSCode or preferred editor
- [ ] Create GitHub account (if needed) and setup SSH keys
- [ ] Clone learning repository template (create your own)

**Wednesday Evening (2 hours) - Reading**
- [ ] Read Crafting Interpreters Introduction and Chapter 1
- [ ] Understand: What is a compiler? Phases of compilation
- [ ] Take notes in markdown (setup notes repo)
- [ ] Watch: "Introduction to Compilers" (any good YouTube intro, ~30 min)
- [ ] Setup reading tracker (markdown file with chapters completed)

**Thursday Evening (2 hours) - First Code**
- [ ] Crafting Interpreters Chapter 2: Scanning
- [ ] Start implementing scanner for toy language
- [ ] Write first 100 lines of code
- [ ] Test with simple input: `var x = 10;`
- [ ] Commit to GitHub

**Saturday Morning (4 hours) - Deep Implementation**
- [ ] Crafting Interpreters Chapters 3-4: Expressions and Parsing
- [ ] Implement recursive descent parser
- [ ] Handle: literals, unary, binary expressions
- [ ] Write tests for parser
- [ ] Target: 300+ lines of working code
- [ ] Debug and fix any issues

**Sunday Afternoon (2 hours) - Review & Planning**
- [ ] Review week's code
- [ ] Refactor and clean up
- [ ] Update notes with key learnings
- [ ] Read ahead: Chapter 5 preview
- [ ] Plan next week's schedule
- [ ] Weekly review: What worked? What didn't?

**Resources This Week:**
- Crafting Interpreters: https://craftinginterpreters.com/
- Stanford CS143 Lecture 1 (YouTube)
- "Compilers: Principles, Techniques, and Tools" - Chapter 1 (optional)

**Deliverable:** Scanner + Parser implementation (~400 lines)

---

### Week 2: Building Your First Compiler

**Monday Evening (2 hours)**
- [ ] Crafting Interpreters Chapter 5: Statements and State
- [ ] Implement variable declarations
- [ ] Handle assignment expressions
- [ ] Test: `var a = 1; var b = a + 2;`

**Wednesday Evening (2 hours)**
- [ ] Chapter 6: Evaluating Expressions
- [ ] Implement interpreter/evaluator
- [ ] Handle all expression types
- [ ] Run first programs successfully

**Thursday Evening (2 hours)**
- [ ] Chapter 7: Statements and Control Flow
- [ ] Implement if statements
- [ ] Implement while loops
- [ ] Test with Fibonacci/factorial programs

**Saturday Morning (4 hours)**
- [ ] Chapter 8: Functions
- [ ] Implement function declarations
- [ ] Handle function calls and return values
- [ ] Implement call stack
- [ ] Write recursive function tests

**Sunday Afternoon (2 hours)**
- [ ] Write comprehensive test suite
- [ ] Document your implementation
- [ ] Create README with examples
- [ ] Blog post outline: "Building My First Compiler"
- [ ] Weekly review and planning

**Deliverable:** Working interpreter with functions (~800 lines)

---

### Week 3: Advanced Compiler Concepts

**Monday Evening (2 hours)**
- [ ] Read "Engineering a Compiler" Chapter 1
- [ ] Understand IR (Intermediate Representation) concepts
- [ ] Study three-address code
- [ ] Design simple IR for your compiler

**Wednesday Evening (2 hours)**
- [ ] Chapter 9: Closures (Crafting Interpreters)
- [ ] Implement lexical scoping
- [ ] Handle closure captures
- [ ] Test nested function scenarios

**Thursday Evening (2 hours)**
- [ ] Add basic optimizations to your compiler
- [ ] Constant folding: `2 + 3` → `5`
- [ ] Dead code elimination
- [ ] Measure improvement

**Saturday Morning (4 hours)**
- [ ] Design code generation phase
- [ ] Target: pseudo-assembly or simple stack machine
- [ ] Generate code for expressions
- [ ] Generate code for control flow
- [ ] End-to-end: source → assembly

**Sunday Afternoon (2 hours)**
- [ ] Test complete pipeline
- [ ] Run benchmark programs
- [ ] Document code generation strategy
- [ ] Write notes on optimizations
- [ ] Weekly review

**Deliverable:** Compiler with code generation (~1200 lines)

---

### Week 4: LLVM Introduction

**Monday Evening (2 hours) - LLVM Setup**
- [ ] Install LLVM 18.0: `sudo apt install llvm-18 clang-18`
- [ ] Or build from source (recommended for learning)
- [ ] Clone LLVM: `git clone https://github.com/llvm/llvm-project.git`
- [ ] Read LLVM Getting Started guide
- [ ] Explore LLVM tools: llc, opt, llvm-dis

**Wednesday Evening (2 hours)**
- [ ] Read LLVM Language Reference Manual (sections 1-3)
- [ ] Generate LLVM IR from C: `clang -S -emit-llvm hello.c`
- [ ] Study IR structure: functions, basic blocks, instructions
- [ ] Write simple IR by hand (use text editor)
- [ ] Assemble and run: `llvm-as test.ll -o test.bc && lli test.bc`

**Thursday Evening (2 hours)**
- [ ] LLVM IR deep dive: Types and constants
- [ ] SSA form understanding
- [ ] PHI nodes: what and why
- [ ] Write IR for: fibonacci, factorial, loops
- [ ] Practice reading compiler-generated IR

**Saturday Morning (4 hours)**
- [ ] Write first LLVM pass (New Pass Manager)
- [ ] Follow tutorial: https://llvm.org/docs/WritingAnLLVMNewPMPass.html
- [ ] Implement: Function name printer pass
- [ ] Build pass as plugin
- [ ] Run: `opt -load-pass-plugin=YourPass.so -passes=yourpass test.ll`
- [ ] Debug and fix issues

**Sunday Afternoon (3 hours)**
- [ ] Write second pass: Instruction counter
- [ ] Count all instructions in functions
- [ ] Print statistics
- [ ] Test on multiple programs
- [ ] Document pass architecture
- [ ] Monthly review: Completed Month 1!
- [ ] Celebrate progress: You've built a compiler AND written LLVM passes!

**Deliverable:** 2 working LLVM passes + understanding of IR

---

## Month 2: LLVM Deep Dive & Assembly (RISC-V + ARM)

### Week 5: LLVM Optimization Passes

**Monday Evening (2 hours)**
- [ ] Read "Getting Started with LLVM Core Libraries" Chapters 1-2
- [ ] Study LLVM pass infrastructure
- [ ] Understand: Function passes, Module passes, Analysis passes
- [ ] Read existing pass code: lib/Transforms/Utils/Mem2Reg.cpp

**Wednesday Evening (2 hours)**
- [ ] Implement constant propagation pass
- [ ] Detect constants: `x = 5; y = x + 3;`
- [ ] Propagate and simplify
- [ ] Write test cases
- [ ] Verify correctness

**Thursday Evening (2 hours)**
- [ ] Implement dead code elimination pass
- [ ] Mark reachable code
- [ ] Remove unreachable blocks
- [ ] Test with if(false) scenarios
- [ ] Measure code size reduction

**Saturday Morning (5 hours)**
- [ ] Implement simple loop optimization
- [ ] Loop Invariant Code Motion (LICM)
- [ ] Detect loop-invariant computations
- [ ] Hoist them outside loop
- [ ] Benchmark on matrix operations
- [ ] Compare with -O2 optimizations

**Sunday Afternoon (2 hours)**
- [ ] Study dataflow analysis
- [ ] Read about reaching definitions
- [ ] Implement live variable analysis (basic)
- [ ] Document your passes
- [ ] Weekly review

**Deliverable:** 3 optimization passes with benchmarks

---

### Week 6: LLVM Backend Basics

**Monday Evening (2 hours)**
- [ ] Read "Writing an LLVM Backend" (LLVM docs)
- [ ] Understand target description
- [ ] Study TableGen basics
- [ ] Look at simple backend: Mips or Sparc

**Wednesday Evening (2 hours)**
- [ ] Study instruction selection
- [ ] DAG (Directed Acyclic Graph) patterns
- [ ] SelectionDAG overview
- [ ] Read: lib/CodeGen/SelectionDAG/

**Thursday Evening (2 hours)**
- [ ] Study register allocation
- [ ] Read about graph coloring
- [ ] Understand register classes
- [ ] Examine: lib/CodeGen/RegAllocGreedy.cpp (overview)

**Saturday Morning (4 hours)**
- [ ] Deep dive into x86 backend (familiar architecture)
- [ ] Study: lib/Target/X86/X86InstrInfo.td
- [ ] Understand instruction definitions
- [ ] Study calling convention: X86CallingConv.td
- [ ] Trace: C code → LLVM IR → x86 assembly
- [ ] Use -debug flag to see selection

**Sunday Afternoon (2 hours)**
- [ ] Install RISC-V toolchain: 
  ```
  sudo apt install gcc-riscv64-linux-gnu
  sudo apt install qemu-user qemu-system-misc
  ```
- [ ] Build "Hello World" for RISC-V
- [ ] Run in QEMU: `qemu-riscv64 ./hello`
- [ ] Examine assembly output
- [ ] Weekly review

**Deliverable:** Understanding of backend architecture + RISC-V setup

---

### Week 7: Assembly Programming - RISC-V & ARM Introduction

**Monday Evening (2 hours) - RISC-V Fundamentals**
- [ ] Read "The RISC-V Reader" Chapters 1-2
- [ ] Understand RISC-V philosophy: Simple, modular, extensible
- [ ] Study RV64I base instruction set (40 instructions)
- [ ] Learn register names: x0-x31, ABI names (a0-a7, t0-t6, s0-s11)
- [ ] Note: RISC-V has 32 general-purpose registers

**Wednesday Evening (2 hours) - ARM Fundamentals**
- [ ] Read ARM Architecture Reference Manual (ARMv8-A overview)
- [ ] Or use "ARM Assembly Language" by William Hohl
- [ ] Understand ARM philosophy: Performance, power efficiency
- [ ] Study AArch64 instruction set basics
- [ ] Learn register names: x0-x30, sp, pc
- [ ] Note key differences: ARM has 31 GPRs + special registers

**Thursday Evening (2 hours) - Comparative Programming**
- [ ] Write same program in BOTH assembly languages:
  - [ ] Add two numbers (RISC-V)
  - [ ] Add two numbers (ARM)
  - [ ] Compare instruction count, clarity
- [ ] Fibonacci (iterative) in both
- [ ] Document differences in syntax and approach

**Saturday Morning (5 hours) - Deep Comparative Work**
- [ ] RISC-V programs (2.5 hours):
  - [ ] Factorial (recursive)
  - [ ] Array sum
  - [ ] String length
  - [ ] Assemble: `riscv64-linux-gnu-as -o prog.o prog.s`
  - [ ] Run in QEMU: `qemu-riscv64 prog`

- [ ] ARM programs (2.5 hours):
  - [ ] Same algorithms in ARM assembly
  - [ ] Factorial (recursive)
  - [ ] Array sum
  - [ ] String length
  - [ ] Assemble: `aarch64-linux-gnu-as -o prog.o prog.s`
  - [ ] Run in QEMU: `qemu-aarch64 prog`

**Sunday Afternoon (3 hours) - Analysis & Comparison**
- [ ] Create comparison table:
  | Feature | RISC-V | ARM |
  |---------|---------|-----|
  | Register count | 32 GPRs | 31 GPRs + SP |
  | Instruction encoding | Fixed 32-bit | Mostly fixed 32-bit |
  | Load/Store | Load/Store only | Load/Store only |
  | Complexity | Minimal | More features |
- [ ] Study calling conventions (both)
- [ ] Compare stack frame layouts
- [ ] Weekly review

**Deliverable:** 6+ programs in BOTH RISC-V and ARM assembly + comparison document

---

### Week 8: LLVM Backend Comparison - RISC-V & ARM

**Monday Evening (2 hours) - RISC-V Backend**
- [ ] Study LLVM RISC-V backend: lib/Target/RISCV/
- [ ] Read: RISCVInstrInfo.td
- [ ] Understand TableGen for RISC-V
- [ ] Map assembly instructions to TableGen definitions

**Wednesday Evening (2 hours) - ARM Backend**
- [ ] Study LLVM ARM backend: lib/Target/AArch64/
- [ ] Read: AArch64InstrInfo.td
- [ ] Compare to RISC-V TableGen approach
- [ ] Note differences in complexity and structure

**Thursday Evening (2 hours) - Code Generation Comparison**
- [ ] Generate RISC-V from C:
  ```bash
  clang --target=riscv64 -S -O2 test.c -o test_rv.s
  ```
- [ ] Generate ARM from same C:
  ```bash
  clang --target=aarch64 -S -O2 test.c -o test_arm.s
  ```
- [ ] Compare generated assembly
- [ ] Identify architectural differences
- [ ] Document optimization choices

**Saturday Morning (5 hours) - Backend Deep Dive**
- [ ] RISC-V backend (2.5 hours):
  - [ ] Study RISCVISelLowering.cpp
  - [ ] Trace IR → SelectionDAG → MachineInstr
  - [ ] Modify simple pattern in RISCVInstrInfo.td
  - [ ] Example: Custom pattern for constant loading
  - [ ] Rebuild and test

- [ ] ARM backend (2.5 hours):
  - [ ] Study AArch64ISelLowering.cpp  
  - [ ] Trace same IR → Assembly on ARM
  - [ ] Compare instruction selection strategies
  - [ ] Note ARM-specific optimizations

**Sunday Afternoon (3 hours) - Comparative Analysis**
- [ ] Create comparison document:
  ```markdown
  # LLVM Backend Comparison: RISC-V vs ARM
  
  ## Code Complexity
  - RISC-V backend: ~X files, Y lines
  - ARM backend: ~X files, Y lines
  
  ## Instruction Selection
  - RISC-V: Simpler patterns, fewer special cases
  - ARM: More complex patterns, more optimizations
  
  ## Register Allocation
  - RISC-V: 32 registers, simpler constraints
  - ARM: 31 registers, more calling convention variants
  ```
- [ ] Monthly review: Month 2 complete!
- [ ] Reflect on dual-architecture learning

**Deliverable:** Comparative analysis of RISC-V vs ARM backends + modified backend code

---

## Month 3: Vector Programming (RVV & NEON) + TVM Introduction

### Week 9: Vector Extensions - RVV (RISC-V) & NEON (ARM)

**Monday Evening (2 hours) - RVV Fundamentals**
- [ ] Download RISC-V Vector Extension Spec v1.0
- [ ] Read: https://github.com/riscv/riscv-v-spec Chapters 1-2
- [ ] Understand: VLEN (vector length), SEW (element width), LMUL (register grouping)
- [ ] Key concept: Vector-length agnostic programming
- [ ] Install RVV-capable toolchain

**Wednesday Evening (2 hours) - ARM NEON Fundamentals**
- [ ] Read ARM NEON Programmer's Guide
- [ ] Or "ARM NEON Optimization" guide
- [ ] Understand: 128-bit fixed-width SIMD vectors
- [ ] Learn NEON register naming: v0-v31 (128-bit each)
- [ ] Study NEON intrinsics: `#include <arm_neon.h>`
- [ ] Compare philosophies: RVV (variable) vs NEON (fixed)

**Thursday Evening (2 hours) - RVV Programming**
- [ ] Write first RVV programs using intrinsics:
  ```c
  #include <riscv_vector.h>
  void vector_add_rvv(float *a, float *b, float *c, size_t n) {
      size_t vl;
      for (size_t i = 0; i < n; i += vl) {
          vl = vsetvl_e32m1(n - i);
          vfloat32m1_t va = vle32_v_f32m1(&a[i], vl);
          vfloat32m1_t vb = vle32_v_f32m1(&b[i], vl);
          vfloat32m1_t vc = vfadd_vv_f32m1(va, vb, vl);
          vse32_v_f32m1(&c[i], vc, vl);
      }
  }
  ```
- [ ] Test on QEMU with RVV support

**Saturday Morning (5 hours) - Dual Implementation**
- [ ] RVV Programs (2.5 hours):
  - [ ] Vector addition (float32, int32)
  - [ ] Dot product with reduction
  - [ ] SAXPY: y = a*x + y
  - [ ] Experiment with LMUL=1,2,4
  - [ ] Benchmark vs scalar code

- [ ] NEON Programs (2.5 hours):
  - [ ] Same operations using NEON intrinsics:
  ```c
  #include <arm_neon.h>
  void vector_add_neon(float *a, float *b, float *c, size_t n) {
      for (size_t i = 0; i < n; i += 4) {  // Fixed: 4 floats per vector
          float32x4_t va = vld1q_f32(&a[i]);
          float32x4_t vb = vld1q_f32(&b[i]);
          float32x4_t vc = vaddq_f32(va, vb);
          vst1q_f32(&c[i], vc);
      }
  }
  ```
  - [ ] Dot product using NEON
  - [ ] SAXPY implementation
  - [ ] Test on RPi 4 or QEMU-ARM

**Sunday Afternoon (3 hours) - Comparative Analysis**
- [ ] Create performance/feature comparison:
  | Feature | RVV | NEON |
  |---------|-----|------|
  | Vector width | Variable (VLEN) | Fixed 128-bit |
  | Adaptability | High (future-proof) | Limited |
  | Compiler support | Maturing | Excellent |
  | Code portability | Very high | Medium |
  
- [ ] Benchmark same operations:
  - Vector add performance
  - Dot product throughput
  - Note hardware differences affect comparison
- [ ] Document learnings in blog post draft
- [ ] Weekly review

**Resources:**
- RVV: https://github.com/riscv/riscv-v-spec
- NEON: ARM Developer Guide (https://developer.arm.com/architectures/instruction-sets/intrinsics/)

**Deliverable:** Vector programs on BOTH platforms + performance comparison doc

---

### Week 10: Advanced Vector Programming & Hardware Setup

**Monday Evening (2 hours) - RVV Advanced Features**
- [ ] Study vector masking (RVV Chapter 5)
- [ ] Implement conditional vector operations with masking
- [ ] Vector compare operations
- [ ] Masked arithmetic

**Wednesday Evening (2 hours) - NEON Advanced Features**
- [ ] Study NEON comparison and selection
- [ ] Use `vcmpq_*` family of intrinsics
- [ ] Implement conditional operations in NEON
- [ ] Compare to RVV masking approach

**Thursday Evening (2 hours) - INT8 Quantization Kernels**
- [ ] RVV: Implement INT8 vector multiply-accumulate
- [ ] NEON: Implement INT8 GEMM kernel basics  
- [ ] Study quantization requirements for both
- [ ] Compare INT8 support: RVV vs NEON

**Saturday Morning (5 hours) - Optimized Matrix Multiply (Dual Platform)**
- [ ] RVV Implementation (2.5 hours):
  - [ ] Tiled matrix multiply with RVV
  - [ ] Cache-aware tiling strategy
  - [ ] Loop unrolling where beneficial
  - [ ] Benchmark: naive vs optimized
  - [ ] Target 50%+ of theoretical peak

- [ ] NEON Implementation (2.5 hours):
  - [ ] Same algorithm adapted for NEON
  - [ ] 4x4 or 8x8 kernel tiles
  - [ ] Fixed-width vectorization
  - [ ] Benchmark performance
  - [ ] Compare approaches

**Sunday Afternoon (3 hours) - Hardware Order & Analysis**
- [ ] **Order both hardware boards:**
  - [ ] VisionFive 2 (8GB) - RISC-V (£70-80)
    - Sources: Mouser UK, RS Components
  - [ ] Raspberry Pi 4/5 (8GB) - ARM (£70-80)
    - Sources: Official distributors, Pimoroni
  - **Total investment: ~£140-160**
  
- [ ] Create comprehensive comparison document:
  ```markdown
  # RVV vs NEON: Comparative Analysis
  
  ## Programming Model
  - RVV: Vector-length agnostic (portable across VLEN)
  - NEON: Fixed 128-bit (explicit in code)
  
  ## Performance (QEMU, preliminary)
  - Matrix multiply throughput
  - Vector add latency
  - INT8 GEMM performance
  
  ## Code Complexity
  - Lines of code comparison
  - Readability assessment
  - Portability considerations
  ```

- [ ] Draft blog post: "Learning Two Vector ISAs: RVV and NEON"
- [ ] Weekly review

**Deliverable:** Optimized matrix kernels on BOTH platforms + hardware ordered + comparison doc

---

### Week 11: TVM Installation & Basics

**Monday Evening (2 hours) - TVM Setup**
- [ ] Install dependencies:
  ```bash
  sudo apt install python3-dev python3-setuptools
  sudo apt install llvm-18-dev libclang-18-dev
  pip3 install numpy decorator attrs tornado psutil scipy
  ```
- [ ] Clone TVM: `git clone --recursive https://github.com/apache/tvm`
- [ ] Configure build with LLVM support
- [ ] Build TVM (use Claude Code to help with build config)

**Wednesday Evening (2 hours)**
- [ ] Complete TVM build
- [ ] Install Python packages: `cd python; pip3 install -e .`
- [ ] Run TVM tests
- [ ] Verify installation: `python3 -c "import tvm; print(tvm.__version__)"`

**Thursday Evening (2 hours)**
- [ ] TVM Tutorial: "Getting Started with TVM"
- [ ] https://tvm.apache.org/docs/tutorial/introduction.html
- [ ] Compile first model (ResNet-18) for x86
- [ ] Understand TVM workflow: Import → Optimize → Compile → Run
- [ ] Test inference

**Saturday Morning (4 hours)**
- [ ] Deep dive into Relay IR
- [ ] Read: https://tvm.apache.org/docs/arch/relay_intro.html
- [ ] Study Relay operators in tvm/relay/op/
- [ ] Write Relay programs manually:
  ```python
  from tvm import relay
  x = relay.var("x", shape=(10, 10))
  y = relay.var("y", shape=(10, 10))
  z = relay.add(x, y)
  func = relay.Function([x, y], z)
  ```
- [ ] Build and run custom graphs

**Sunday Afternoon (2 hours)**
- [ ] Study Tensor Expression (TE)
- [ ] Read: https://tvm.apache.org/docs/tutorial/tensor_expr.html
- [ ] Write compute definitions
- [ ] Simple operator: element-wise add
- [ ] Understand scheduling concept
- [ ] Weekly review

**Deliverable:** TVM installed and first models compiled

---

### Week 12: Comparative Benchmarking on Real Hardware

**Monday Evening (2 hours) - RISC-V TVM Setup**
- [ ] Configure TVM for RISC-V target:
  ```python
  target = tvm.target.Target("llvm -mtriple=riscv64 -mcpu=sifive-u74 -mattr=+v")
  ```
- [ ] Compile simple model for RISC-V
- [ ] Test in QEMU first

**Wednesday Evening (2 hours) - ARM TVM Setup**
- [ ] Configure TVM for ARM target:
  ```python
  target = tvm.target.Target("llvm -mtriple=aarch64 -mcpu=cortex-a72")
  ```
- [ ] Compile same model for ARM
- [ ] Test in QEMU-ARM

**Thursday Evening (2 hours) - Benchmark Framework Setup**
- [ ] Create benchmark script for both platforms:
  ```python
  # benchmark.py - runs on both RISC-V and ARM
  import tvm
  import time
  import numpy as np
  
  def benchmark_model(model, inputs, num_runs=100):
      # Warmup
      for _ in range(10):
          model.run()
      
      # Benchmark
      times = []
      for _ in range(num_runs):
          start = time.perf_counter()
          model.run()
          times.append(time.perf_counter() - start)
      
      return {
          'mean_ms': np.mean(times) * 1000,
          'std_ms': np.std(times) * 1000,
          'median_ms': np.median(times) * 1000
      }
  ```
- [ ] Test locally

**Saturday Morning (5 hours) - Real Hardware Benchmarking**
- [ ] **VisionFive 2 Setup** (2.5 hours, if arrived):
  - [ ] Flash Ubuntu/Debian image
  - [ ] SSH configuration
  - [ ] Install TVM runtime
  - [ ] Transfer compiled models
  - [ ] Run benchmarks on RISC-V hardware
  - [ ] Collect metrics (latency, throughput, memory)
  
- [ ] **Raspberry Pi Setup** (2.5 hours):
  - [ ] Flash Raspberry Pi OS (64-bit)
  - [ ] SSH configuration
  - [ ] Install TVM runtime
  - [ ] Transfer ARM-compiled models
  - [ ] Run same benchmarks
  - [ ] Collect comparable metrics

**Sunday Afternoon (3 hours) - Comparative Analysis**
- [ ] Create performance comparison:
  | Model | RISC-V (VisionFive 2) | ARM (RPi 4) | Ratio |
  |-------|----------------------|-------------|-------|
  | ResNet-18 (inference ms) | ? | ? | ? |
  | Memory usage (MB) | ? | ? | ? |
  | Power (watts) | ? | ? | ? |
  
- [ ] Document differences:
  - Architecture impact on performance
  - Compiler optimization differences
  - Vector utilization (RVV vs NEON)
  
- [ ] Start "RISC-V vs ARM for Edge ML" blog post
- [ ] Monthly review: Month 3 complete!
- [ ] Major milestone: Comparative benchmarks on real hardware!

**Deliverable:** Performance comparison document + benchmark suite running on both platforms

---

## Month 4: TVM Optimization for Transformers (RISC-V & ARM)

### Week 13: Writing Custom TVM Operators

**Monday Evening (2 hours)**
- [ ] Study TVM operator implementation
- [ ] Read tvm/topi/python/topi/ directory
- [ ] Understand TOPI (TVM Operator Inventory)
- [ ] Study conv2d implementation

**Wednesday Evening (2 hours)**
- [ ] Implement custom operator: Leaky ReLU
- [ ] Write compute definition
- [ ] Write schedule
- [ ] Register operator
- [ ] Test in Relay graph

**Thursday Evening (2 hours)**
- [ ] Implement: Matrix multiply operator
- [ ] Write naive version
- [ ] Write scheduled version with tiling
- [ ] Compare performance
- [ ] Document approach

**Saturday Morning (4 hours)**
- [ ] Implement conv2d for RISC-V
- [ ] Choose algorithm: im2col or direct
- [ ] Write compute definition
- [ ] Implement schedule with tiling
- [ ] Test with actual conv layers
- [ ] Benchmark vs reference

**Sunday Afternoon (2 hours)**
- [ ] Implement depthwise convolution
- [ ] Optimize for RISC-V
- [ ] Common in MobileNet architectures
- [ ] Test and benchmark
- [ ] Weekly review

**Deliverable:** 3+ custom operators for RISC-V

---

### Week 14: Vector Optimization in TVM

**Monday Evening (2 hours)**
- [ ] Study TVM's vector intrinsics support
- [ ] Read: tvm/topi/arm_cpu/ for inspiration
- [ ] Understand how to emit vector code
- [ ] Study tensorization concept

**Wednesday Evening (2 hours)**
- [ ] Implement vectorized element-wise operations
- [ ] Use TVM's vectorization primitive
- [ ] Generate RVV instructions
- [ ] Verify assembly output

**Thursday Evening (2 hours)**
- [ ] Study TVM tensorization
- [ ] Read: https://tvm.apache.org/docs/how_to/optimize_operators/opt_conv_tensorcore.html
- [ ] Adapt for RISC-V vectors
- [ ] Define tensor intrinsic

**Saturday Morning (4 hours)**
- [ ] Implement tensorized GEMM for RVV
- [ ] Define 4x4 or 8x8 tensor multiply intrinsic
- [ ] Use in matrix multiply schedule
- [ ] Generate vector code
- [ ] Benchmark on VisionFive 2 (or QEMU)
- [ ] Compare vs scalar: should see 4-8x speedup

**Sunday Afternoon (2 hours)**
- [ ] Implement vectorized reduction
- [ ] Sum reduction with vectors
- [ ] Max/min pooling with vectors
- [ ] Test in full model
- [ ] Weekly review

**Deliverable:** Vectorized operators using RVV

---

### Week 15: AutoTVM Basics

**Monday Evening (2 hours)**
- [ ] Read AutoTVM documentation
- [ ] https://tvm.apache.org/docs/how_to/tune_with_autotvm/
- [ ] Understand: templates, search space, tuner
- [ ] Study cost model concept

**Wednesday Evening (2 hours)**
- [ ] Write tunable template for matrix multiply
- [ ] Define search space: tile sizes, unroll factors
- [ ] Use ConfigSpace API
- [ ] Create tuning script

**Thursday Evening (2 hours)**
- [ ] Run AutoTVM on simple operator
- [ ] Use local tuner (quick)
- [ ] Extract best config
- [ ] Apply to operator
- [ ] Measure improvement

**Saturday Morning (4 hours)**
- [ ] Tune conv2d for RISC-V
- [ ] Define comprehensive search space
- [ ] Run tuning (may take time)
- [ ] Log tuning process
- [ ] Analyze best schedules
- [ ] Apply to model

**Sunday Afternoon (2 hours)**
- [ ] Study Ansor (next-gen AutoTVM)
- [ ] Read paper: "Ansor: Generating High-Performance Tensor Programs"
- [ ] Understand sketch-based search
- [ ] Compare AutoTVM vs Ansor approaches
- [ ] Weekly review

**Deliverable:** Auto-tuned operators with logs

---

### Week 16: Transformer/LLM Optimization Introduction

**Monday Evening (2 hours)**
- [ ] Choose model: GPT-2 small or BERT-Base
- [ ] Import to TVM from ONNX/PyTorch
- [ ] Run baseline inference (unoptimized)
- [ ] Profile: measure layer-by-layer time (attention is bottleneck)

**Wednesday Evening (2 hours)**
- [ ] Study attention mechanism implementation
- [ ] Understand QKV computation: Q=XW_q, K=XW_k, V=XW_v
- [ ] Analyze memory access patterns
- [ ] Identify optimization opportunities

**Thursday Evening (2 hours)**
- [ ] Optimize multi-head attention for RISC-V
- [ ] Implement fused QKV projection
- [ ] Vectorize matrix operations with RVV
- [ ] Test correctness vs reference

**Saturday Morning (5 hours)**
- [ ] Optimize attention scoring and softmax
- [ ] Implement efficient batched matrix multiply for attention
- [ ] Optimize for different sequence lengths
- [ ] KV-cache optimization for autoregressive generation
- [ ] Compile for RISC-V with RVV
- [ ] Deploy to VisionFive 2
- [ ] Benchmark thoroughly:
  - Tokens/second generation
  - Prefill vs decode latency
  - Memory bandwidth utilization
  - Compare to baseline

**Sunday Afternoon (3 hours)**
- [ ] Document transformer optimization journey
- [ ] Create before/after comparison
- [ ] Write detailed blog post: "Optimizing Transformers for RISC-V"
- [ ] Share on TVM forum/Discord
- [ ] Monthly review: Month 4 complete!
- [ ] Major achievement: LLM running on RISC-V!

**Deliverable:** Optimized transformer model on RISC-V with attention optimizations

---

## Month 5: Quantization & Advanced Topics

### Week 17: Quantization Theory & Implementation

**Monday Evening (2 hours)**
- [ ] Read quantization papers:
  - "Quantization and Training of NNs for Efficient Integer-Arithmetic-Only Inference"
  - Available on arXiv
- [ ] Understand: INT8, INT4, symmetric, asymmetric
- [ ] Study scale and zero-point

**Wednesday Evening (2 hours)**
- [ ] TVM quantization tutorial
- [ ] https://tvm.apache.org/docs/how_to/deploy/quantization.html
- [ ] Quantize simple model
- [ ] Understand calibration process
- [ ] Measure accuracy impact

**Thursday Evening (2 hours)**
- [ ] Implement INT8 GEMM manually
- [ ] Handle scale factors
- [ ] Handle zero-points
- [ ] Use RISC-V integer multiply instructions
- [ ] Test for correctness

**Saturday Morning (4 hours)**
- [ ] Implement quantization-aware compilation
- [ ] Add quantization pass in TVM
- [ ] Insert scale/dequantize ops
- [ ] Optimize fused quantized operations
- [ ] Test on transformer model (BERT or GPT-2)
- [ ] LLM-specific: Quantize attention, layernorm, embeddings
- [ ] Measure: accuracy vs latency vs memory

**Sunday Afternoon (2 hours)**
- [ ] Study mixed precision for LLMs
- [ ] Quantize attention to INT8, keep sensitive layers in FP16
- [ ] Per-layer sensitivity analysis for transformers
- [ ] Implement mixed precision pipeline
- [ ] Weekly review

**Deliverable:** Quantization pipeline for RISC-V

---

### Week 18: Graph Optimization & Fusion

**Monday Evening (2 hours)**
- [ ] Study TVM Relay pass infrastructure
- [ ] Read: https://tvm.apache.org/docs/arch/relay_pass_infra.html
- [ ] Understand pass manager
- [ ] Look at existing passes: relay/transform/

**Wednesday Evening (2 hours)**
- [ ] Study operator fusion for transformers
- [ ] Element-wise fusion
- [ ] QKV projection fusion (fuse 3 matmuls)
- [ ] Attention block fusion
- [ ] Implement custom fusion pass
- [ ] Test on transformer models

**Thursday Evening (2 hours)**
- [ ] Layout transformation for transformers
- [ ] Optimize for sequence length dimension
- [ ] Implement layout conversion pass for attention
- [ ] Measure impact on RISC-V vector code

**Saturday Morning (4 hours)**
- [ ] Implement comprehensive graph optimization for LLMs:
  - [ ] Constant folding (static KV-cache shapes)
  - [ ] Dead code elimination
  - [ ] Fused QKV projections
  - [ ] Fused attention + dropout + residual
  - [ ] LayerNorm fusion with preceding ops
- [ ] Apply to GPT-2 or BERT
- [ ] Measure graph size reduction
- [ ] Measure performance improvement (tokens/sec)

**Sunday Afternoon (2 hours)**
- [ ] Study memory planning
- [ ] Understand memory pool allocation
- [ ] Implement in-place operations
- [ ] Reduce memory footprint
- [ ] Test on memory-constrained scenarios
- [ ] Weekly review

**Deliverable:** Complete graph optimization pass

---

### Week 19: MLIR Introduction

**Monday Evening (2 hours)**
- [ ] Install MLIR (comes with LLVM)
- [ ] Read MLIR paper: "MLIR: A Compiler Infrastructure for the End of Moore's Law"
- [ ] Understand dialects concept
- [ ] Study progressive lowering

**Wednesday Evening (2 hours)**
- [ ] MLIR Toy Tutorial Chapter 1-2
- [ ] https://mlir.llvm.org/docs/Tutorials/Toy/
- [ ] Build toy language
- [ ] Define AST
- [ ] Generate MLIR

**Thursday Evening (2 hours)**
- [ ] Toy Tutorial Chapters 3-4
- [ ] High-level optimization
- [ ] Inline, shape inference
- [ ] Understand operation traits
- [ ] Test transformations

**Saturday Morning (4 hours)**
- [ ] Toy Tutorial Chapters 5-7
- [ ] Partial lowering
- [ ] Affine dialect for optimization
- [ ] Lower to LLVM IR
- [ ] Generate code for RISC-V
- [ ] Run complete pipeline

**Sunday Afternoon (2 hours)**
- [ ] Study existing MLIR dialects
- [ ] Linalg: Linear algebra operations
- [ ] Vector: Vector operations (relevant for RVV!)
- [ ] Affine: Polyhedral optimizations
- [ ] Understand dialect lowering chains
- [ ] Weekly review

**Deliverable:** MLIR toy compiler working

---

### Week 20: MLIR for AI & Integration

**Monday Evening (2 hours)**
- [ ] Study how TensorFlow uses MLIR
- [ ] MHLO (Meta HLO) dialect
- [ ] Study IREE (MLIR-based ML compiler)
- [ ] https://github.com/openxla/iree

**Wednesday Evening (2 hours)**
- [ ] Write custom MLIR dialect for transformer ops
- [ ] Define operations: attention, layernorm, gelu
- [ ] Model multi-head attention in MLIR
- [ ] Implement op verification
- [ ] Test dialect

**Thursday Evening (2 hours)**
- [ ] Implement lowering to Linalg dialect
- [ ] Convert attention to linalg.generic operations
- [ ] Understand batched matmul representation
- [ ] Test transformation on transformer layers

**Saturday Morning (4 hours)**
- [ ] Implement MLIR vector lowering for transformer on RISC-V
- [ ] Use Vector dialect for attention operations
- [ ] Optimize softmax with RVV
- [ ] Generate RVV code for QKV projections
- [ ] Compare: MLIR path vs TVM path for transformers
- [ ] Document both approaches for LLM compilation

**Sunday Afternoon (2 hours)**
- [ ] Study polyhedral optimization in MLIR
- [ ] Affine dialect transformations
- [ ] Loop tiling, fusion, vectorization
- [ ] Apply to matrix multiply
- [ ] Compare vs manual TVM scheduling
- [ ] Weekly review

**Deliverable:** MLIR pipeline generating RISC-V vector code

---

## Month 6: Portfolio Projects & First Contributions

### Week 21: Project Planning & Research

**Monday Evening (2 hours)**
- [ ] Review everything learned so far
- [ ] Identify knowledge gaps
- [ ] Plan major portfolio project
- [ ] Choose focus: TVM contribution or novel optimization

**Wednesday Evening (2 hours)**
- [ ] Research current TVM RISC-V issues
- [ ] Check GitHub issues: https://github.com/apache/tvm/issues
- [ ] Look for "good first issue" or "help wanted"
- [ ] Join TVM Discord and introduce yourself
- [ ] Ask about contribution opportunities

**Thursday Evening (2 hours)**
- [ ] Study successful TVM PRs
- [ ] Read contribution guidelines
- [ ] Understand code style
- [ ] Setup development workflow
- [ ] Fork TVM repository

**Saturday Morning (4 hours)**
- [ ] Design portfolio project: "Optimized AI Models for RISC-V"
- [ ] Select 3 models: ResNet-50, MobileNetV2, BERT-Tiny
- [ ] Plan benchmarking methodology
- [ ] Setup benchmark infrastructure
- [ ] Create project repository
- [ ] Write project README

**Sunday Afternoon (2 hours)**
- [ ] Start documentation website/blog
- [ ] Setup GitHub Pages or use Medium
- [ ] Write project introduction
- [ ] Document goals and approach
- [ ] Weekly review

---

### Week 22: Major Implementation Work - GPT-2 Optimization

**Monday Evening (2 hours)**
- [ ] Implement optimization for GPT-2 (124M)
- [ ] Focus on attention layers (most compute)
- [ ] Optimize multi-head attention implementation
- [ ] Profile before/after

**Wednesday Evening (2 hours)**
- [ ] Optimize layer normalization + fusion
- [ ] Implement fused attention patterns
- [ ] Fuse residual connections
- [ ] Test accuracy preservation
- [ ] Benchmark improvement

**Thursday Evening (2 hours)**
- [ ] Quantize GPT-2 to INT8
- [ ] Calibrate on sample prompts
- [ ] Measure perplexity on validation set
- [ ] Optimize INT8 matmul kernels for RISC-V
- [ ] Handle mixed precision for sensitive layers

**Saturday Morning (5 hours)**
- [ ] Complete GPT-2 optimization
- [ ] Run full benchmarks on VisionFive 2
- [ ] Measure:
  - Prefill latency (process prompt)
  - Decode latency (per token)
  - Tokens/second generation
  - Memory usage (including KV-cache)
  - Perplexity / quality metrics
- [ ] Compare to baseline (unoptimized)
- [ ] Document all optimizations applied
- [ ] Generate graphs and charts

**Sunday Afternoon (2 hours)**
- [ ] Write detailed blog post: "Optimizing GPT-2 for RISC-V Edge Devices"
- [ ] Include code snippets for attention optimization
- [ ] Include benchmark results
- [ ] Explain KV-cache strategy
- [ ] Share on TVM forum
- [ ] Weekly review

**Deliverable:** Fully optimized and documented GPT-2 on RISC-V

---

### Week 23: Second LLM Model & Contribution

**Monday Evening (2 hours)**
- [ ] Optimize smaller LLM (TinyLlama-1.1B or DistilGPT2)
- [ ] Focus on memory efficiency for edge
- [ ] Implement grouped-query attention (GQA) if model supports
- [ ] Optimize for low-memory scenarios

**Wednesday Evening (2 hours)**
- [ ] Apply aggressive quantization
- [ ] INT4 for weights, INT8 for activations
- [ ] Test quality carefully (LLMs sensitive to quantization)
- [ ] Optimize for minimal memory footprint
- [ ] Implement dynamic quantization for KV-cache

**Thursday Evening (2 hours)**
- [ ] Benchmark second LLM model
- [ ] Compare to reference implementation
- [ ] Measure tokens/sec, memory usage
- [ ] Document optimizations
- [ ] Add to portfolio

**Saturday Morning (4 hours)**
- [ ] Choose first TVM contribution related to LLMs/RISC-V
- [ ] Options:
  - Add optimized attention operator for RISC-V
  - Improve RVV code generation for transformers
  - Add KV-cache optimization pass
  - Improve LLM-related documentation
  - Add test cases for transformer layers
- [ ] Implement fix/feature
- [ ] Write comprehensive tests
- [ ] Prepare PR

**Sunday Afternoon (2 hours)**
- [ ] Submit first TVM PR!
- [ ] Write clear description
- [ ] Link to relevant issues
- [ ] Respond to review feedback professionally
- [ ] Weekly review
- [ ] Celebrate: First open source contribution!

**Deliverable:** Optimized second LLM + first TVM PR

---

### Week 24: Final Projects & Month 6 Wrap-up

**Monday Evening (2 hours)**
- [ ] Work on BERT-Base optimization
- [ ] Advanced attention optimization techniques
- [ ] Flash Attention-style optimization for RISC-V
- [ ] Implement efficient bi-directional attention
- [ ] Compare to GPT-2 (decoder-only)

**Wednesday Evening (2 hours)**
- [ ] Optimize remaining transformer components
- [ ] Layer normalization with variance epsilon handling
- [ ] GELU activation approximations for RISC-V
- [ ] Positional encoding optimization
- [ ] Token embeddings lookup optimization
- [ ] Benchmark encoder vs decoder architectures

**Thursday Evening (2 hours)**
- [ ] Create comprehensive LLM benchmark suite
- [ ] Include: GPT-2, TinyLlama/DistilGPT2, BERT
- [ ] Consistent methodology across models
- [ ] Publication-quality results
- [ ] Generate comparison charts (tokens/sec, memory, quality)
- [ ] Highlight RISC-V-specific optimizations

**Saturday Morning (5 hours)**
- [ ] Write comprehensive technical blog post
- [ ] "6 Months Journey: LLM Compiler Engineering for RISC-V Edge"
- [ ] Cover all major learnings:
  - Compiler fundamentals → LLM optimization
  - RISC-V vectors for attention
  - Quantization strategies for transformers
  - KV-cache optimization
  - Memory bandwidth challenges
- [ ] Include all benchmarks with analysis
- [ ] Discuss challenges specific to LLMs on RISC-V
- [ ] Share on multiple platforms:
  - Medium/dev.to
  - TVM forum
  - RISC-V community
  - LinkedIn
  - HackerNews (if confident)

**Sunday Afternoon (3 hours)**
- [ ] Complete 6-month review
- [ ] Assess progress against goals:
  - ✅ Compiler fundamentals
  - ✅ LLVM expertise
  - ✅ RISC-V proficiency (including RVV)
  - ✅ TVM competency for LLMs
  - ✅ Optimized transformer models
  - ✅ First contributions
  - ✅ LLM-specific optimizations
- [ ] Update portfolio:
  - GitHub repositories (LLM focus)
  - Blog posts (3+ LLM-focused)
  - LinkedIn profile (highlight LLM compiler work)
  - Resume (emphasize edge LLM optimization)
- [ ] Plan next 6 months (Months 7-12):
  - Larger LLMs (3B-7B parameter models)
  - Advanced techniques (speculative decoding, etc.)
  - Production deployment
- [ ] Set new goals
- [ ] **Celebrate major milestone!**

**Deliverable:** Complete LLM-focused portfolio + comprehensive blog + updated career materials

---

## Development Environment Setup Guide
### (Use Claude Code to help with this)

### Initial System Setup

```bash
# Update system
sudo apt update && sudo apt upgrade -y

# Install build essentials
sudo apt install -y build-essential git cmake ninja-build \
    python3 python3-pip python3-dev \
    wget curl vim

# Install LLVM 18
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 18
sudo apt install -y llvm-18-dev libclang-18-dev clang-18

# Install RISC-V toolchain
sudo apt install -y gcc-riscv64-linux-gnu g++-riscv64-linux-gnu \
    binutils-riscv64-linux-gnu

# Install QEMU
sudo apt install -y qemu-user qemu-system-misc qemu-utils

# Python packages
pip3 install --user numpy scipy tornado psutil decorator attrs
```

### Workspace Structure

```bash
mkdir -p ~/risc-v-compiler-learning
cd ~/risc-v-compiler-learning

# Create directory structure
mkdir -p {compiler-projects,llvm-passes,risc-v-asm,tvm-work,benchmarks,blog-posts}
mkdir -p tools/{llvm,tvm,riscv-gnu-toolchain}
mkdir -p hardware/{visionfive2,qemu}
```

### Clone Key Repositories

```bash
cd ~/risc-v-compiler-learning/tools

# LLVM (this is large, ~3GB)
git clone https://github.com/llvm/llvm-project.git llvm
cd llvm
git checkout release/18.x
cd ..

# TVM
git clone --recursive https://github.com/apache/tvm.git
cd tvm
git checkout main
cd ..

# RISC-V GNU Toolchain (if building from source)
git clone https://github.com/riscv-collab/riscv-gnu-toolchain.git
```

### Build LLVM

```bash
cd ~/risc-v-compiler-learning/tools/llvm
mkdir build && cd build

cmake -G Ninja ../llvm \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_ENABLE_PROJECTS="clang;lld" \
    -DLLVM_TARGETS_TO_BUILD="X86;RISCV" \
    -DCMAKE_INSTALL_PREFIX=~/risc-v-compiler-learning/tools/llvm-install \
    -DLLVM_ENABLE_ASSERTIONS=ON

# Build (this takes 1-3 hours on 8 cores)
ninja -j8

# Install
ninja install

# Add to PATH in ~/.bashrc
echo 'export PATH=~/risc-v-compiler-learning/tools/llvm-install/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

### Build TVM

```bash
cd ~/risc-v-compiler-learning/tools/tvm
mkdir build && cd build

# Copy config
cp ../cmake/config.cmake .

# Edit config.cmake to enable LLVM
# set(USE_LLVM ~/risc-v-compiler-learning/tools/llvm-install/bin/llvm-config)

cmake -G Ninja ..
ninja -j8

# Install Python package
cd ../python
pip3 install --user -e .

# Test
python3 -c "import tvm; print(tvm.__version__)"
```

### VSCode Setup

```bash
# Install VSCode
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'
sudo apt update
sudo apt install code

# Recommended extensions
code --install-extension ms-vscode.cpptools
code --install-extension ms-python.python
code --install-extension llvm-vs-code-extensions.vscode-clangd
code --install-extension ms-vscode.cmake-tools
```

### Project Templates

Create initial project structure:

```bash
cd ~/risc-v-compiler-learning

# Compiler project template
cat > compiler-projects/template.cpp << 'EOF'
#include <iostream>
#include <string>

int main() {
    std::cout << "Compiler project template\n";
    return 0;
}
EOF

# LLVM pass template
cat > llvm-passes/template-pass.cpp << 'EOF'
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct MyPass : public FunctionPass {
    static char ID;
    MyPass() : FunctionPass(ID) {}
    
    bool runOnFunction(Function &F) override {
        errs() << "Processing: " << F.getName() << "\n";
        return false;
    }
};
}

char MyPass::ID = 0;
static RegisterPass<MyPass> X("mypass", "My Pass");
EOF
```

---

## Weekly Time Tracking Template

```markdown
# Week [NUMBER] - [DATES]

## Planned Hours: 12-14
## Actual Hours: ___

### Monday Evening
- [ ] Task 1 (estimated: 30min) - actual: ___
- [ ] Task 2 (estimated: 1hr) - actual: ___
- [ ] Task 3 (estimated: 30min) - actual: ___
**Total planned: 2hr** | **Actual: ___**

### Wednesday Evening
- [ ] Task 1
- [ ] Task 2
**Total planned: 2hr** | **Actual: ___**

### Thursday Evening
- [ ] Task 1
- [ ] Task 2
**Total planned: 2hr** | **Actual: ___**

### Saturday Morning
- [ ] Task 1
- [ ] Task 2
- [ ] Task 3
**Total planned: 4-5hr** | **Actual: ___**

### Sunday Afternoon
- [ ] Task 1
- [ ] Task 2
**Total planned: 2-3hr** | **Actual: ___**

## Completed:
- 

## Challenges:
- 

## Learnings:
- 

## Next Week Adjustments:
- 
```

---

## Monthly Review Template

```markdown
# Month [NUMBER] Review - [MONTH YEAR]

## Goals vs Achievement
### Technical Goals
- [ ] Goal 1 - Status: 
- [ ] Goal 2 - Status:
- [ ] Goal 3 - Status:

### Projects Completed
1. 
2. 
3. 

### Code Statistics
- Lines of code written: ~___
- GitHub commits: ___
- Repositories created: ___
- Pull requests submitted: ___

## Skills Acquired
- 
- 
- 

## Challenges Faced
1. 
   - How resolved:
   
2. 
   - How resolved:

## Time Analysis
- Total hours spent: ___
- Average hours/week: ___
- Most productive time: ___
- Least productive time: ___

## Health Check
- Enjoying the work? (1-10): ___
- Sustainable pace? (1-10): ___
- Work-life balance? (1-10): ___
- Motivation level? (1-10): ___

## Adjustments for Next Month
- 
- 
- 

## Highlights
Best moment this month:

Most interesting learning:

Proudest achievement:

## Next Month Plan
Focus areas:
1. 
2. 
3. 

Key deliverables:
1. 
2. 
3. 
```

---

## Resource Checklist

### Books to Acquire
- [ ] Crafting Interpreters (free online or £30 physical)
- [ ] Engineering a Compiler (£65)
- [ ] Getting Started with LLVM Core Libraries (£40)
- [ ] The RISC-V Reader (£25)
- [ ] Computer Organization and Design RISC-V Edition (£55)

### Hardware to Order
- [ ] VisionFive 2 (8GB) - £60-80
- [ ] MicroSD card (64GB+) - £10-15
- [ ] USB-C power supply - £10
- [ ] Optional: RISC-V dev board collection

### Online Accounts
- [ ] GitHub account
- [ ] TVM Discord
- [ ] RISC-V forum account
- [ ] LinkedIn (update profile)
- [ ] Medium or dev.to for blog
- [ ] ArXiv account (for paper reading)

### Subscriptions (Optional)
- [ ] ACM Digital Library (£15/month) - for papers
- [ ] JetBrains CLion (£20/month, 1st year free)
- [ ] GitHub Copilot (£8/month) - optional

---

## Success Metrics - 6 Month Checkpoint

By the end of Month 6, you should have:

### Technical Skills
- [ ] Built a complete compiler from scratch
- [ ] Written 10+ LLVM optimization passes
- [ ] **Fluent in both RISC-V and ARM assembly**
- [ ] **Expert in both RVV (RISC-V) and NEON (ARM) vector extensions**
- [ ] Modified LLVM backends (both RISC-V and AArch64)
- [ ] Compiled and optimized LLM models with TVM for both platforms
- [ ] Implemented custom TVM operators for transformers (dual-platform)
- [ ] Used AutoTVM for auto-optimization
- [ ] Implemented quantization pipeline for LLMs
- [ ] Basic MLIR competency with transformer ops
- [ ] Optimized attention mechanisms for both RVV and NEON
- [ ] Implemented KV-cache strategies
- [ ] **Created comparative benchmarks: RISC-V vs ARM**

### Portfolio
- [ ] GitHub with 5+ repositories
- [ ] **3-5 technical blog posts including comparative analysis:**
  - "Learning Two Vector ISAs: RVV vs NEON"
  - "RISC-V vs ARM for Edge LLMs: Benchmark Comparison"
  - "Optimizing GPT-2 for Both RISC-V and ARM"
- [ ] **Optimized LLM models on BOTH platforms with benchmarks**
- [ ] **Comparative performance analysis (RISC-V vs ARM)**
- [ ] 1-3 open source contributions (PRs submitted to TVM/LLVM)
- [ ] Documentation for all projects
- [ ] **Token generation benchmarks on both VisionFive 2 and Raspberry Pi**

### Community
- [ ] Active on TVM Discord
- [ ] Participated in both RISC-V and ARM forums
- [ ] Made connections with 5+ people in field
- [ ] Shared work publicly
- [ ] **Built reputation in both RISC-V and ARM ecosystems**

### Career Readiness
- [ ] Updated resume highlighting dual-architecture expertise
- [ ] LinkedIn profile showcasing comparative work
- [ ] Can explain transition story and unique positioning
- [ ] **Understand both RISC-V and ARM job markets**
- [ ] **Have hedge strategy: ARM for immediate opportunities, RISC-V for future**
- [ ] Ready for next 6 months of deeper work

---

## Emergency Adjustments

### If Falling Behind
1. **Don't panic** - This is normal
2. Reduce scope, not quality
3. Skip optional exercises
4. Focus on core deliverables
5. Extend timeline by 1-2 weeks
6. Take guilt-free rest week

### If Ahead of Schedule
1. Deepen current topics
2. Start next month's content
3. Do additional projects
4. Help others in community
5. Write more blog posts
6. Don't burn out!

### If Losing Motivation
1. Take full week off
2. Revisit "why" you started
3. Talk to someone in the field
4. Watch inspirational talks
5. Review progress made
6. Set smaller, achievable goals

---

## Final Notes

**Remember:**
- **Consistency > Intensity**: 12 hours/week for 6 months > 40 hours/week for 1 month
- **Done > Perfect**: Ship messy code, iterate later
- **Public > Private**: Share your learning, help others
- **Progress > Comparison**: Your journey is unique
- **Health > Everything**: Rest is part of the process

**You have 15 years of ML experience. This is your superpower.**

Most compiler engineers don't understand production ML.
Most ML engineers don't understand compilation.
You will bridge both worlds.

**This makes you uniquely valuable.**

---

Good luck with your journey! 🚀

**Start Date:** ___________
**Expected Completion:** ___________
**Actual Completion:** ___________

---

*This schedule is a guide, not a prison. Adjust as needed for your life circumstances while maintaining forward momentum.*
