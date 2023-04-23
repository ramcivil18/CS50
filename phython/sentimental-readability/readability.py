# Import the get_string function from the cs50 library
from cs50 import get_string

# Get a string from the user
text = get_string("Enter your text: ")

# Initialize variables to store the number of letters, sentences, and words in the text
letters = 0
sentence = 0
words = 1

# Get the length of the text
l = len(text)

# Iterate over the characters in the text
for i in range(l):
    # If the character is an alphabetical character, increment the letter count
    if (text[i].isalpha()):
        letters += 1
    # If the character is a space, increment the word count
    if (text[i] == " "):
        words += 1
    # If the character is a period, exclamation mark, or question mark, increment the sentence count
    if text[i] in [".", "!", "?"]:
        sentence += 1

# Calculate the average number of letters per 100 words
avg_L = letters / words * 100

# Calculate the average number of sentences per 100 words
avg_S = sentence / words * 100

# Calculate the readability index using the formula given in the prompt
index = round(0.0588 * avg_L - 0.296 * avg_S - 15.8)

# Print the appropriate message based on the value of the readability index
if (index < 1):
    print("Before Grade 1")
elif (index > 15):
    print("Grade 16+")
else:
    print(f"Grade {index}")
