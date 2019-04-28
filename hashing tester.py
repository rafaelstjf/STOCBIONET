
def hashing1(delayTime, precision, low, high, capacity):
    # usado atualmente
    """ 
    low = tempo atual
    high = tempo do maior delay + tempo atual
     """
    return ((delayTime - low) * ((1.0 / precision) / (high - (1 + low))) % capacity)


def hashing2(delayTime, precision, low, high, capacity):
    """
    d1 = delay - tempo atual
    high = tempo do maior delay
    """
    d1 = delayTime - low
    return (d1 * ((1.0 / precision) / (high - 1)) % capacity)


def hashing3(delayTime, precision, low, high, capacity):
    """
    low = inicio da simulação
    high = tempo máximo da simulação
    """
    return ((delayTime - low) * ((1.0/precision)/(high - (1 + low))) % capacity)


def hashing4(delayTime, capacity, lastDelay):
    """
    verifica o ultimo delay e passa a organizar a tabela fazendo o mod dele
    """
    if(lastDelay == 0):
        return (delayTime % capacity)
    else:
        return (round(delayTime % lastDelay))


def main():
    capacity = 1000
    precision = 0.000001
    op = int(input("OP: "))
    delayTime = float(input("DELAY TIME: "))
    if(op != 4):
        low = float(input("LOW: "))
        high = float(input("HIGH: "))
    if(op == 1):
        print(hashing1(delayTime, precision, low, high, capacity))
    elif(op == 2):
        print(hashing2(delayTime, precision, low, high, capacity))
    elif(op == 3):
        print(hashing3(delayTime, precision, low, high, capacity))
    elif(op == 4):
        lastDelay = float(input("LAST DELAY: "))
        print(hashing4(delayTime, capacity, lastDelay))


if(__name__ == "__main__"):
    main()
