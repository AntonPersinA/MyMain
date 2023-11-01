
fw = open("big_int_test.txt", "w")
fr = open("big_int_test.txt", "r")


def sum1():
    i1 = 127 #на каких числах проверять
    i2 = 100 #на каких числах проверять
    for i in range(i1,i1+3):
        for j in range(i1,i1+30000):
            fw.write(str(bin(i))[2:]+'\n')
            fw.write(str(bin(j))[2:]+'\n')
            fw.write(str(bin(i+j))[2:]+'\n')



sum1()


fw.close()
fr.close()
