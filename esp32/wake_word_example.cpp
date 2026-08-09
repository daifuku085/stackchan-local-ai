/*
 * wake_word_example.cpp
 *
 * Integration sketch for local wake-word detection on an ESP32-S3-based
 * StackChan device.
 *
 * Target wake word:
 *   コギト・エルゴ・スム
 *
 * IMPORTANT:
 * This file is intentionally an integration example, not a drop-in build target.
 * The exact AudioService / callback API depends on the firmware version and the
 * packaged ESP-SR / WakeNet assets used by the device.
 *
 * Adapt the callback registration and model-loading section to the actual
 * StackChan / Xiaozhi firmware tree you are building.
 */

#include <atomic>
#include <string>

namespace {

std::atomic<bool> g_wake_detected{false};

// Keep the logical wake-word identifier in one place.
// Depending on the generated WakeNet package, the callback may report a
// normalized model name rather than this literal Japanese string.
constexpr const char* kTargetWakeWord = u8"コギト・エルゴ・スム";

}  // namespace

/*
 * Pseudocode based on the AudioService callback pattern used by compatible
 * ESP32-S3 voice firmware.
 *
 * Replace the placeholder types/functions below with the actual API exposed
 * by your firmware version.
 */
void ConfigureWakeWordDetection(/* AudioService& audio_service,
                                  AudioCodec& codec */) {
    /*
    AudioServiceCallbacks callbacks{};

    callbacks.on_wake_word_detected =
        [](const std::string& wake_word) {
            // Some generated models may expose an internal identifier.
            // Confirm the actual callback value once the custom WakeNet
            // package is delivered.
            if (wake_word == kTargetWakeWord) {
                g_wake_detected.store(true);
            }
        };

    audio_service.SetCallbacks(callbacks);
    audio_service.Initialize(codec);

    // Load/register the packaged ESP-SR / WakeNet model assets here.
    //
    // Example concept:
    //   const auto* wake_model = Assets::Get(...);
    //   audio_service.LoadWakeWordModel(wake_model);
    //
    // Use the API provided by the firmware version you are integrating.

    audio_service.Start();
    */
}

/*
 * Call this from the main application loop/task.
 *
 * Once true:
 *   1. acknowledge the wake event,
 *   2. start or resume the voice interaction session,
 *   3. send audio to the local xiaozhi-esp32-server only after activation.
 */
bool ConsumeWakeWordEvent() {
    return g_wake_detected.exchange(false);
}
