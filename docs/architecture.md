# Architecture

## Goal

The project aims to keep wake-word detection on the ESP32-S3 while running
speech recognition, language-model inference, and speech synthesis on a local
server.

The target wake word is:

> **コギト・エルゴ・スム**

## High-level flow

```text
                    User
                     │
             "コギト・エルゴ・スム"
                     │
                     ▼
          ┌─────────────────────┐
          │ ESP32-S3 / StackChan│
          │                     │
          │ ESP-SR / WakeNet    │
          └──────────┬──────────┘
                     │
             wake word detected
                     │
                     ▼
          ┌─────────────────────┐
          │ Voice session starts│
          │ WebSocket / LAN     │
          └──────────┬──────────┘
                     │
                     ▼
          ┌─────────────────────┐
          │ xiaozhi-esp32-server│
          └──────────┬──────────┘
                     │
          ┌──────────┴──────────┐
          ▼                     ▼
┌──────────────────┐   ┌──────────────────┐
│ FunASR           │   │ Ollama           │
│ SenseVoiceSmall  │   │ qwen2.5:1.5b     │
│ Local ASR        │   │ Local LLM        │
└────────┬─────────┘   └────────┬─────────┘
         │                      │
         └──────────┬───────────┘
                    ▼
          ┌─────────────────────┐
          │ Local TTS           │
          └──────────┬──────────┘
                     │
                     ▼
          ┌─────────────────────┐
          │ StackChan speaker   │
          │ Voice response      │
          └─────────────────────┘
```

## Component responsibilities

### ESP32-S3 / StackChan

- Continuously monitors microphone input for the wake word.
- Runs ESP-SR / WakeNet locally.
- Does not need to continuously stream idle microphone audio to the PC.
- Starts the voice interaction after a successful wake-word detection.
- Plays the synthesized response through the device speaker.

### xiaozhi-esp32-server

- Provides the local voice-session backend.
- Accepts audio from the ESP32-S3 over the local network.
- Connects ASR, LLM, and TTS components.

### Local ASR

Current implementation:

- FunASR
- SenseVoiceSmall

The ASR stage converts the user's post-wake speech into text.

### Local LLM

Current implementation:

- Ollama
- qwen2.5:1.5b

The initial goal is a lightweight model that runs acceptably on modest local
hardware. Larger or alternative models can be evaluated later.

### Local TTS

The TTS component converts the generated response back to speech.

A Japanese local TTS engine is being evaluated separately so the complete
voice path can remain local.

## Wake-word behavior

Desired idle-state behavior:

```text
Idle
  │
  ├─ microphone processed locally by WakeNet
  │
  └─ no continuous ASR/LLM processing

"コギト・エルゴ・スム"
  │
  ▼
WakeNet detects phrase
  │
  ▼
Voice session activated
  │
  ▼
ASR → LLM → TTS
  │
  ▼
Return to wake-word idle state
```

## Future RAG layer

A later phase will add a local knowledge base.

```text
Speech
  ↓
ASR
  ↓
User question
  ↓
Local retrieval / RAG
  ↓
Relevant local documents
  ↓
Local LLM
  ↓
TTS
```

The assistant should distinguish between information it can retrieve and
information that is not present in its local knowledge base rather than
inventing an answer.

## Privacy and locality

The intended architecture keeps the main AI processing inside the user's local
network:

- wake-word detection: ESP32-S3
- ASR: local server
- LLM: local server
- TTS: local server
- future RAG data: local storage

External cloud AI services are not required for the intended final system.
