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

test1_5(10)

f.close()