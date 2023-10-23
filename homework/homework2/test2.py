from random import randint

f = open("2test1.txt", "w")


def test2_1(n_fibonachi):
    f.write(str(n_fibonachi) + "\n")
    f_i2 = 1
    f_i1 = 1
    f_i3 = 1
    for i in range(3,n_fibonachi+1):
        f_i3 = f_i1+f_i2
        f_i1 = f_i2
        f_i2 = f_i3
    f.write(str(f_i3) + "\n")

def test2_2():
    m = randint(-10,10)
    n = randint(0,10)

    f.write(str(m) + "\n")
    f.write(str(n) + "\n")
    f.write(str(m**n) + "\n")


def test2_3():
    difference = 50
    a = [randint(randint(-difference,difference),2*difference) for i in range(randint(1,1000))]
    f.write(str(len(a)) + "\n")
    for i in a:
        f.write(str(i) + "\n")
    a.sort()
    for i in a:
        f.write(str(i) + "\n")


def test2_4():
    s = "Look C code"



test2_3()
f.close()