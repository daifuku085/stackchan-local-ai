# StackChan Local AI Assistant

A fully local, voice-interactive AI assistant built around an ESP32-S3-based StackChan device and a local AI server.

The goal is a small, standalone AI assistant that wakes on a custom Japanese wake word and holds a voice conversation entirely without cloud AI services.

## Overview

The assistant uses an ESP32-S3 device as the voice interface, communicating with a local server that handles speech recognition, language-model inference, and speech synthesis.

The planned wake word is:

> **コギト・エルゴ・スム**
> *Ko-gi-to E-ru-go Su-mu*

Wake word detection is intended to run entirely on-device, using ESP-SR / WakeNet on the ESP32-S3. Once the wake word is detected, the device starts a voice conversation with the local AI system.

## Architecture

```text
             "コギト・エルゴ・スム"
                       │
                       ▼
              ┌─────────────────┐
              │   ESP32-S3      │
              │   StackChan     │
              │                 │
              │ ESP-SR/WakeNet  │
              └────────┬────────┘
                       │
               Wake word detected
                       │
                       ▼
              ┌─────────────────┐
              │  Local AI Server│
              │                 │
              │  Local ASR      │
              │       ↓         │
              │  Local LLM      │
              │       ↓         │
              │  Local TTS      │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
              │    StackChan    │
              │  Voice Response │
              └─────────────────┘
```

## Hardware

* ESP32-S3-based device
* M5Stack / StackChan-compatible hardware
* Microphone
* Speaker

The ESP32-S3 acts as the user-facing voice interface.

## Software

### ESP32-S3

* ESP-IDF
* ESP-SR
* WakeNet
* StackChan firmware

### Local AI Server

* **xiaozhi-esp32-server** for voice interaction
* **FunASR / SenseVoiceSmall** for local speech recognition
* **Ollama** for local LLM inference
* **Qwen3 4B Q4_K_M** as the initial local language model
* A local text-to-speech engine

The AI server runs on the local network, so no AI inference depends on a cloud service.

## Why Local Wake Word Detection?

The project already runs AI processing on a local server. Running wake word detection directly on the ESP32-S3 adds further benefits:

* Microphone audio doesn't need to stream continuously to the server.
* Wake word detection works independently of the LLM.
* Network traffic drops while the device is idle.
* Voice interaction can start immediately after local detection.
* The overall system becomes more privacy-friendly and self-contained.

## Current Status

* [x] ESP32-S3 / StackChan firmware
* [x] Local network communication
* [x] xiaozhi-esp32-server
* [x] Local speech recognition
* [x] Ollama local LLM
* [x] Voice interaction between StackChan and the local server
* [ ] Custom Japanese WakeNet model
* [ ] Local detection of 「コギト・エルゴ・スム」
* [ ] Wake-word-triggered conversation flow
* [ ] Integration with a local knowledge base / RAG

## Future Work

1. Add local WakeNet detection for 「コギト・エルゴ・スム」
2. Start voice conversations only after wake word detection
3. Improve local Japanese speech synthesis
4. Add a local knowledge base using RAG
5. Improve response latency on low-power local hardware
6. Make the complete system usable without any external cloud AI services

## Project Goal

The long-term goal is a compact local AI terminal that can:

* stay idle while listening only for its wake word,
* activate when called,
* understand spoken Japanese,
* search a locally stored knowledge base,
* answer using a local language model,
* clearly indicate when the requested information isn't available,
* and respond using synthesized speech.

This project is a personal, open-source experiment in local voice AI on ESP32-S3 devices.
