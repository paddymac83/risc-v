# LLM Optimization Modifications Summary

## Overview of Changes

The 6-month learning plan has been updated to focus specifically on **Large Language Model (LLM) optimization for RISC-V edge devices**, while maintaining the strong compiler fundamentals foundation.

---

## Key Changes Made

### 1. **Month 4 - Transformer Introduction (Week 16)**

**Changed from:** MobileNetV2 optimization (computer vision)  
**Changed to:** GPT-2/Transformer optimization

**New focus:**
- Multi-head attention mechanism optimization
- QKV (Query-Key-Value) projection optimization
- Fused attention kernels
- KV-cache optimization for autoregressive generation
- Memory bandwidth analysis for transformers
- Prefill vs decode phase optimization

---

### 2. **Month 5 - LLM-Specific Optimizations**

#### Week 17 - Quantization
**Added LLM-specific content:**
- Quantizing attention mechanisms
- Quantizing LayerNorm and embeddings
- Mixed precision strategies for transformers
- Per-layer sensitivity analysis for LLMs (different from CV models)

#### Week 18 - Graph Optimization
**Changed from:** Conv-BN-ReLU fusion (CV-specific)  
**Changed to:** Transformer-specific fusions
- Fused QKV projections (combine 3 matrix multiplications)
- Attention block fusion
- LayerNorm fusion with preceding operations
- Attention + dropout + residual fusion

#### Week 20 - MLIR for AI
**Updated focus:**
- Custom MLIR dialect for transformer operations
- Attention operation modeling in MLIR
- Batched matrix multiply for transformers
- Vector lowering for attention on RISC-V

---

### 3. **Month 6 - LLM Portfolio Projects**

#### Week 22 - Major Implementation
**Changed from:** ResNet-50 optimization  
**Changed to:** GPT-2 (124M parameters) full optimization

**New deliverable includes:**
- Prefill latency (processing input prompt)
- Decode latency (per-token generation)
- Tokens/second metrics
- KV-cache memory usage
- Perplexity/quality metrics

#### Week 23 - Second Model
**Changed from:** MobileNetV2 optimization  
**Changed to:** TinyLlama or DistilGPT2 optimization

**New focus:**
- Grouped-query attention (GQA) optimization
- Aggressive quantization (INT4 weights, INT8 activations)
- Dynamic quantization for KV-cache
- Memory-efficient edge deployment

#### Week 24 - Final Projects
**Enhanced BERT optimization:**
- Flash Attention-style optimization for RISC-V
- Bi-directional vs autoregressive comparison
- Encoder vs decoder architecture analysis
- Comprehensive LLM benchmark suite

---

### 4. **Added New Section: LLM Optimization Focus**

Added at the beginning of the schedule explaining:
- Why LLMs are the focus
- Key topics covered (attention, KV-cache, memory bandwidth, etc.)
- Target models (GPT-2, TinyLlama, BERT)
- Real-world applications (edge AI assistants, on-device inference, etc.)

---

## What Stayed the Same

**Months 1-3 (Compiler Foundations)** remain unchanged:
- Month 1: Compiler basics, LLVM introduction, RISC-V assembly
- Month 2: LLVM deep dive, RISC-V backend
- Month 3: RISC-V Vector Extension, TVM basics

**Why:** These foundational skills are essential regardless of whether you're optimizing CV models or LLMs. The core compiler concepts apply to all AI workloads.

---

## Skills You'll Gain (LLM-Specific)

By the end of 6 months, you'll be able to:

### Attention Mechanism Optimization
- ✅ Optimize multi-head attention (MHA) for RISC-V vectors
- ✅ Implement multi-query attention (MQA) for faster inference
- ✅ Understand grouped-query attention (GQA)
- ✅ Apply Flash Attention concepts to RISC-V

### KV-Cache Management
- ✅ Implement efficient KV-cache for autoregressive generation
- ✅ Optimize memory layouts for cache efficiency
- ✅ Handle dynamic sequence lengths
- ✅ Understand PagedAttention concepts

### Memory & Performance
- ✅ Optimize for memory bandwidth (critical for LLMs)
- ✅ Distinguish prefill vs decode optimization strategies
- ✅ Measure and improve tokens/second generation
- ✅ Handle large activation sizes efficiently

### LLM-Specific Layers
- ✅ LayerNorm optimization with variance handling
- ✅ GELU/SiLU activation functions optimized for RISC-V
- ✅ Token embedding lookup patterns
- ✅ Positional encoding optimization

### Quantization for LLMs
- ✅ INT8/INT4 quantization preserving LLM quality
- ✅ Mixed precision strategies (different from CV)
- ✅ Quantizing attention vs FFN layers differently
- ✅ Dynamic vs static quantization trade-offs

---

## Models You'll Optimize

### GPT-2 (124M parameters)
- **Type:** Decoder-only transformer
- **Use case:** Text generation, code completion
- **Focus:** Autoregressive generation, KV-cache efficiency
- **Target:** 5+ tokens/second on VisionFive 2

### TinyLlama / DistilGPT2 (1.1B parameters)
- **Type:** Smaller decoder-only models
- **Use case:** Edge deployment, on-device inference
- **Focus:** Aggressive quantization, memory efficiency
- **Target:** Usable generation on resource-constrained RISC-V

### BERT-Base (110M parameters)
- **Type:** Encoder-only transformer
- **Use case:** Classification, embeddings
- **Focus:** Bi-directional attention, different optimization patterns
- **Target:** Fast embedding generation

---

## Career Impact

### Job Market Positioning

**Before modifications:** AI Compiler Engineer (general)
**After modifications:** LLM Compiler Engineer (specialized niche)

**Why this matters:**
- LLMs are exploding in edge AI applications
- Few engineers understand both LLMs AND compilation
- RISC-V is growing rapidly in edge/IoT
- This triple combination (LLMs + Compilation + RISC-V) is extremely rare

### Relevant Roles (UK Market)

**Companies actively hiring for this skillset:**
- Graphcore - IPU optimization for transformers
- Google DeepMind - TPU compiler work, JAX/XLA
- Amazon - AWS Inferentia/Trainium for LLM inference
- ARM - ML optimization for embedded
- Startups - Edge AI, on-device LLMs

**Salary expectation:** £90k-£150k+ (higher than general compiler roles due to LLM specialization)

---

## Updated Deliverables

### Portfolio Changes

**Before:** 
- ResNet-50 optimized
- MobileNetV2 optimized
- BERT-Tiny basic

**After:**
- GPT-2 (124M) fully optimized with attention kernels
- TinyLlama/DistilGPT2 (1.1B) for edge deployment
- BERT-Base with bidirectional attention analysis

### Blog Posts Updated

1. ~~"Optimizing ResNet-50 for RISC-V"~~ → **"Optimizing GPT-2 for RISC-V Edge Devices"**
2. ~~"TVM Scheduling Deep Dive"~~ → **"TVM Scheduling for Transformer Attention"**
3. ~~"6-Month Journey: AI Compiler Engineering"~~ → **"6-Month Journey: LLM Compiler Engineering for RISC-V"**

### Open Source Contributions

**Updated focus areas:**
- TVM: Add optimized attention operators for RISC-V
- TVM: Improve RVV code generation for transformers
- TVM: Add KV-cache optimization passes
- LLVM: RISC-V backend improvements for transformer workloads

---

## Resources to Add

### Papers (LLM-Specific)
- "Attention Is All You Need" (Vaswani et al., 2017) - Transformer fundamentals
- "Flash Attention: Fast and Memory-Efficient Exact Attention" (Dao et al., 2022)
- "GQA: Training Generalized Multi-Query Transformer" (Ainslie et al., 2023)
- "LLM.int8(): 8-bit Matrix Multiplication for Transformers" (Dettmers et al., 2022)

### Additional Online Resources
- Hugging Face Transformers documentation
- Papers With Code - Transformer section
- IREE compiler for transformers (MLIR-based)
- TVM tutorials for NLP models

---

## Timeline Still Realistic?

**Yes, with adjustments:**

- Foundational months (1-3) are unchanged - same timeline
- Months 4-6 replace CV optimization with LLM optimization
- Complexity is similar (transformers vs convolutions both challenging)
- Time commitment stays 12-14 hours/week

**Potential challenges:**
- LLMs may be harder to debug (autoregressive generation complexity)
- Memory requirements are higher (need to manage this carefully)
- Fewer TVM examples for transformers (you'll pioneer more)

**Advantages:**
- Attention is conceptually simpler than complex convolution variants
- Matrix multiply dominates (easier to optimize than diverse CV ops)
- Growing community interest means more help available

---

## Modified Success Metrics

### By End of Month 6:

**Technical Skills:**
- ✅ Built compiler from scratch
- ✅ 10+ LLVM passes written
- ✅ RISC-V assembly + RVV mastery
- ✅ **LLM models compiled and optimized with TVM**
- ✅ **Custom transformer operators**
- ✅ **Attention mechanism optimization**
- ✅ **KV-cache implementation**
- ✅ **LLM quantization pipeline**

**Portfolio:**
- ✅ 5+ repos (LLM-focused)
- ✅ 3-5 blog posts (transformer optimization theme)
- ✅ **Optimized GPT-2, TinyLlama, BERT**
- ✅ **Token generation benchmarks**
- ✅ 1-3 TVM/LLVM contributions

**Career:**
- ✅ Resume highlighting LLM compiler expertise
- ✅ LinkedIn profile emphasizing edge LLM work
- ✅ Clear narrative: ML Engineer → LLM Compiler Engineer
- ✅ Job-ready for specialized LLM compiler roles

---

## Questions & Answers

### Q: Can I still learn CV model optimization later?
**A:** Yes! The skills transfer. Convolution optimization uses similar techniques (tiling, vectorization, fusion). Many companies need both.

### Q: Is LLM optimization harder than CV?
**A:** Different, not necessarily harder. Transformers have simpler ops (mostly matmul) but complex memory patterns. CV has diverse ops but simpler memory access.

### Q: Will this limit my job opportunities?
**A:** No - it actually increases them. LLM + Compiler is rarer than CV + Compiler. You can learn CV later, but starting with hot area (LLMs) is strategic.

### Q: What if I want to focus on CV instead?
**A:** Use the original version of the plan (before these modifications). Or do this plan, then spend months 7-9 on CV.

### Q: Can I do both CV and LLM in 6 months?
**A:** Not recommended. You'd be spread too thin. Master one, then learn the other. The compiler fundamentals apply to both.

---

## Next Steps After 6 Months

**Months 7-12 Potential Focus:**
1. **Larger LLMs** - 3B to 7B parameter models
2. **Advanced Techniques** - Speculative decoding, continuous batching
3. **Production Deployment** - Serving infrastructure, multi-node
4. **CV Models** - Add computer vision to your portfolio
5. **Custom RISC-V Extensions** - Design AI-specific instructions

---

## Summary

The modified plan maintains the **strong compiler foundations** while specializing in the **hot, growing area of LLM optimization for edge devices**. 

You'll emerge with:
- Deep compiler expertise (unchanged)
- Specialized LLM knowledge (added value)
- RISC-V vector optimization (enhanced)
- Rare, valuable skillset (career advantage)

**The modifications make you more valuable, not less.**

Your 15 years of ML experience + new compiler skills + LLM specialization = unique positioning for high-paying, cutting-edge roles.

---

**Ready to start? The complete modified package is ready for download!** 🚀
