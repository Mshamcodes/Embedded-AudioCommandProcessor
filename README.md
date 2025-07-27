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

--------------------------------------------------------------------------------------------------------

## ✅ Phase 3: Audio System State with Bitfields

### 🔹 New Modules:
- `audio_systemState.c/.h`:
  - Bitfield-based state: `is_playing`, `is_muted`
  - Tracks system volume (0–100)
  - Functions: `reset_audio_system`, `print_audio_status`, `get_audio_system`

- **New Commands Added**:
  - `mute` – sets `is_muted` flag
  - `unmute` – clears `is_muted` flag
  - `reset` – resets volume and flags

---

## 🧪 Sample Input: `commands.txt`
```txt
play audio.wav
stop
volumeUp
volumeDown
mute
unmute
reset
invalid
```

---------------------------------------------------------------------------------------------------------

## WorkFlow of PROJECT 

-> 
    main()
    │
    ├── register_audio_commands()
    │   ├── register_command("play",        handle_play_command)
    │   ├── register_command("stop",        handle_stop_command)
    │   ├── register_command("volumeUp",    handle_volumeUp_command)
    │   ├── register_command("volumeDown",  handle_volumeDown_command)
    │   ├── register_command("reset",       handle_reset_command)
    │   ├── register_command("mute",        handle_mute_command)
    │   ├── register_command("unmute",      handle_unmute_command)
    │   └── register_command("invalid",     handle_invalid_command)
    │
    ├── Open and read "commands.txt"
    │
    ├── For each line in file:
    │   ├── parse into audioCommand (name + arg)
    │   ├── dispatch_command(cmd)
    │   │   └── Search for matching name in command registry
    │   │   └── If found:
    │   │        └── Call corresponding handler with argument
    │   │             e.g., handle_play_command("file.mp3")
    │   │             ├── Updates audio system state
    │   │             └── Calls print_audio_status()
    │   │   └── Else:
    │   │        └── Call handle_invalid_command()
    │
    └── Cleanup:
        ├── Free all command list nodes
        └── Exit
-> 
---

