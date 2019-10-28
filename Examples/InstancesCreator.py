def weaklyCoupled():
    print("A[i] -> A[(i+1) mod M] \ni = 1..Number of reactions\n")
    k = int(input("Type the number of reactions\n"))
    m = int(input("Type the M value\n"))
    text_file = open("weaklyCoupled-" + str(k) +"-" + str(m) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1, k+1):
        text_file.write("A{}".format(i) + "=1;\n")
    for i in range(1, k+1):
        if(i == m-1):
            text_file.write("transcription,k1:" +
                            "A{}".format(i) + "-> A{}".format(m) + ";\n")
        else:
            text_file.write("transcription,k1:" + "A{}".format(i) +
                            "-> A{}".format((i + 1) % m) + ";\n")

def weaklyCoupled2():
    print("S[i] -> S[j]\ni = 1..Number of reactions, j = 2... Number of reactions + 1")
    n = int(input("Type the number of reactions\n"))
    text_file = open("weaklyCoupled2-" + str(n) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "=1000;\n")
    it2 = 2
    it = 1
    while(it2 <= n):
        text_file.write("transcription, k1:" + "S{}".format(it) + " -> S{};\n".format(it2))
        it = it + 2
        it2 = it2 + 2
    text_file.close()

def weaklyCoupled2Delay():
    print("S[i] -> S[j](d1)\ni = 1..Number of reactions, j = 2... Number of reactions + 1")
    n = int(input("Type the number of reactions\n"))
    text_file = open("weaklyCoupled2-delay-" + str(n) + ".txt", "w")
    text_file.write("k1=1;\nd1=0.1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "=1000;\n")
    it2 = 2
    it = 1
    while(it2 <= n):
        text_file.write("transcription, k1:" + "S{}".format(it) + " -> S{}(d1);\n".format(it2))
        it = it + 2
        it2 = it2 + 2
    text_file.close()

def tightlyCoupled():
    # Colloidal Aggregation Model
    print("S[n] + S[m] -> S[n+m]\nS[n+m] -> S[n] + S[m]\n (m+n) = 2..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    text_file = open("tightlyCoupled-1-" + str(n) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "=1;\n")
    for i in range(1, n+1):
        for j in range(i, n+1):
            if(j+i <= n):
                if(i == j):
                    text_file.write(
                        "transcription,k1:" + "2S{}".format(i) + "-> S{}".format(i+j) + ";\n")
                    text_file.write(
                        "transcription,k1:" + "S{}".format(i+j) + "-> 2S{}".format(i) + ";\n")
                else:
                    text_file.write("transcription,k1:" + "S{}".format(i) +
                                    " + S{}".format(j) + "-> S{}".format(i+j) + ";\n")
                    text_file.write("transcription,k1:" + "S{}".format(i+j) +
                                    "-> S{}".format(i) + " + S{}".format(j) + ";\n")


def tightlyCoupledDelay():
    # Colloidal Aggregation Model with delay
    print("S[n] + S[m] -> S[n+m]\nS[n+m] -> S[n] + S[m]\n (m+n) = 2..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    text_file = open("tightlyCoupled-1-Delay-" + str(n) + ".txt", "w")
    text_file.write("k1=1;\n")
    text_file.write("d1=0.1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "=1;\n")
    for i in range(1, n+1):
        for j in range(i, n+1):
            if(j+i <= n):
                if(i == j):
                    text_file.write(
                        "transcription,k1:" + "2S{}".format(i) + "-> S{}".format(i+j) + ";\n")
                    text_file.write("transcription,k1:" + "S{}".format(i+j) +
                                    "(d1)" + "-> 2S{}".format(i) + + "(d1)" + ";\n")
                else:
                    text_file.write("transcription,k1:" + "S{}".format(i) +
                                    " + S{}".format(j) + "-> S{}".format(i+j) + ";\n")
                    text_file.write("transcription,k1:" + "S{}".format(i+j) +
                                    "-> S{}".format(i) + "(d1)" + " + S{}(d1)".format(j) + ";\n")


def tightlyCoupled2():
    print("S[n] -> S[(n+1) mod M] + ... + S[(n+g) mod M] \n (n) = 1..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    m = int(input("Type the M value\n"))
    g = int(input("Type the g value\n"))
    text_file = open("tightlyCoupled-2-" + str(n) + "-" + str(m) + "-" + str(g) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "=40;\n")
    for i in range(1, n+1):
        text_file.write("transcription,k1:" + "S{}".format(i) + "-> ")
        for j in range(1, (g+1)):
            text_file.write("S{}".format((1 + j) % m))
            if(j < g):
                text_file.write(" + ")
        text_file.write(";\n")


def tightlyCoupled2Delay():
    print("S[n] -> S[(n+1) mod M] + ... + S[(n+g) mod M] \n (n) = 1..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    m = int(input("Type the M value\n"))
    g = int(input("Type the g value\n"))
    text_file = open("tightlyCoupled-2-Delay-" + str(n) + "-" + str(m) + "-" + str(g) + ".txt", "w")
    text_file.write("k1=1;\n")
    text_file.write("d1=0.1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "=40;\n")
    for i in range(1, n+1):
        text_file.write("transcription,k1:" + "S{}".format(i) + "-> ")
        for j in range(1, (g+1)):
            text_file.write("S{}(d1)".format((1 + j) % m))
            if(j < g):
                text_file.write(" + ")
        text_file.write(";\n")

def tightlyCoupled3():
    print("S[n] -> S[1] + ... + S[n-1]] \n (n) = 1..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    text_file = open("tightlyCoupled-3-" + str(n) + ".txt", "w")
    text_file.write("k1=1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "= 1;\n")
    for i in range(1, n+1):
        text_file.write("transcription,k1:" + "S{}".format(i) + "-> ")
        for j in range(1, (i)):
            if(j!=i):
                text_file.write("S{}".format(j))
            if(j < (i-1)):
                text_file.write(" + ")
        text_file.write(";\n")

def tightlyCoupled3Delay():
    print("S[n] -> S[1] + ... + S[n-1]] \n (n) = 1..Number of reactions\n")
    n = int(input("Type the number of reactions\n"))
    text_file = open("tightlyCoupled-3-delay" + str(n) + ".txt", "w")
    text_file.write("k1=1;\nd1=1;\n")
    for i in range(1, n+1):
        text_file.write("S{}".format(i) + "= 1;\n")
    for i in range(1, n+1):
        text_file.write("transcription,k1:" + "S{}".format(i) + "-> ")
        for j in range(1, (i)):
            if(j!=i):
                text_file.write("S{}(d1)".format(j))
            if(j < (i-1)):
                text_file.write(" + ")
        text_file.write(";\n")
op = int(input(
    "Choose a intance:\n1-Weakly Coupled\n2-Tightly Coupled-1\n3-Tightly Coupled-2\n4-Tightly Coupled-1 with delay\n5-Tightly Coupled-2 with delay\n6-Tightly Coupled-3\n7-Tightly Coupled-3 with delay\n8-Weakly Coupled-2\n9-Weakly Coupled-2-Delay\n"))
if(op == 1):
    weaklyCoupled()
elif(op == 2):
    tightlyCoupled()
elif(op == 3):
    tightlyCoupled2()
elif(op == 4):
    tightlyCoupledDelay()
elif(op == 5):
    tightlyCoupled2Delay()
elif(op == 6):
    tightlyCoupled3()
elif(op == 7):
    tightlyCoupled3Delay()
elif(op == 8):
    weaklyCoupled2()
elif(op == 9):
    weaklyCoupled2Delay()


