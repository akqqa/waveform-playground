#include "SoundHandler.hpp"
#include <vector>

SoundHandler::SoundHandler()
    : m_samples(1024, 0)
{
    initialize(1, 44100, { sf::SoundChannel::Mono });
    m_currentSample = 0;
}

void SoundHandler::updateWaveform(const std::vector<std::int16_t>& samples) {
    m_samples = samples;
}

bool SoundHandler::onGetData(Chunk& data) {
    const std::size_t samplesToSend = 1024;
    m_tempBuffer.resize(samplesToSend);
    // loops over samples to send, going back to the start with mod size each time it reaches end
    for (std::size_t i = 0; i < samplesToSend; ++i)
    {
        m_tempBuffer[i] = m_samples[(m_currentSample + i) % m_samples.size()];
    }
    data.samples = m_tempBuffer.data();
    data.sampleCount = samplesToSend;

    // Sets counter right with mod
    m_currentSample = (m_currentSample + samplesToSend) % m_samples.size();

    return true;
}

void SoundHandler::onSeek(sf::Time timeOffset) {
    // Convert time to sample index
    m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate()) % m_samples.size();
}