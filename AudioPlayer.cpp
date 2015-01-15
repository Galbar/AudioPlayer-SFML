#include "AudioPlayer.hpp"

AudioPlayer* AudioPlayer::s_audio_player = NULL;

AudioPlayer::AudioPlayer()
{
    m_music.setLoop(true);
    m_resource_count = 0;
}

AudioPlayer* AudioPlayer::instance()
{
    if (s_audio_player == NULL)
    {
        s_audio_player = new AudioPlayer();
    }
    return s_audio_player;
}

void AudioPlayer::clear()
{
    if (s_audio_player != NULL)
        delete s_audio_player;
}

AudioPlayer::~AudioPlayer()
{
    stopMusic();
    stopSound();
}

bool AudioPlayer::playMusic(int i)
{
    if (!m_music.openFromFile(m_music_table[i]))
        return false;
    m_music.setVolume(100);
    m_music.play();
    return true;
}

bool AudioPlayer::playMusic(int i, float j)
{
    if (!m_music.openFromFile(m_music_table[i]))
        return false;
    m_music.setVolume(j);
    m_music.play();
    return true;
}

void AudioPlayer::playSound(int i)
{
    m_sound.setBuffer(m_sound_table[i]);
    m_sound.setVolume(100);
    m_sound.play();
}

void AudioPlayer::playSound(int i, float j)
{
    m_sound.setBuffer(m_sound_table[i]);
    m_sound.setVolume(j);
    m_sound.play();
}

void AudioPlayer::stopMusic()
{
    m_music.stop();
}

void AudioPlayer::stopSound()
{
    m_sound.stop();
}

int AudioPlayer::loadMusic(const std::string& path)
{
    auto it = m_resource_table.find(path);
    int i;
    if (it == m_resource_table.end())
    {
        i = m_resource_count++;
        m_music_table.insert(std::pair<int, std::string>(i, path));
        auto it = m_resource_table.insert(std::pair<std::string, std::pair<int, int>>(path, std::pair<int, int>(i, 0))).first;
        m_reverse_resource_table.insert(std::pair<int, res_table_it>(i, it));
    }
    else
    {
        it->second.second++;
        i = it->second.first;
    }
    return i;
}

int AudioPlayer::loadSound(const std::string& path)
{
    auto it = m_resource_table.find(path);
    int i;
    if (it == m_resource_table.end())
    {
        i = m_resource_count++;
        sf::SoundBuffer buffer;
        buffer.loadFromFile(path);
        m_sound_table.insert(std::pair<int, sf::SoundBuffer>(i, buffer));
        auto it = m_resource_table.insert(std::pair<std::string, std::pair<int, int>>(path, std::pair<int, int>(i, 0))).first;
        m_reverse_resource_table.insert(std::pair<int, res_table_it>(i, it));
    }
    else
    {
        it->second.second++;
        i = it->second.first;
    }
    return i;
}

void AudioPlayer::setMusicOffset(sf::Time t)
{
    m_music.setPlayingOffset(t);
}

sf::Time AudioPlayer::getMusicOffset()
{
    return m_music.getPlayingOffset();
}

void AudioPlayer::releaseSound(int i)
{
    auto it = m_reverse_resource_table.find(i)->second;
    it->second.second--;
    if (it->second.second == 0)
    {
        m_sound_table.erase(i);
        m_resource_table.erase(it->first);
        m_reverse_resource_table.erase(i);
    }
}

void AudioPlayer::releaseMusic(int i)
{
    auto it = m_reverse_resource_table.find(i)->second;
    it->second.second--;
    if (it->second.second == 0)
    {
        m_music_table.erase(i);
        m_resource_table.erase(it);
        m_reverse_resource_table.erase(i);
    }
}