def weak():
    k = int(input("Type the number of reactions\n"))
    m = int(input("Type the M value\n"))
    text_file = open("weak" + str(k) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1,k+1):
            text_file.write("A{}".format(i) + "=1;\n")
    for i in range(1,k+1):
        if(i == m-1):
            text_file.write("transcription,k1:" + "A{}".format(i) + "-> A{}".format(m)+ ";\n")
        else:
            text_file.write("transcription,k1:" + "A{}".format(i) + "-> A{}".format((i + 1) % m)+ ";\n")

weak()
