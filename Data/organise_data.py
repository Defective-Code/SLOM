# Open the file in read mode
with open('Data\Freq.txt', 'r') as file:
    # Iterate through each line in the file
    for line in file:
        # Process each line
        print(line.strip())  # Use .strip() to remove leading/trailing whitespace
