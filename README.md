# Embedded-AudioCommandProcessor
🎯 A modular C project simulating an embedded audio command handling system using key embedded concepts.

## 🔧 Features (Phase 1)
- Logging system with levels: INFO, WARN, ERROR, INPUT
- Reads simulated commands from `commands.txt`
- Stubbed processor that recognizes input and prints dummy routing

## 📁 Structure
- `main.c` - Main loop to read commands
- `logger.c/.h` - Lightweight logging system
- `commands.txt` - Input simulation file
- `Makefile` - Build automation

## ▶️ How to Run
```bash
-> make -f MakeFile

-> ./audio_command_processor commands.txt
