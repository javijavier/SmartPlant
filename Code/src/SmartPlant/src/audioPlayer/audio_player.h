//audio_player.h

//This library is used to reproduce .wav files in Spresense board
#include <Audio.h>
#include <SDHCI.h>

#include "common/common_data.h"
#include <iostream>
#include <map>

class AudioPlayer {

    private:

        AudioClass *m_TheAudio;
        SDClass m_TheSD;
        File m_MyFile;
        WavContainerFormatParser m_TheParser;
        
        const int32_t sc_buffer_size = 6144;
        static const uint32_t m_Sc_prestore_frames = 10;

        uint8_t *m_uBuffer;
        uint32_t m_uRemain_size;

        std::map<eAudioFiles, char*> m_vSoundFiles;

        void loadSoundFiles();
        char *getSoundFile(eAudioFiles eAudioFile);
        void initSD();
        void loadSoundInSD(eAudioFiles eAudioFile);
        void setAudioToBegin(uint32_t data_offset);
        void initAudioLibrary(eAudioFiles eAudioFile);

        static void audio_attention_cb(const ErrorAttentionParam *atrm);

    public:

        AudioPlayer();
        ~AudioPlayer();

        void setVolume(int volume);
        void respond(eAudioFiles audioFile);
        void init();
        void stop();

    
};