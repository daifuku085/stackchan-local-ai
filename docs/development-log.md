# Development Log

This document records the implementation status of the local StackChan voice AI
project.

## 2026-08

### ESP32-S3 / StackChan

- StackChan hardware obtained and tested.
- Device voice interaction confirmed.
- ESP-IDF environment prepared.
- ESP-IDF 5.5.4 build environment confirmed.
- Firmware build completed successfully.
- Investigated moving wake-word detection from continuous server-side audio
  streaming to the ESP32-S3.

### Local AI server

- Docker / WSL environment prepared.
- `xiaozhi-esp32-server` launched locally.
- WebSocket endpoint configured for the ESP32-S3 client.
- Local server communication confirmed.

### Local ASR

- FunASR configured.
- SenseVoiceSmall model loaded locally.
- Local speech-recognition path confirmed.

### Local LLM

- Ollama installed and tested.
- Initial model: `qwen2.5:1.5b`.
- Ollama REST response confirmed.
- `xiaozhi-esp32-server` configured to use the local Ollama endpoint.

### Wake word

Target phrase:

> **コギト・エルゴ・スム**

Pronunciation:

> **Ko-gi-to E-ru-go Su-mu**

Language:

> **Japanese**

Current status:

- Reviewed ESP-SR / WakeNet community wake-word training.
- Confirmed Japanese is a supported target for the current TTS-based training
  pipeline.
- Preparing a custom WakeNet model request.
- Integration point for the wake-word callback identified.
- Custom model not yet available.

Next milestone:

- Obtain the custom WakeNet model from the ESP-SR community program.
- Package/load the generated model assets on the ESP32-S3.
- Confirm the callback identifier returned by the model.
- Trigger the local voice session only after wake-word detection.

### Local TTS

- Local Japanese speech synthesis is part of the planned architecture.
- TTS engine selection and voice evaluation are ongoing.

### RAG / local knowledge base

Planned, not yet implemented.

Goals:

- Load a locally stored knowledge collection.
- Retrieve relevant passages before LLM generation.
- Make the assistant explicitly indicate when the requested information is not
  available in the local knowledge base.

## Current checklist

- [x] StackChan hardware available
- [x] ESP-IDF 5.5.4 environment
- [x] ESP32-S3 firmware build
- [x] xiaozhi-esp32-server running locally
- [x] Local WebSocket communication
- [x] FunASR / SenseVoiceSmall
- [x] Ollama
- [x] qwen2.5:1.5b
- [x] Basic voice interaction
- [ ] Custom Japanese WakeNet model
- [ ] 「コギト・エルゴ・スム」 local wake detection
- [ ] Wake-triggered conversation flow
- [ ] Final local Japanese TTS selection
- [ ] Local RAG knowledge base
