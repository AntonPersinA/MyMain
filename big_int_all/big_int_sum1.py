
fw = open("big_int_test.txt", "w")
fr = open("big_int_test.txt", "r")


def sum1():
    i1 = 0 #на каких числах проверять
    i2 = 0 #на каких числах проверять
    for i in range(i1,i1+1000):
        for j in range(i2,i2+1000):
            fw.write(str(bin(i))[2:]+'\n')
            fw.write(str(bin(j))[2:]+'\n')
            fw.write(str(bin(i+j))[2:]+'\n')

sum1()


fw.close()
fr.close()
