# Embedded Audio Command Processor Simulator

🎯 A modular C project simulating an embedded audio command handling system using key embedded concepts.

## 🔧 Features (Phase 1) 
- Logging system with levels: INFO, WARN, ERROR, INPUT
- Reads simulated commands from `commands.txt`
- Stubbed processor that recognizes input and prints dummy routing

## 📁 Structure
- `aud_main.c` - Main loop to read commands
- `audio_logger.c/.h` - Lightweight logging system
- `commands.txt` - Input simulation file
- `Makefile` - Build automation

## ▶️ How to Run
```bash
-> make -f MakeFile
-> ./audio_command_processor commands.txt
``` 
--------------------------------------------------------------------------------------------------------

## 🔧 Features (Phase 2)

- Command dispatch using function pointer table
- Argument parsing (e.g., `"play audio.wav"` → `play` as command, `audio.wav` as argument)
- Modular handler functions for commands:
  - `play`
  - `stop`
  - `volume up`
  - `volume down`
  - `reset`
  - fallback for invalid commands

## 📁 Structure
- `aud_main.c` - Main loop to read commands
- `audio_logger.c/.h` - Lightweight logging system
- `audio_command_processor.c/.h` - Logic for audio command dispatcher and audio routing handler with handler architecture
- `commands.txt` - Input simulation file
- `Makefile` - Build automation


## WorkFlow of PROJECT 


    main() 
    └── register_audio_commands()
            └── register_command("play", handle_play_command)
            └── register_command("stop", handle_stop_command)
            └── ...
    └── Open and read "commands.txt"
    └── For each command:
            └── dispatch_command("play file.mp3")
                └── Find "play" in linked list
                └── Call handle_play_command("file.mp3")
    └── Cleanup and exit

---

