  
letters = 0
words = 1
sentences = 0

text = input("Text: ")
for c in text:
    if c.isalpha():
        letters += 1
    if c == " ":
        words += 1
    if c == "!" or c == "?" or c == ".":
        sentences += 1

L = letters/words * 100
S = sentences/words * 100

index = round(0.0588 * L - 0.296 * S - 15.8)
if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")