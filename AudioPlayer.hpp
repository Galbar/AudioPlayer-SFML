#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>

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
    int addMusic(std::string path);
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
    
    // Add sound resource to the player and returns its resource id
    int addSound(std::string path);
    // Play sound with resource id i
    void playSound(int i);
    // Play sound with resource id i with volume 0 <= j <= 100
    void playSound(int i, float j);
    // Stop playing current sound
    void stopSound();


private:
    static AudioPlayer* s_audio_player;
    std::vector<sf::SoundBuffer> m_sound_list;
    std::vector<std::string> m_music_list;
    sf::Sound m_sound;
    sf::Music m_music;
};

#endif