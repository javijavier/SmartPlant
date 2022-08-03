import pyttsx3

TEXT = 'I have just drunk a lot. I will not need water for a while'
FILENAME = 'WATER_HIGH'
def main():

    converter = pyttsx3.init()

    voices = converter.getProperty('voices')
    voice = voices[2]
    converter.setProperty('rate', 130)
    converter.setProperty('volume', 0.8)

    converter.setProperty('voice', voice.id)
    filePath = "ML/Audios/" + FILENAME + ".mp3" 
    print(filePath)
    converter.save_to_file(TEXT, filePath) 
    converter.runAndWait()

    print("Sound file created!")

if __name__ == "__main__":
    main()