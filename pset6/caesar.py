import sys
from string import ascii_letters

if len(sys.argv)!=2:
    sys.exit(1)
charSet = ascii_letters
try:
    key = int(sys.argv[1], 10)
except ValueError:
    sys.exit(1)
    
text = input ("plaintext: ")
print("ciphertext: ",end="")
for char in text:
    charindex = charSet.find(char) + 1
    if charindex > 0:
        if charindex > 26:
            charindex = (charindex-26 + key)%26 + 25
        else:
            charindex = (charindex + key)%26 - 1
        print(charSet[charindex], end="")
    else:
        print(char, end="")
print("")        
