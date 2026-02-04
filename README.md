# RISC-V AI Compiler Engineering Learning Package
## Complete 6-Month Roadmap for Working Professionals

---

## 📦 What's Included

This package contains everything you need to transform from an AI Engineer to a Compiler Engineer specializing in AI optimization on RISC-V, while working full-time.

### Core Documents

1. **QUICK-START.md** ⭐ **START HERE**
   - Immediate action steps
   - Shopping list for books and hardware
   - Week 1 detailed breakdown
   - Community setup guide
   - Motivation and commitment framework

2. **risc-v-compiler-6month-schedule.md** 📅 **YOUR ROADMAP**
   - Complete 6-month curriculum
   - Week-by-week breakdown (24 weeks)
   - Daily task assignments
   - Resource links for each week
   - Deliverables and milestones
   - 12-14 hours/week time allocation

3. **progress-tracker.md** 📊 **TRACK YOUR JOURNEY**
   - Weekly progress checklists
   - Monthly review templates
   - Skill development checklist
   - Portfolio tracking
   - Time tracking templates
   - Reflection prompts

4. **setup-environment.sh** ⚙️ **AUTOMATED SETUP**
   - Bash script for complete environment setup
   - Installs LLVM, RISC-V toolchain, TVM
   - Creates workspace structure
   - Sets up helper scripts
   - Configures environment variables

---

## 🎯 Who Is This For?

**Perfect for you if:**
- You have AI/ML production experience (5+ years)
- You work full-time and can dedicate 12-14 hours/week
- You want to specialize in compiler engineering for AI
- You're interested in RISC-V architecture
- You're in the UK (or elsewhere, but job market info is UK-focused)

**Target outcome:**
- Compiler Engineer roles at companies like ARM, Graphcore, Google, Amazon
- Salary: £80k-£140k+ (UK, senior level)
- Timeline: 6 months of part-time learning + job search

---

## 🤖 LLM Optimization Focus

**This curriculum is specifically designed for optimizing Large Language Models on RISC-V edge devices.**

While you'll build strong compiler fundamentals applicable to all AI workloads, the projects and examples emphasize:

**Transformer/LLM Optimization:**
- Multi-head attention optimization for RISC-V vectors
- KV-cache management strategies
- Efficient autoregressive generation
- Memory bandwidth optimization critical for LLMs
- INT8/INT4 quantization preserving LLM quality

**Target Models:**
- GPT-2 (124M) - full optimization pipeline
- TinyLlama (1.1B) - edge deployment focus  
- BERT-Base - encoder architecture
- Custom small transformers

**Real-World Application:**
Deploy production-ready small LLMs on RISC-V edge devices for:
- On-device AI assistants
- Privacy-preserving inference
- Real-time language tasks
- Embedded systems with AI

**Why LLMs + RISC-V:**
This combination is exploding in edge AI. Companies need engineers who can deploy LLMs efficiently on open-architecture processors. Your ML background + LLM compiler expertise = highly valuable skillset.

---

## 📖 How to Use This Package

### Getting Started (Day 1)

1. **Read QUICK-START.md** (1 hour)
   - Understand the commitment
   - Get immediate action steps
   - See shopping list

2. **Read risc-v-compiler-6month-schedule.md Overview** (30 min)
   - Understand the full journey
   - Review Month 1 in detail
   - Familiarize with structure

3. **Run setup-environment.sh** (2-3 hours)
   ```bash
   chmod +x setup-environment.sh
   ./setup-environment.sh
   ```
   - This sets up your entire development environment
   - Can also use Claude Code to help with setup

4. **Start progress-tracker.md** (15 min)
   - Fill in start date
   - Read the templates
   - Commit to tracking weekly

### Week-by-Week Usage

**Each Monday:**
- Open `risc-v-compiler-6month-schedule.md`
- Review current week's goals
- Note resources needed
- Plan your time

**Each Session:**
- Reference schedule for specific tasks
- Use Claude Code for environment/coding help
- Document progress in `progress-tracker.md`

**Each Sunday:**
- Complete weekly reflection in `progress-tracker.md`
- Review accomplishments
- Plan next week
- Adjust if needed

**Each Month:**
- Complete monthly review template
- Assess progress vs goals
- Adjust timeline if needed
- Celebrate achievements!

---

## 🗺️ Learning Path Overview

### Month 1: Compiler Foundations
- Build compiler from scratch
- Learn LLVM fundamentals
- Start RISC-V assembly
- **Deliverable:** Working compiler + 2 LLVM passes

### Month 2: LLVM Deep Dive & RISC-V
- Write optimization passes
- Study LLVM backend
- Master RISC-V assembly
- **Deliverable:** Modified LLVM backend

### Month 3: RISC-V Vectors & TVM
- Learn RISC-V Vector Extension
- Install and use TVM
- Compile models for RISC-V
- **Deliverable:** Model running on RISC-V

### Month 4: TVM Optimization & Transformers
- Write custom TVM operators for transformers
- Optimize attention mechanisms with RVV
- Use AutoTVM for LLM kernels
- **Deliverable:** Optimized GPT-2 on RISC-V

### Month 5: Quantization & Advanced LLM Topics
- Implement INT8/INT4 quantization for LLMs
- Graph optimizations for transformers
- Learn MLIR for transformer ops
- **Deliverable:** Quantization pipeline for edge LLMs

### Month 6: Portfolio & Contributions
- Optimize multiple LLM models (GPT-2, TinyLlama, BERT)
- Submit open source PRs for transformer optimization
- Build comprehensive LLM portfolio
- **Deliverable:** Job-ready portfolio with LLM expertise

---

## 💻 Technical Requirements

### Hardware (Minimum)
- **CPU:** 4+ cores (8+ recommended for faster builds)
- **RAM:** 16GB minimum (32GB+ recommended)
- **Storage:** 500GB free space (LLVM builds are large)
- **OS:** Linux (Ubuntu 22.04/24.04) or WSL2

### Hardware (To Purchase)
- **VisionFive 2** (£60-80) - RISC-V development board
- **MicroSD Card** (£10-15) - For VisionFive 2
- **Books** (£150-250) - See shopping list in QUICK-START.md

### Software (All Free/Open Source)
- LLVM 18+
- TVM
- RISC-V GNU Toolchain
- QEMU
- Python 3.10+
- Git, CMake, Ninja

**Total Budget:** £900-£1500 over 6 months
(£500 hardware, £250 books, £150-500 conferences/optional tools)

---

## 📚 Key Resources Referenced

### Books (Purchase Week 1)
1. **Crafting Interpreters** - FREE online or £30 physical
2. **Engineering a Compiler** - £65
3. **Getting Started with LLVM** - £40
4. **The RISC-V Reader** - £25
5. **Computer Organization RISC-V** - £55

### Online (All Free)
- LLVM Documentation: https://llvm.org/docs/
- TVM Tutorials: https://tvm.apache.org/docs/
- RISC-V Specs: https://riscv.org/technical/specifications/
- Crafting Interpreters: https://craftinginterpreters.com/

### Communities (Join Week 1)
- TVM Discord: https://discord.gg/tvm
- RISC-V Discourse: https://discourse.riscv.org/
- LLVM Discourse: https://discourse.llvm.org/

---

## 🎯 Success Metrics

By the end of 6 months, you will have:

### Technical Skills ✅
- Built compiler from scratch
- Written 10+ LLVM passes
- Fluent in RISC-V assembly and vectors
- Optimized 3+ AI models for RISC-V
- Implemented quantization pipeline
- Basic MLIR competency

### Portfolio ✅
- 5+ GitHub repositories
- 5-8 technical blog posts
- Benchmarked, optimized models
- 3-5 open source contributions

### Career Readiness ✅
- Resume updated with projects
- LinkedIn optimized
- Clear transition story
- Understanding of job market
- Ready for compiler interviews

**Realistic Timeline to Job Offer:** 12-18 months from start
- 6 months: This curriculum
- 3-6 months: Continued learning + applications
- 3-6 months: Interview process

---

## ⚠️ Important Notes

### Time Commitment
**12-14 hours/week is realistic for:**
- 3 weekday evenings (2h each) = 6h
- Saturday morning (4-5h) = 4-5h
- Sunday afternoon (2-3h) = 2-3h

**You MUST be able to sustain this.** If you can't:
- Adjust timeline (extend to 9-12 months)
- Reduce scope
- Wait until you have time

### Difficulty Level
This is **hard**. You will:
- Feel overwhelmed (normal!)
- Want to quit (everyone does)
- Get stuck (ask for help!)
- Fall behind schedule (adjust it)

**But:** Your 15 years of ML experience is a superpower.
Most compiler engineers don't understand ML.
You bridge both worlds = valuable.

### Success Rate
**Realistic expectations:**
- 50% will start enthusiastically
- 30% will make it to Month 3
- 15% will complete all 6 months
- 10% will land compiler jobs within 18 months

**You increase your odds by:**
- Following schedule consistently
- Asking for help early
- Tracking progress
- Sharing your journey
- Not giving up when hard

---

## 🚀 Next Steps (Right Now)

### Today (2 hours total)

1. **Read QUICK-START.md** (30 min)
   - [ ] Understand commitment
   - [ ] Review Week 1 plan
   - [ ] Check prerequisites

2. **Run setup-environment.sh** (1-1.5 hours)
   - [ ] Make executable: `chmod +x setup-environment.sh`
   - [ ] Run: `./setup-environment.sh`
   - [ ] Follow prompts (requires sudo)
   - [ ] Let LLVM build overnight

3. **Order Materials** (30 min)
   - [ ] Order first 2 books from Amazon UK
   - [ ] Bookmark VisionFive 2 (order Week 2)
   - [ ] Join TVM Discord
   - [ ] Create GitHub repo

### This Week

Follow **Week 1** schedule in `risc-v-compiler-6month-schedule.md`:
- [ ] Start Crafting Interpreters
- [ ] Write first compiler code
- [ ] Setup progress tracking
- [ ] Join communities

---

## 📞 Getting Help

### Technical Issues
- **Claude Code:** Ask for help with setup, coding, debugging
- **TVM Discord:** #beginners channel
- **LLVM Discourse:** Compiler questions
- **Stack Overflow:** Specific errors

### Motivation & Strategy
- **Find study buddy:** Post in communities
- **Share journey:** #LearnInPublic on Twitter
- **Progress tracking:** Review weekly accomplishments

### This Package
If you have questions about how to use these materials:
- Re-read QUICK-START.md
- Check progress-tracker.md templates
- Ask Claude Code for guidance

---

## 🎉 Why This Works

### Designed for Working Professionals
- **12-14 hours/week** (not 40)
- **6 months** (not 6 weeks)
- **Part-time sustainable** pace
- **Built-in rest** days

### Leverages Your Experience
- **You already know ML** - just learning compilation
- **Production mindset** - huge advantage
- **15 years experience** - not starting from zero
- **Unique combination** - ML + compilers = rare

### Proven Structure
- **Hands-on first** - 80% coding, 20% reading
- **Progressive complexity** - builds on itself
- **Real projects** - portfolio pieces, not tutorials
- **Community support** - you're not alone

### Clear Outcomes
- **Specific deliverables** each week
- **Measurable progress** tracking
- **Portfolio building** from day 1
- **Job-ready skills** by month 6

---

## 🏆 Success Stories Template

**When you complete this (yes, when, not if):**

1. **Share your journey**
   - Blog post: "6 Months from ML Engineer to Compiler Engineer"
   - Include your progress tracker
   - Help the next person

2. **Update this package**
   - What worked best?
   - What would you change?
   - Share your version

3. **Give back**
   - Help beginners in communities
   - Contribute to open source
   - Mentor others

---

## 📋 File Checklist

Ensure you have all files:
- [ ] README.md (this file)
- [ ] QUICK-START.md
- [ ] risc-v-compiler-6month-schedule.md
- [ ] progress-tracker.md
- [ ] setup-environment.sh

**Where to save:**
```bash
mkdir -p ~/risc-v-compiler-learning/materials
cd ~/risc-v-compiler-learning/materials
# Save all files here
```

---

## 🎓 Final Words

You're about to start an incredible journey.

Six months is long enough to:
- Build real expertise
- Create impressive portfolio
- Make meaningful contributions
- Transform your career

But short enough to:
- Maintain motivation
- See clear end goal
- Fit around full-time work
- Not burn out

**The key is consistency.**
Not perfection. Not speed. Not genius.
Just consistent, steady progress.

**12 hours/week for 6 months = 288 hours of focused learning.**

That's more than most people invest in their entire career development.
That's enough to become competent in a new field.
That's enough to change your career trajectory.

**You have everything you need:**
- The roadmap (this package)
- The time (12-14 hours/week)
- The background (15 years ML)
- The resources (books, hardware, communities)
- The tools (LLVM, TVM, RISC-V)

**All you need now is to start.**

---

## 🚦 Your Decision Point

**Option 1: Start Today**
- Read QUICK-START.md
- Run setup-environment.sh
- Begin Week 1
- Join communities
- Commit to 6 months

**Option 2: Prepare to Start**
- Address any blockers
- Get family support
- Plan schedule
- Set start date
- Come back when ready

**Option 3: Not Right Now**
- That's okay!
- Save these materials
- Revisit in 3-6 months
- When you're ready, they'll be here

---

**If you choose Option 1:**

Welcome to your journey! 🚀

Open QUICK-START.md and begin.

Your future self will thank you.

---

**Created by:** AI Compiler Learning Path Project  
**Version:** 1.0 (February 2025)  
**License:** Use freely, share widely, give credit  
**Contact:** Share your progress in TVM Discord or RISC-V forums

**Good luck! You've got this.** 💪

---

*"A journey of a thousand miles begins with a single step."*
*"A compiler of a thousand lines begins with a single token."*

**Take that first step today.**
