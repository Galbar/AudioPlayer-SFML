#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <unordered_map>
#include <string>

typedef std::unordered_map<std::string, std::pair<int, int>>::iterator res_table_it;

class AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    // Get pointer to instance
    static AudioPlayer* instance();
    // Delete instance
    static void clear();

    // Add music resource to the player and returns its resource id
    int loadMusic(const std::string& path);
    // Play music with resource id i
    bool playMusic(int i);
    // Play music with resource id i with volume 0 <= j <= 100
    bool playMusic(int i, float j);
    // Returns the current music time offset
    sf::Time getMusicOffset();
    // Sets the current music to a time offset of t
    void setMusicOffset(sf::Time t);
    // Stop playing current music
    void stopMusic();
    // Remove music resource
    void releaseMusic(int i);
    
    // Add sound resource to the player and returns its resource id
    int loadSound(const std::string& path);
    // Play sound with resource id i
    void playSound(int i);
    // Play sound with resource id i with volume 0 <= j <= 100
    void playSound(int i, float j);
    // Stop playing current sound
    void stopSound();
    // Remove sound resource
    void releaseSound(int i);


private:
    static AudioPlayer* s_audio_player;
    int m_resource_count;
    sf::Sound m_sound;
    sf::Music m_music;
    std::unordered_map<std::string, std::pair<int, int>> m_resource_table;
    std::unordered_map<int, res_table_it> m_reverse_resource_table;
    std::unordered_map<int, sf::SoundBuffer> m_sound_table;
    std::unordered_map<int, std::string> m_music_table;
};

#endif