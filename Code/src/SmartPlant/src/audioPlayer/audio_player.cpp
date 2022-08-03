//audio_player.cpp

#include "audio_player.h"
#include <iostream>
#include <map>

bool m_ErrEnd = false;

AudioPlayer::AudioPlayer(){

    m_TheAudio = nullptr;
    this->m_TheSD = SDClass();
    this->m_MyFile = File();
    this->m_uRemain_size = 0;
    this->m_TheParser = WavContainerFormatParser();
    this->m_uBuffer[sc_buffer_size];

}

AudioPlayer::~AudioPlayer(){


}

static void audio_attention_cb(const ErrorAttentionParam *atprm)
{
  puts("Attention!");
  
  if (atprm->error_code >= AS_ATTENTION_CODE_WARNING)
    {
      m_ErrEnd = true;
    }
}

void AudioPlayer::loadSoundFiles(){

    this->m_vSoundFiles.insert(std::pair<eAudioFiles,char*>(eAudioFiles::HELLO, "/mnt/sd0/sounds/HELLO.wav"));
    this->m_vSoundFiles.insert(std::pair<eAudioFiles,char*>(eAudioFiles::LIGHT_DARK, "/mnt/sd0/sounds/LIGHT_DARK.wav"));
    this->m_vSoundFiles.insert(std::pair<eAudioFiles,char*>(eAudioFiles::TEMP_GOOD, "/mnt/sd0/sounds/TEMP_GOOD.wav"));
    this->m_vSoundFiles.insert(std::pair<eAudioFiles,char*>(eAudioFiles::WATER_THIRSTY, "/mnt/sd0/sounds/WATER_THIRSTY.wav"));
}

char *AudioPlayer::getSoundFile(eAudioFiles eAudioFile){

    for (auto it = this->m_vSoundFiles.begin(); it != this->m_vSoundFiles.end(); ++it)
        if (it->first == eAudioFile)
            return it->second;

}

void AudioPlayer::initSD(){

    /* Initialize SD */
    while (!this->m_TheSD.begin())
    {
        /* wait until SD card is mounted. */
        Serial.println("Insert SD card.");
    }
}

void AudioPlayer::loadSoundInSD(eAudioFiles eAudioFile){

    /* Open file placed on SD card */
    this->m_MyFile = this->m_TheSD.open(this->getSoundFile(eAudioFile));

    /* Verify file open */
    if (!this->m_MyFile)
        {
        printf("File open error\n");
        exit(1);
        }
    printf("Open! %s\n", this->m_MyFile.name());
}

void AudioPlayer::initAudioLibrary(eAudioFiles eAudioFile){

    fmt_chunk_t fmt;
    handel_wav_parser_t *handle = (handel_wav_parser_t *)this->m_TheParser.parseChunk(this->getSoundFile(eAudioFile), &fmt);
    if (handle == NULL)
        {
        printf("Wav parser error.\n");
        exit(1);
        }

    // Get data chunk info from wav format
    uint32_t data_offset = handle->data_offset;
    this->m_uRemain_size = handle->data_size;

    this->m_TheParser.resetParser((handel_wav_parser *)handle);

    // start audio system
    this->m_TheAudio = AudioClass::getInstance();
    this->m_TheAudio->begin(audio_attention_cb);

    puts("initialization Audio Library");

    /* Set clock mode to normal */

    this->m_TheAudio->setRenderingClockMode((fmt.rate <= 48000) ? AS_CLKMODE_NORMAL : AS_CLKMODE_HIRES);

    /* Set output device to speaker with first argument.
    * If you want to change the output device to I2S,
    * specify "AS_SETPLAYER_OUTPUTDEVICE_I2SOUTPUT" as an argument.
    * Set speaker driver mode to LineOut with second argument.
    * If you want to change the speaker driver mode to other,
    * specify "AS_SP_DRV_MODE_1DRIVER" or "AS_SP_DRV_MODE_2DRIVER" or "AS_SP_DRV_MODE_4DRIVER"
    * as an argument.
    */
    this->m_TheAudio->setPlayerMode(AS_SETPLAYER_OUTPUTDEVICE_SPHP, AS_SP_DRV_MODE_LINEOUT);

    /*
    * Set main player to decode wav. Initialize parameters are taken from wav header.
    * Search for WAV decoder in "/mnt/sd0/BIN" directory
    */
    err_t err = this->m_TheAudio->initPlayer(AudioClass::Player0, AS_CODECTYPE_WAV, "/mnt/sd0/BIN", fmt.rate, fmt.bit, fmt.channel);

    /* Verify player initialize */
    if (err != AUDIOLIB_ECODE_OK)
    {
        printf("Player0 initialize error\n");
        exit(1);
    }

    this->setAudioToBegin(data_offset);
}

void AudioPlayer::setAudioToBegin(uint32_t data_offset){

    /* Set file position to beginning of data */
    this->m_MyFile.seek(data_offset);

    for (uint32_t i = 0; i < this->m_Sc_prestore_frames; i++)
    {
        size_t supply_size = this->m_MyFile.read(this->m_uBuffer, sizeof(this->m_uBuffer));
        this->m_uRemain_size-= supply_size;
        
        err_t err = this->m_TheAudio->writeFrames(AudioClass::Player0, this->m_uBuffer, supply_size);
        if (err != AUDIOLIB_ECODE_OK)
        {
            break;
        }
            
        if (this->m_uRemain_size == 0)
         {
            break;
        }
    }
}

void AudioPlayer::setVolume(int volume){

    this->m_TheAudio->setVolume(volume);
}

void AudioPlayer::init(){

    this->loadSoundFiles();

    this->initSD();

    this->initAudioLibrary(eAudioFiles::HELLO);

    this->loadSoundInSD(eAudioFiles::HELLO);
    
    this->setVolume(-160);
}

void AudioPlayer::stop(){

  this->m_TheAudio->stopPlayer(AudioClass::Player0);
  this->m_MyFile.close();
  this->m_TheAudio->setReadyMode();
  this->m_TheAudio->end();

}

void AudioPlayer:: respond(eAudioFiles audio){

     static bool is_carry_over = false;
     static size_t supply_size = 0;
     static const uint32_t sc_store_frames = 10;


     /* Send new frames to decode in a loop until file ends */
    for (uint32_t i = 0; i < sc_store_frames; i++)
        {
        if (!is_carry_over)
            {
            supply_size = this->m_MyFile.read(this->m_uBuffer, (this->m_uRemain_size < sizeof(this->m_uBuffer)) ? this->m_uRemain_size : sizeof(this->m_uBuffer));
            this->m_uRemain_size -= supply_size;
            }
        is_carry_over = false;

        int err = this->m_TheAudio->writeFrames(AudioClass::Player0, this->m_uBuffer, supply_size);

        if (err == AUDIOLIB_ECODE_SIMPLEFIFO_ERROR)
            {
            is_carry_over = true;
            break;
            }

        if (this->m_uRemain_size == 0)
            {
                this->stop();
                break;
            }
        }

    if (m_ErrEnd)
    {
        printf("Error End\n");
        this->stop();
    }
}