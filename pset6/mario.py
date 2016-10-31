height=-1   
while height<0 or height>23:
    print("hello, write integer up to 23 ", end="")
    while True:
        try:
            height = input()
            height = int(height, 10)
            break
        except ValueError:
            pass
        print("Retry: ", end="")
     
for line in range (height):
    print(" "*(height-line)+"#"*line+"##")
    
