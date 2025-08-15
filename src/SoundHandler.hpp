#pragma once
#include <SFML/Audio.hpp>
#include <vector>

class SoundHandler : public sf::SoundStream {
    public:
        SoundHandler();

        void updateWaveform(const std::vector<std::int16_t>& samples);

    protected:
        // Mandatory overrides
        virtual bool onGetData(Chunk& data) override;
        virtual void onSeek(sf::Time timeOffset) override;

    private:
        std::vector<std::int16_t> m_samples;
        std::size_t m_currentSample;
        std::vector<std::int16_t> m_tempBuffer;
};