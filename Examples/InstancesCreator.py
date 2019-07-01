def weaklyCoupled():
    print("A[i] -> A[(i+1) mod M] \ni = 1..Number of reactions\n")
    k = int(input("Type the number of reactions\n"))
    m = int(input("Type the M value\n"))
    text_file = open("weaklyCoupled" + str(k) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1,k+1):
            text_file.write("A{}".format(i) + "=1;\n")
    for i in range(1,k+1):
        if(i == m-1):
            text_file.write("transcription,k1:" + "A{}".format(i) + "-> A{}".format(m)+ ";\n")
        else:
            text_file.write("transcription,k1:" + "A{}".format(i) + "-> A{}".format((i + 1) % m)+ ";\n")

def tightlyCoupled():
    #Colloidal Aggregation Model
    print("S[n] + S[m] -> S[n+m]\nS[n+m] -> S[n] + S[m]\n (m+n) = 2..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    text_file = open("tightlyCoupled-1-" + str(n) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1,n+1):
            text_file.write("S{}".format(i) + "=1;\n")
    for i in range(1, n+1):
        for j in range(i, n+1):
            if(j+i <=n):
                if(i==j):
                    text_file.write("transcription,k1:" + "2S{}".format(i) + "-> S{}".format(i+j)+ ";\n")    
                    text_file.write("transcription,k1:" + "S{}".format(i+j) + "-> 2S{}".format(i)+ ";\n")
                else:
                    text_file.write("transcription,k1:" + "S{}".format(i) + " + S{}".format(j) + "-> S{}".format(i+j)+ ";\n")
                    text_file.write("transcription,k1:" + "S{}".format(i+j) + "-> S{}".format(i) + " + S{}".format(j)+ ";\n")

def tightlyCoupledDelay():
    #Colloidal Aggregation Model
    print("S[n] + S[m] -> S[n+m]\nS[n+m] -> S[n] + S[m]\n (m+n) = 2..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    text_file = open("tightlyCoupled-1-" + str(n) + ".txt", "w")
    text_file.write("k1=1;\n")
    text_file.write("d1=0.1")
    for i in range(1,n+1):
            text_file.write("S{}".format(i) + "=1;\n")
    for i in range(1, n+1):
        for j in range(i, n+1):
            if(j+i <=n):
                if(i==j):
                    text_file.write("transcription,k1:" + "2S{}".format(i) + "-> S{}".format(i+j)+ ";\n")    
                    text_file.write("transcription,k1:" + "S{}".format(i+j) + "(d1)" + "-> 2S{}".format(i)+ + "(d1)" +";\n")
                else:
                    text_file.write("transcription,k1:" + "S{}".format(i) + " + S{}".format(j) + "-> S{}".format(i+j)+ ";\n")
                    text_file.write("transcription,k1:" + "S{}".format(i+j) + "-> S{}".format(i) + "(d1)" + " + S{}(d1)" +".format(j)+ ";\n")

def tightlyCoupled2():
    print("S[n] -> S[(n+1) mod M] + ... + S[(n+g) mod M] \n (n) = 1..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    m = int(input("Type the M value\n"))
    g = int(input("Type the g value\n"))
    text_file = open("tightlyCoupled-2-" + str(n) +"-"+ str(g) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1,n+1):
        text_file.write("S{}".format(i) + "=40;\n")
    for i in range(1,n+1):
        text_file.write("transcription,k1:" + "S{}".format(i) + "-> ")
        for j in range(1, (g+1)):
            text_file.write("S{}".format((1 + j) % m))
            if(j <g):
                text_file.write(" + ")
        text_file.write(";\n")

op = int(input("Choose a intance:\n1-Weakly Coupled\n2-Tightly Coupled-1\n3-Tightly Coupled-2\n"))
if(op==1):
    weaklyCoupled()
elif(op==2):
    tightlyCoupled()
elif(op==3):
    tightlyCoupled2()
elif(op==4):
    tightlyCoupledDelay()
