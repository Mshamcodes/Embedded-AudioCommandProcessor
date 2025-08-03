# 🔊 Embedded Audio Command Processor Simulator

This project simulates a simple **Embedded Audio Command Processor** written in C, mimicking the kind of software found in embedded audio systems. It processes user commands like `play`, `pause`, `mute`, `unmute`, `volumeUp`, `volumeDown`, `reset`, and `help`, while managing internal audio state, buffer simulation, and visual feedback.

---

## 🚀 Features

- 🎙️ **Command Handling** — Text-based command input to control audio system behavior.
- 📦 **Audio Buffer Simulation** — Simulates enqueueing and dequeuing audio chunks.

           Audio Source (Producer)         Audio Sink (Consumer)
           ───────────────────────        ───────────────────────
                   │                                ▲
            [enqueue chunk: 🎵]             [dequeue chunk: 🎵]
                   ▼                                │
           ┌────────────────────┐         ┌────────────────────────┐
           │Circular AudioBuffer│  <──>   │ Audio Playback System  |
           └────────────────────┘         └────────────────────────┘

- 🎛️ **State Management** — Tracks volume, mute status, and playback status using bitfields.
- 📈 **Interactive Buffer View** — Visually shows buffer front/rear and fill state using icons.
- 🛠️ **Modular Design** — Cleanly separated source files for commands, buffer, state, and logging.
- 🆘 **Help Command** — Lists all available commands at runtime.

---

## 🧠 Architecture Overview

### Modules

| Module                     | Responsibility                                 |
|----------------------------|------------------------------------------------|
| `audio_command_registry.*` | Registers commands and dispatches handlers     |
| `audio_command_processor.*`| Core logic for command parsing and execution   |
| `audio_systemState.*`      | Manages audio flags and volume using bitfields |
| `audio_buffer.*`           | Simulates circular audio chunk buffer          |
| `audio_logger.*`           | Colorful log output with levels                |

---

## 🔄 Workflow of the Project

```text
main()
│
├── register_audio_commands()
│   ├── register_command("help",        handle_help_command)
│   ├── register_command("play",        handle_play_command)
│   ├── register_command("pause",       handle_pause_command)
│   ├── register_command("volumeUp",    handle_volumeUp_command)
│   ├── register_command("volumeDown",  handle_volumeDown_command)
│   ├── register_command("reset",       handle_reset_command)
│   ├── register_command("mute",        handle_mute_command)
│   ├── register_command("unmute",      handle_unmute_command)
│   └── register_command("invalid",     handle_invalid_command)
│
├── LOOP: Accept user input from terminal
│   ├── parse input into audioCommand (name + arg)
│   ├── dispatch_command(cmd)
│   │   ├── Search command registry for match
│   │   ├── If found:
│   │   │   └── Call corresponding handler with argument
│   │   │       ├── e.g., handle_play_command("track1.mp3")
│   │   │       ├── Updates audio system state (bitfields)
│   │   │       ├── Enqueues audio chunks into audio buffer
│   │   │       ├── Dequeues a few chunks to simulate playback
│   │   │       └── Prints buffer state using visualization
│   │   └── Else:
│   │       └── Call handle_invalid_command()
│   │
└── On exit signal:
    ├── Free all command registry nodes
    └── Exit gracefully

```

## 🖥️ How It Works

### Example Session

```text
[INFO] Command Processor Initialized.
Enter command: help
[INPUT] Received: "help"

Available Commands:
 - play       : Start playing audio
 - pause      : Pause audio playback and clear buffer
 - volumeUp   : Increase volume by 10 units (max 100)
 - volumeDown : Decrease volume by 10 units (min 0)
 - mute       : Mute the audio
 - unmute     : Unmute the audio
 - reset      : Reset system state and buffer
 - help       : Show the list of commands supported

[INFO] Displayed help information.

Enter command: play
[INPUT] Received: "play"
[INFO] Playing audio:
[INFO] Audio Buffer - Chunks: 5 / 10 | Front: 0 | Rear: 5
Buffer View: [F🟩][🟩][🟩][🟩][🟩][R🟩][⬜][⬜][⬜][⬜]

[AUDIO] Playing chunk: AUDIO_CHUNK_1
[AUDIO] Playing chunk: AUDIO_CHUNK_2
[INFO] Audio Buffer - Chunks: 3 / 10 | Front: 2 | Rear: 5
Buffer View: [⬜][⬜][F🟩][🟩][🟩][R🟩][⬜][⬜][⬜][⬜]

Enter command: pause
[INPUT] Received: "pause"
Audio buffer has been reset.
[INFO] Audio Buffer - Chunks: 0 / 10 | Front: 0 | Rear: 0
Buffer View: [⬜][⬜][⬜][⬜][⬜][⬜][⬜][⬜][⬜][⬜]
[INFO] Handling pause command: 
[INFO] System Status: Volume: 50 | Playing: No | Muted: No

Enter command: volumeUp
[INPUT] Received: "volumeUp"
[INFO] Handling volume up command: 
[INFO] System Status: Volume: 60 | Playing: No | Muted: No

Enter command: volumeDown
[INPUT] Received: "volumeDown"
[INFO] Handling volume down command: 
[INFO] System Status: Volume: 60 | Playing: No | Muted: No
[INFO] System Status: Volume: 70 | Playing: No | Muted: No

Enter command: mute
[INPUT] Received: "mute"
[INFO] Handling mute command:
[INFO] System Status: Volume: 60 | Playing: No | Muted: No\

Enter command: unmute
[INPUT] Received: "unmute"
[INFO] Handling unmute command: 
[INFO] System Status: Volume: 50 | Playing: No | Muted: No

Enter command: reset
[INPUT] Received: "reset"
[INFO] System reset: volume = 50 | playing = 0 | muted = 0
[INFO] Handling reset command: 
[INFO] System Status: Volume: 50 | Playing: No | Muted: No

Enter command: exit
[INFO] Exiting interactive mode.
[INFO] Command processor freed

```
