import pyttsx3
import random
import os
import ffmpeg  
from pydub import AudioSegment

SPANHSIH_KEY = 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\Tokens\TTS_MS_ES-ES_HELENA_11.0'
random.seed(5)


TEXT = 'How are you'
LABEL = 'HOW_ARE_YOU'

def main():

    converter = pyttsx3.init()
    fileCounter = 0
    filesPath  = []
    os.mkdir('../Dataset/'+ LABEL)

    voices = converter.getProperty('voices')

    for samples in range(0, 40):

        rate = int(random.random()*50 + 130)
        volume = random.random()/2 + 0.5
        converter.setProperty('rate', rate)
        converter.setProperty('volume', volume)

        for voice in voices:

            if(voice.id != SPANHSIH_KEY):
                converter.setProperty('voice', voice.id)
                filePath = "../Dataset/" + LABEL + "/"+ LABEL + "." + str(fileCounter) + ".wav" 
                converter.save_to_file(TEXT, filePath) 
                filesPath.append(filePath)
                fileCounter = fileCounter + 1

    converter.runAndWait()

    for file in filesPath:

        sound = AudioSegment.from_wav(file)

        startTime = 100
        endTime = startTime -218.1633 + 222.466*len(TEXT) - 19.46429*pow(len(TEXT),2) + 0.6207483*pow(len(TEXT),3) 
        extract = sound[startTime:endTime]
        extract.export(file, format = "wav")

    print("Sound files created!")

if __name__ == "__main__":
    main()