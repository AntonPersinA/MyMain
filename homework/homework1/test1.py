from random import randint

f = open("1test1.txt", "w")


def test1_1():
    a = randint(-10,10)
    b = randint(-10,10)
    f.write(str(a) + ' ' + str(b) + '\n')
    f.write(str(b) + ' ' + str(a))


def test1_2():
    size = 10
    k = 0
    a = [0]*size
    for i in range(size):
        h = randint(-5,5)
        a[i] = h
        if (h == 0):
            k+=1
    f.write(str(k) + " " + str(size) + "\n")
    for i in a:
        f.write(str(i) + "\n")


def test1_3(how_many_test):
    f.write(str(how_many_test)+"\n")
    f.write(str(10) + " " + str(0) + " " + str(0) + "\n")
    for i in range(how_many_test):
        a = randint(-300,300)
        b = randint(-300,300)
        while(b == 0):
            b = randint(-15,15)
        c = a%b
        f.write(str(a) + " " + str(b) + " " + str(c) + "\n")


def test1_4():
    f.write(str(55252) + "\n")

    
def test1_5(how_many_test):
    f.write(str(how_many_test)+"\n")
    for g in range(how_many_test):
        len_str = randint(1,4)
        str1 = ""
        if (randint(1,3) == 1):
            for i in range(len_str):
                if (randint(0,1)):
                    str1 = str1 + ')'
                else:
                    str1 = str1 + '('
        elif (randint(1,3) == 2):
            for i in range(len_str):
                if (randint(0,1)):
                    str1 = str1 + ']'
                else:
                    str1 = str1 + '['
        else:
            for i in range(len_str):
                if (randint(0,1)):
                    str1 = str1 + '{'
                else:
                    str1 = str1 + '}'
        skobe = 0
        flag = 0
        for iii in str1:
            if (iii in "{[("):
                skobe+=1
            if (iii in "}])"):
                skobe-=1
            if (skobe<0):
                f.write("0 ")
                f.write(str1+"\n")
                flag = 1
        if flag:
            continue
        if (skobe > 0):
            f.write("0 ")
            f.write(str1+"\n")
            continue
        f.write("1 ")
        f.write(str1+"\n")


def test1_6():
    test_num = randint(2,100)
    a=[]
    for i in range(2,test_num+1):
        flag = 1
        for j in range(2,int(i**0.5) + 1):
            if i%j == 0:
                flag = 0
                break
        if flag:
            a.append(i)

    f.write('\t'+str(len(a))+"\n")
    for i in a:
        f.write(str(i)+"\n")



def test1_7():
        str1 = ""
        str1_len = randint(2, 30)
        for i in range(str1_len):
            a = randint(97, 122)
            str1 = str1 + chr(a)

        str2 = ""
        str2_len = randint(1, 3)
        for i in range(str2_len):
            a = randint(97, 122)
            str2 = str2 + chr(a)

        answer1 = len(str1.split(str2)) - 1

        f.write(str(str1_len) + "\n")
        f.write(str1 + "\n")
        f.write(str(str2_len) + "\n")
        f.write(str2 + "\n")
        f.write(str(answer1) + "\n")


def test1_8():
    x1 = 1
    x2 = 8
    f.write(str(x1) + "\n")
    f.write(str(x2) + "\n")
    a = [randint(-10,10) for i in range(randint(10,11))]

    f.write(str(len(a)) + "\n")

    for i in a:
        f.write(str(i) + "\n")

    a_h = a[:x1] + a[x2:x1-1:-1] + a[x2+1:]

    for i in a_h:
        f.write(str(i) + "\n")



test1_4()












f.close()