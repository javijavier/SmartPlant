import os
import ffmpeg  

filePath = '../Dataset/HELLO/HELLO.0.wav'

def main():

    audio_input = ffmpeg.input(filePath)
    print(audio_input)
    ffmpeg.run(audio_input)

    #audio_cut = audio_input.audio.filter('atrim', duration= 0.5)   
    #audio_output  = ffmpeg.output(audio_cut, filePath)
    #ffmpeg.run(audio_output)

    print("Trimm Done!")

if __name__ == "__main__":
    main()