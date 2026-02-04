# 6-Month Detailed Learning Schedule
## AI Compiler Engineer for RISC-V (Part-Time, Full-Time Employment Compatible)

**Target:** 12-14 hours/week sustained learning
**Your Background:** 15 years AI/ML production experience
**End Goal:** Compiler Engineer specializing in AI workload optimization on RISC-V

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

## 🎯 LLM Optimization Focus

**This curriculum emphasizes Large Language Model (LLM) optimization on RISC-V edge devices.**

While you'll learn fundamental compiler skills applicable to all AI workloads, the examples and projects are specifically designed around transformer architectures and LLM deployment:

**Key LLM Topics Covered:**
- **Attention Mechanism Optimization** - Multi-head, multi-query, grouped-query attention
- **KV-Cache Management** - Efficient memory strategies for autoregressive generation
- **Transformer-Specific Kernels** - LayerNorm, GELU, token embeddings optimized for RISC-V
- **Memory Bandwidth Optimization** - Critical for LLM inference on edge devices
- **Quantization for LLMs** - INT8/INT4 strategies preserving quality
- **Prefill vs Decode Optimization** - Different optimization strategies for each phase
- **Small LLM Deployment** - 124M to 1.1B parameter models on RISC-V hardware

**Target Models:**
- GPT-2 (124M parameters) - Full optimization pipeline
- TinyLlama/DistilGPT2 (1.1B parameters) - Edge deployment
- BERT-Base - Encoder architecture comparison
- Custom transformer variants

**Real-World Application:**
By the end, you'll be able to optimize and deploy small LLMs on RISC-V edge devices, achieving practical token generation rates suitable for on-device applications like:
- Edge AI assistants
- Real-time translation
- Code completion on embedded systems
- Privacy-preserving LLM inference

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

## Month 2: LLVM Deep Dive & RISC-V Basics

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

### Week 7: RISC-V Assembly Programming

**Monday Evening (2 hours)**
- [ ] Read "The RISC-V Reader" Chapters 1-2
- [ ] Order physical copy if you don't have it
- [ ] Understand RISC-V philosophy: Simple, modular, extensible
- [ ] Study RV64I base instruction set (40 instructions)
- [ ] Learn register names: x0-x31, ABI names (a0-a7, t0-t6, s0-s11)

**Wednesday Evening (2 hours)**
- [ ] Write first RISC-V assembly programs:
  - [ ] Add two numbers
  - [ ] Fibonacci (iterative)
  - [ ] String length calculation
- [ ] Use GNU assembler: `riscv64-linux-gnu-as -o prog.o prog.s`
- [ ] Link: `riscv64-linux-gnu-ld -o prog prog.o`
- [ ] Run in QEMU

**Thursday Evening (2 hours)**
- [ ] Study RISC-V calling convention
- [ ] Argument passing: a0-a7
- [ ] Return values: a0-a1
- [ ] Saved vs temporary registers
- [ ] Stack frame layout
- [ ] Write function calls in assembly

**Saturday Morning (4 hours)**
- [ ] Implement algorithms in RISC-V assembly:
  - [ ] Factorial (recursive)
  - [ ] Array sum
  - [ ] Array maximum
  - [ ] String copy
  - [ ] Simple linked list traversal
- [ ] Practice stack manipulation
- [ ] Handle function prologues/epilogues
- [ ] Test all programs

**Sunday Afternoon (2 hours)**
- [ ] Study load/store instructions deeply
- [ ] Understand: lb, lh, lw, ld, lbu, lhu, lwu
- [ ] Understand: sb, sh, sw, sd
- [ ] Memory alignment requirements
- [ ] Write memory access patterns
- [ ] Weekly review

**Deliverable:** 10+ RISC-V assembly programs

---

### Week 8: RISC-V & LLVM Integration

**Monday Evening (2 hours)**
- [ ] Study LLVM RISC-V backend location: lib/Target/RISCV/
- [ ] Read: RISCVInstrInfo.td
- [ ] Understand TableGen for RISC-V
- [ ] Map assembly instructions to TableGen definitions

**Wednesday Evening (2 hours)**
- [ ] Generate RISC-V from LLVM IR:
  ```
  clang --target=riscv64 -S test.c
  ```
- [ ] Study generated assembly
- [ ] Compare to your hand-written code
- [ ] Identify optimization opportunities

**Thursday Evening (2 hours)**
- [ ] Deep dive: RISCVISelLowering.cpp
- [ ] Understand instruction selection for RISC-V
- [ ] Study how calls are lowered
- [ ] Trace IR → SelectionDAG → MachineInstr

**Saturday Morning (4 hours)**
- [ ] Build LLVM with RISC-V backend
- [ ] Modify simple pattern in RISCVInstrInfo.td
- [ ] Example: Add custom pattern for constant loading
- [ ] Rebuild LLVM (this takes time!)
- [ ] Test your modification
- [ ] Verify code generation changed

**Sunday Afternoon (3 hours)**
- [ ] Document RISC-V backend architecture
- [ ] Create diagram: IR → Assembly flow
- [ ] Write up learnings
- [ ] Compare RISC-V vs x86 backend design
- [ ] Monthly review: Month 2 complete!
- [ ] Plan Month 3

**Deliverable:** Modified LLVM RISC-V backend + documentation

---

## Month 3: RISC-V Vectors & TVM Introduction

### Week 9: RISC-V Vector Extension (RVV) Basics

**Monday Evening (2 hours) - Vector Setup**
- [ ] Download RISC-V Vector Extension Specification v1.0
- [ ] Read: https://github.com/riscv/riscv-v-spec
- [ ] Study Chapters 1-2: Overview and programming model
- [ ] Understand: VLEN, SEW, LMUL concepts
- [ ] Install RVV-capable toolchain

**Wednesday Evening (2 hours)**
- [ ] Read Spec Chapter 3: Vector register organization
- [ ] Understand vector register grouping (LMUL)
- [ ] Study element width (SEW): 8, 16, 32, 64 bits
- [ ] Learn vtype and vl CSRs
- [ ] Configure vectors: `vsetvli` instruction

**Thursday Evening (2 hours)**
- [ ] Study vector arithmetic instructions
- [ ] Read Spec Chapters 11-12: Integer/FP arithmetic
- [ ] Understand: vadd, vsub, vmul, vdiv
- [ ] Study widening/narrowing operations
- [ ] Write first vector intrinsics code:
  ```c
  #include <riscv_vector.h>
  vfloat32m1_t vec_add(vfloat32m1_t a, vfloat32m1_t b, size_t vl) {
      return vfadd_vv_f32m1(a, b, vl);
  }
  ```

**Saturday Morning (5 hours)**
- [ ] Implement vector operations using intrinsics:
  - [ ] Vector addition (int32, float32)
  - [ ] Vector multiplication
  - [ ] Dot product
  - [ ] SAXPY: y = a*x + y
  - [ ] Vector reduction (sum all elements)
- [ ] Test with different vector lengths
- [ ] Experiment with LMUL=1,2,4,8
- [ ] Measure performance vs scalar

**Sunday Afternoon (2 hours)**
- [ ] Study vector memory operations (Chapter 7)
- [ ] Unit-stride: vle32.v, vse32.v
- [ ] Strided: vlse32.v, vsse32.v
- [ ] Indexed: vluxei32.v, vsuxei32.v
- [ ] Implement matrix-vector multiply (basic)
- [ ] Weekly review

**Resources:**
- RVV Spec: https://github.com/riscv/riscv-v-spec
- RVV Intrinsics: https://github.com/riscv-non-isa/rvv-intrinsic-doc
- SiFive Vector Blog: https://www.sifive.com/blog/risc-v-vector-extension

**Deliverable:** 5+ vectorized operations with benchmarks

---

### Week 10: Advanced Vector Programming

**Monday Evening (2 hours)**
- [ ] Study vector masking (Chapter 5)
- [ ] Understand predication
- [ ] Implement conditional operations
- [ ] Write vector compare operations

**Wednesday Evening (2 hours)**
- [ ] Vector permutations and slides
- [ ] vslideup, vslidedown
- [ ] vrgather for arbitrary permutations
- [ ] Implement vector reverse
- [ ] Implement vector rotate

**Thursday Evening (2 hours)**
- [ ] Study fixed-point arithmetic in vectors
- [ ] Scaling and saturation
- [ ] Implement quantized operations (INT8)
- [ ] Simulate INT8 GEMM kernel

**Saturday Morning (4 hours)**
- [ ] Implement optimized matrix-matrix multiply
- [ ] Use vector intrinsics
- [ ] Tile for cache locality
- [ ] Unroll loops
- [ ] Compare: naive vs optimized vs scalar
- [ ] Target: 60%+ of theoretical peak
- [ ] Profile and identify bottlenecks

**Sunday Afternoon (2 hours)**
- [ ] Order VisionFive 2 board (~£70)
  - Mouser UK or RS Components
  - 8GB version recommended
- [ ] While waiting: Continue QEMU work
- [ ] Document vector optimization techniques
- [ ] Write blog post outline: "RISC-V Vector Programming"
- [ ] Weekly review

**Deliverable:** Optimized matrix multiply kernel

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

### Week 12: TVM Scheduling & RISC-V Target

**Monday Evening (2 hours)**
- [ ] Study TVM schedule primitives
- [ ] split: divide iteration
- [ ] reorder: change loop order
- [ ] bind: map to hardware threads
- [ ] compute_at: control when/where computation happens

**Wednesday Evening (2 hours)**
- [ ] Implement scheduled matrix multiply
- [ ] Tile loops for cache
- [ ] Reorder for locality
- [ ] Compare scheduled vs naive
- [ ] Measure speedup

**Thursday Evening (2 hours)**
- [ ] Configure TVM for RISC-V cross-compilation
- [ ] Set target: `target = tvm.target.Target("llvm -mtriple=riscv64-unknown-linux-gnu")`
- [ ] Compile simple model for RISC-V
- [ ] Generate shared library

**Saturday Morning (5 hours)**
- [ ] Compile ResNet-18 for RISC-V
- [ ] Use QEMU for testing
- [ ] Write inference script
- [ ] Measure performance baseline
- [ ] Study generated code (assembly)
- [ ] Identify optimization opportunities
- [ ] Document full compilation pipeline

**Sunday Afternoon (3 hours)**
- [ ] VisionFive 2 setup (if arrived)
  - [ ] Flash Linux image
  - [ ] SSH setup
  - [ ] Install TVM runtime
  - [ ] Run inference on hardware!
- [ ] If not arrived: Continue QEMU work
- [ ] Monthly review: Month 3 complete!
- [ ] Major milestone: TVM + RISC-V working!

**Deliverable:** TVM compiling models for RISC-V, running inference

---

## Month 4: TVM Optimization & Custom Operators

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
- [ ] Fluent in RISC-V assembly (write without docs)
- [ ] Expert in RISC-V vector extension (RVV)
- [ ] Modified LLVM backend successfully
- [ ] Compiled and optimized LLM models with TVM
- [ ] Implemented custom TVM operators for transformers
- [ ] Used AutoTVM for auto-optimization
- [ ] Implemented quantization pipeline for LLMs
- [ ] Basic MLIR competency with transformer ops
- [ ] Optimized attention mechanisms for RISC-V vectors
- [ ] Implemented KV-cache strategies

### Portfolio
- [ ] GitHub with 5+ repositories
- [ ] 3-5 technical blog posts (1500+ words each) focused on LLM optimization
- [ ] Optimized LLM models with benchmarks (GPT-2, TinyLlama, BERT)
- [ ] 1-3 open source contributions (PRs submitted to TVM/LLVM)
- [ ] Documentation for all projects
- [ ] Token generation benchmarks on RISC-V hardware

### Community
- [ ] Active on TVM Discord
- [ ] Participated in RISC-V forums
- [ ] Made connections with 5+ people in field
- [ ] Shared work publicly

### Career Readiness
- [ ] Updated resume with projects
- [ ] LinkedIn profile showcasing work
- [ ] Can explain transition story
- [ ] Understand job market
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
