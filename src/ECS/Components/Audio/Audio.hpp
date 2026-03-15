#pragma once
#include "../Component.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "../../../rica.hpp"

class AudioComponent : public Component {
public:
  AudioComponent() {
    // ✅ Регистрируем поля для Details панели
  }

  const char* getComponentName() const override { return "Audio"; }

  void addSound(const std::string& tag, const std::string& path) {
    if (tag.empty() || path.empty()) {
      return;
    }
    Sound sound = LoadSound(path.c_str());
    audioVector.push_back({tag, path, sound, false});
    tagToIndex[tag] = audioVector.size() - 1;
  }

  ~AudioComponent() {
    for (auto& audio : audioVector) {
      UnloadSound(audio.sound);
    }
  }

  void play(const std::string& tag) {
    auto it = tagToIndex.find(tag);
    if (it != tagToIndex.end()) {
      size_t idx = it->second;
      PlaySound(audioVector[idx].sound);
      audioVector[idx].isPlaying = true;
    }
  }

  void stop(const std::string& tag) {
    auto it = tagToIndex.find(tag);
    if (it != tagToIndex.end()) {
      size_t idx = it->second;
      StopSound(audioVector[idx].sound);
      audioVector[idx].isPlaying = false;
    }
  }

  void pause(const std::string& tag) {
    auto it = tagToIndex.find(tag);
    if (it != tagToIndex.end()) {
      PauseSound(audioVector[it->second].sound);
    }
  }

  void resume(const std::string& tag) {
    auto it = tagToIndex.find(tag);
    if (it != tagToIndex.end()) {
      ResumeSound(audioVector[it->second].sound);
    }
  }

  void setVolume(const std::string& tag, float volume) {
    auto it = tagToIndex.find(tag);
    if (it != tagToIndex.end()) {
      SetSoundVolume(audioVector[it->second].sound, volume);
    }
  }

  void setVolumeAll(float volume) {
    for (auto& audio : audioVector) {
      SetSoundVolume(audio.sound, volume);
    }
  }

  void setPitch(const std::string& tag, float pitch) {
    auto it = tagToIndex.find(tag);
    if (it != tagToIndex.end()) {
      SetSoundPitch(audioVector[it->second].sound, pitch);
    }
  }

  void setPan(const std::string& tag, float pan) {
    auto it = tagToIndex.find(tag);
    if (it != tagToIndex.end()) {
      SetSoundPan(audioVector[it->second].sound, pan);
    }
  }

  void setPanAll(float pan) {
    for (auto& audio : audioVector) {
      SetSoundPan(audio.sound, pan);
    }
  }

  bool hasPlayingSounds() const {
    for (const auto& audio : audioVector) {
      if (audio.isPlaying && IsSoundPlaying(audio.sound)) {
        return true;
      }
    }
    return false;
  }

  const std::vector<size_t> getPlayingIndices() const {
    std::vector<size_t> indices;
    for (size_t i = 0; i < audioVector.size(); ++i) {
      if (audioVector[i].isPlaying && IsSoundPlaying(audioVector[i].sound)) {
        indices.push_back(i);
      }
    }
    return indices;
  }

private:
  struct AudioData {
    std::string tag;
    std::string path;
    Sound sound;
    bool isPlaying = false;
  };

  std::vector<AudioData> audioVector;
  std::unordered_map<std::string, size_t> tagToIndex;
};
