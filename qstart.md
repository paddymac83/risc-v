# Quick Start Guide
## AI Compiler Engineer Learning Path for RISC-V

**Welcome!** This guide will get you started on your 6-month journey.

---

## 🎯 Your Goal

Become a **Compiler Engineer specializing in AI workload optimization on RISC-V** while working full-time as an AI Engineer in the UK.

**Specific Focus:** Large Language Model (LLM) optimization for edge deployment on RISC-V architectures.

**Timeline:** 6 months (12-14 hours/week)  
**Background:** 15 years AI/ML production experience  
**Outcome:** Job-ready for compiler engineering roles with expertise in LLM optimization

**What makes this unique:** You'll learn to optimize transformer models (GPT-2, TinyLlama, BERT) specifically for RISC-V edge devices, covering attention mechanisms, KV-cache management, and memory-efficient inference strategies.

---

## 📋 Before You Start

### Prerequisites Checklist
- [ ] Linux machine (Ubuntu 22.04/24.04) or WSL2
- [ ] 32GB+ RAM (recommended for LLVM builds)
- [ ] 500GB+ free disk space
- [ ] Stable internet connection
- [ ] GitHub account
- [ ] 12-14 hours/week availability

### Investment Required
- **Time:** 300 hours over 6 months
- **Money:** £900-£1500 (hardware, books, conferences)
- **Commitment:** Consistent weekly effort

---

## 🚀 Getting Started (Day 1)

### Step 1: Download Your Materials (5 minutes)

You should have these three files:
1. **risc-v-compiler-6month-schedule.md** - Your complete roadmap
2. **setup-environment.sh** - Automated environment setup
3. **progress-tracker.md** - Track your progress

### Step 2: Read the Schedule (30 minutes)

Open `risc-v-compiler-6month-schedule.md` and:
- [ ] Read the entire overview section
- [ ] Understand the time commitment
- [ ] Review Month 1 in detail
- [ ] Familiarize yourself with the structure

### Step 3: Setup Your Environment (2-3 hours)

**Option A: Automated Setup (Recommended)**
```bash
# Make executable
chmod +x setup-environment.sh

# Run setup (will ask for sudo password)
./setup-environment.sh

# This will:
# - Install all dependencies
# - Create workspace structure
# - Clone LLVM and TVM
# - Setup environment variables
# - Create helper scripts
```

**Option B: Use Claude Code**
Ask Claude Code to help you:
```
Please help me set up my RISC-V compiler learning environment 
following the setup-environment.sh script. I need:
- LLVM 18 installed
- RISC-V toolchain
- QEMU for RISC-V
- TVM cloned and ready
- Workspace structure created
```

### Step 4: Build LLVM (1-3 hours, run overnight)

```bash
cd ~/risc-v-compiler-learning
./build-llvm.sh

# This will take time. Start it before bed or during work.
# On 8 cores: ~2 hours
# On 4 cores: ~4 hours
```

**While LLVM builds, you can:**
- Order your books (see shopping list below)
- Order VisionFive 2 hardware (£60-80)
- Set up GitHub repositories
- Start reading Crafting Interpreters online

---

## 📚 Shopping List

### Books (Order Week 1)

**Essential (£150-250):**
- [ ] **Crafting Interpreters** by Robert Nystrom (FREE online or £30 physical)
  - https://craftinginterpreters.com/
  - Start reading immediately while waiting for others
  
- [ ] **Engineering a Compiler** by Cooper & Torczon (£65)
  - Amazon UK: Search "Engineering a Compiler 2nd Edition"
  
- [ ] **Getting Started with LLVM Core Libraries** (£40)
  - Amazon UK
  
- [ ] **The RISC-V Reader** by Patterson & Waterman (£25)
  - Amazon UK or direct from RISC-V Foundation
  
- [ ] **Computer Organization and Design RISC-V Edition** (£55)
  - Amazon UK - Reference book

### Hardware (Order Week 2-3)

**Essential:**
- [ ] **VisionFive 2** (8GB version) - £60-80
  - Buy from: Mouser UK, RS Components, or The Pi Hut
  - Search: "VisionFive 2 8GB RISC-V"
  
- [ ] **MicroSD Card** (64GB+ A2 rated) - £10-15
  - For VisionFive 2 OS
  
- [ ] **USB-C Power Supply** (5V 3A minimum) - £10
  - For VisionFive 2

**Where to Buy (UK):**
- Mouser Electronics UK
- RS Components
- The Pi Hut
- Amazon UK (last resort)

---

## 🗓️ Your First Week (Week 1)

### Monday Evening (2 hours) - Setup
- [x] Read this quick start guide
- [ ] Run setup-environment.sh
- [ ] Start LLVM build (overnight)
- [ ] Order books from shopping list
- [ ] Create GitHub account (if needed)

### Tuesday
**Rest day** - Let LLVM build

### Wednesday Evening (2 hours) - Start Learning
- [ ] Crafting Interpreters: Introduction + Chapter 1
- [ ] Take notes in markdown
- [ ] Set up note-taking system
- [ ] Read ahead: Chapter 2

### Thursday Evening (2 hours) - First Code
- [ ] Crafting Interpreters: Chapter 2 (Scanning)
- [ ] Start implementing scanner
- [ ] Write first 100 lines of code
- [ ] Commit to GitHub

### Friday
**Rest day** - Social life matters!

### Saturday Morning (4-5 hours) - Deep Work
- [ ] Crafting Interpreters: Chapters 3-4
- [ ] Implement recursive descent parser
- [ ] Write tests
- [ ] Target: 300+ lines of working code
- [ ] Debug and fix issues

### Sunday Afternoon (2-3 hours) - Review
- [ ] Review week's code
- [ ] Refactor and clean up
- [ ] Update progress tracker
- [ ] Plan Week 2
- [ ] Celebrate: You've started! 🎉

**Week 1 Total: 12-14 hours**

---

## 📊 Setting Up Progress Tracking

### Daily Logging

Create a file: `~/risc-v-compiler-learning/daily-log.md`

```markdown
# Daily Learning Log

## 2025-XX-XX (Week 1, Day 1)
**Planned:** 2 hours - Environment setup
**Actual:** ___ hours
**Completed:**
- 
- 
**Challenges:**
- 
**Tomorrow:**
- 
```

### Weekly Reviews (Every Sunday)

Open `progress-tracker.md` and update:
- Hours completed
- Tasks checked off
- Deliverables status
- Reflection notes

### Monthly Reviews

Set calendar reminder:
- Last Sunday of each month
- Review entire month
- Adjust next month's plan
- Celebrate progress

---

## 🛠️ Essential Tools Setup

### Code Editor

**Option A: VSCode (Recommended)**
```bash
# Already installed by setup script
code --install-extension ms-vscode.cpptools
code --install-extension ms-python.python
code --install-extension llvm-vs-code-extensions.vscode-clangd
```

**Option B: Your preferred editor**
- vim/neovim with LSP
- Emacs
- CLion (paid, but excellent)

### Version Control

```bash
# Configure Git
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# Create learning repo
cd ~/risc-v-compiler-learning
git init
git add .
git commit -m "Initial commit - Starting RISC-V compiler journey"

# Create GitHub repo and push
# Go to github.com, create new repo
git remote add origin https://github.com/yourusername/risc-v-compiler-learning.git
git push -u origin main
```

### Note Taking

**Recommended: Markdown in Git**
```bash
mkdir ~/risc-v-compiler-learning/notes
touch ~/risc-v-compiler-learning/notes/week-01.md
```

**Alternative:**
- Notion
- Obsidian
- OneNote
- Physical notebook (yes, really!)

---

## 🎓 Learning Strategy

### The 80/20 Rule

**80% Doing, 20% Reading**
- Don't get stuck in tutorial hell
- Code every single day you study
- Build things, even if messy
- Reading without coding = wasted time

### Pomodoro Technique

For deep work sessions:
1. 25 minutes focused work
2. 5 minute break
3. Repeat 4 times
4. Take 15-30 minute break

### Avoid Common Pitfalls

❌ **Don't:**
- Read without coding
- Aim for perfection
- Compare yourself to others
- Study when exhausted
- Skip rest days

✅ **Do:**
- Write code every session
- Ship messy code, iterate later
- Track your own progress
- Rest properly
- Ask for help

---

## 👥 Community Connections

### Join These Communities (Week 1)

**Essential:**
- [ ] **TVM Discord** - https://discord.gg/tvm
  - Introduce yourself in #general
  - Ask questions in #beginners
  
- [ ] **RISC-V Discourse** - https://discourse.riscv.org/
  - Create account
  - Read recent discussions
  
- [ ] **LLVM Discourse** - https://discourse.llvm.org/
  - Create account
  - Subscribe to relevant categories

**LinkedIn:**
- [ ] Update profile headline: "AI Engineer learning compiler engineering for RISC-V"
- [ ] Connect with people in the field
- [ ] Share your learning journey

**Twitter/X (Optional):**
- [ ] Follow compiler/RISC-V researchers
- [ ] Share progress with #LearnInPublic

### Finding a Study Buddy

Post in communities:
```
Hi! I'm starting a 6-month journey to learn AI compiler 
engineering for RISC-V while working full-time. Anyone else 
on a similar path want to be accountability partners? 
Working through LLVM, TVM, and RISC-V vector optimization.
```

---

## 🎯 Month 1 Goals Review

By end of Month 1, you will have:

### Technical
- [ ] Built a complete compiler from scratch (~1200 lines)
- [ ] Written 2 LLVM optimization passes
- [ ] Fluent in basic LLVM IR
- [ ] Written RISC-V assembly programs
- [ ] Environment fully setup

### Portfolio
- [ ] GitHub with first projects
- [ ] Notes and documentation
- [ ] Code committed regularly

### Skills
- [ ] Understanding of compilation phases
- [ ] Basic LLVM navigation
- [ ] RISC-V ISA familiarity

**This is real progress!** Most people never get this far.

---

## ⚠️ When Things Get Hard

### Week 3-4: First Crisis Point

**You'll think:** "This is too hard. Maybe I'm not cut out for this."

**Reality:** Everyone feels this way. It's normal.

**What to do:**
1. Take 2-3 days completely off
2. Review what you've already learned (it's a lot!)
3. Talk to someone in the field
4. Adjust pace if needed
5. Remember: 6 months is marathon, not sprint

### Debugging Failures

**LLVM won't build:**
- Check available disk space (needs 50GB+)
- Check RAM (builds need 16GB+)
- Use fewer cores: `ninja -j4` instead of `ninja -j8`
- Ask Claude Code for help

**Code won't compile:**
- Don't spend more than 30 min stuck
- Ask on Discord/forums
- Post code snippet and error
- People want to help!

**Falling behind schedule:**
- **This is normal**
- Adjust timeline, don't quit
- 7 months is fine, 8 months is fine
- Consistency matters more than speed

---

## 📞 Getting Help

### When Stuck Technically (>30 min)

**For LLVM:**
- LLVM Discord: https://discord.llvm.org/
- LLVM Discourse: https://discourse.llvm.org/
- Stack Overflow: Tag `llvm`

**For TVM:**
- TVM Discord: https://discord.gg/tvm (most responsive)
- TVM Forum: https://discuss.tvm.apache.org/
- GitHub Issues: For bugs

**For RISC-V:**
- RISC-V Discord
- RISC-V Discourse: https://discourse.riscv.org/

**For General Compiler Questions:**
- Stack Overflow
- Computer Science Stack Exchange

### When Losing Motivation

**Talk to:**
- Study buddy (if you found one)
- Online communities
- Friend/family who supports you

**Do:**
- Review progress tracker (see how far you've come!)
- Read success stories
- Take guilt-free break
- Adjust goals if needed

---

## 🎉 Milestones to Celebrate

### Week 1
- ✅ Environment setup complete
- ✅ First lines of compiler code written
- ✅ Joined communities

### Week 4
- ✅ First compiler complete
- ✅ First LLVM pass working
- ✅ Month 1 done!

### Week 12
- ✅ Model running on RISC-V
- ✅ Quarter way through!

### Week 24
- ✅ Complete portfolio
- ✅ Open source contributions
- ✅ 6 months done! 🎊

**Celebrate each one!** This journey is hard. Acknowledge progress.

---

## 📅 Next Steps Right Now

### If you're reading this for the first time:

1. **Today (1 hour):**
   - [ ] Read the full schedule: `risc-v-compiler-6month-schedule.md`
   - [ ] Decide: Am I committed to 6 months?
   - [ ] If yes: Continue below
   - [ ] If no: That's okay! Not the right time.

2. **This Evening (2 hours):**
   - [ ] Run `setup-environment.sh`
   - [ ] Start LLVM build (overnight)
   - [ ] Order first 2 books from shopping list

3. **Tomorrow:**
   - [ ] Order VisionFive 2 hardware
   - [ ] Create GitHub repositories
   - [ ] Set up progress tracking

4. **This Week:**
   - [ ] Follow Week 1 schedule
   - [ ] Start Crafting Interpreters
   - [ ] Write first compiler code
   - [ ] Join communities

### If LLVM is already building:

1. **Right Now:**
   - [ ] Start reading Crafting Interpreters online
   - [ ] Take notes in markdown
   - [ ] Set up GitHub repo

2. **When LLVM finishes:**
   - [ ] Test: `llvm-config --version`
   - [ ] Build TVM: `./build-tvm.sh`
   - [ ] Continue Week 1 tasks

---

## 🎯 Your Commitment

Before you start, commit to yourself:

```
I commit to:
- 12-14 hours per week for 6 months
- Consistent progress over perfection
- Asking for help when stuck
- Sharing my learning publicly
- Celebrating small wins
- Being kind to myself

I understand:
- This is a marathon, not a sprint
- Everyone struggles; that's normal
- Progress > Comparison
- Done > Perfect
- Rest is part of the process

Start Date: _______________
Signature: _______________
```

---

## 📚 Additional Resources

### Free Online Resources

**Crafting Interpreters:**
https://craftinginterpreters.com/
- Start reading immediately

**LLVM Documentation:**
https://llvm.org/docs/
- Bookmark for reference

**TVM Tutorials:**
https://tvm.apache.org/docs/tutorial/
- Start in Week 11

**RISC-V Specifications:**
https://riscv.org/technical/specifications/
- Download PDFs for offline reading

### YouTube Channels

- **LLVM Developers' Meetings** - Conference talks
- **Computerphile** - Compiler basics
- **Ben Eater** - Computer architecture fundamentals

### Papers (Read as you go)

- TVM: OSDI 2018
- Ansor: OSDI 2020
- Quantization: CVPR 2018
- MLIR: arXiv 2002.11054

---

## 🚦 Quick Decision Tree

**"Should I start today?"**

Do you have:
- [ ] 12-14 hours/week available?
- [ ] Linux machine or can set up WSL2?
- [ ] £1000-1500 budget (over 6 months)?
- [ ] Support from family/friends?
- [ ] Genuine interest in compilers?

**All yes?** → Start today! ✅  
**Some no?** → Address blockers first, then start  
**Most no?** → Maybe not the right time

**"I'm not sure I can do this..."**

Remember:
- You have 15 years of ML experience (huge advantage!)
- This schedule is designed for working professionals
- Thousands have done this while working full-time
- You don't need to be perfect, just consistent
- The field needs people like you

**You can do this.** 💪

---

## 🎬 Final Checklist - Start Right Now

- [ ] Read schedule: `risc-v-compiler-6month-schedule.md`
- [ ] Run: `./setup-environment.sh`
- [ ] Start LLVM build
- [ ] Order 2 books
- [ ] Create GitHub repo
- [ ] Join TVM Discord
- [ ] Open Crafting Interpreters website
- [ ] Read Chapter 1
- [ ] Update `progress-tracker.md` with start date
- [ ] Tell someone you're starting (accountability!)

---

## 📞 Contact & Support

**Questions about this guide:**
- Post in TVM Discord #beginners
- Ask on RISC-V forums
- Use Claude Code for setup help

**Technical issues:**
- Claude Code can help debug
- Community forums
- Stack Overflow

**Moral support:**
- Study buddy (find in communities)
- Learning in public (#LearnInPublic)
- Track progress visibly

---

## 🎊 Welcome to Your Journey!

You're about to embark on an incredible 6-month transformation.

Six months from now, you'll have:
- Built real compilers
- Optimized AI models for RISC-V
- Contributed to major open source projects
- A portfolio that gets you interviews
- Skills that are rare and valuable

**But the best part?**

You'll have proven to yourself that you can do hard things.
That you can learn complex topics while working full-time.
That you can achieve ambitious goals with consistency.

**This skill—the ability to learn—is more valuable than any single technology.**

---

**Now go build something amazing.** 🚀

**Your journey starts today.**

---

*"The best time to plant a tree was 20 years ago. The second best time is now."*

**Start Date:** _______________
**Expected Completion:** _______________
**Let's go!** 💪
