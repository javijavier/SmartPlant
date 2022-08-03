import os

folder = "../Dataset/NOISE/"
count = 1
# count increase by 1 in each iteration
# iterate all files from a directory
for file_name in os.listdir(folder):
    # Construct old file name
    source = folder + file_name

    # Adding the count to the new file name and extension
    destination = "NOISE." + str(count) + ".wav"

    # Renaming the file
    os.rename(source, destination)
    count += 1

print('All Files Renamed')