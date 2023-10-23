from random import randint

f = open("3test1.txt", "w")

def test3_1():
    difference = 500
    a = [randint(randint(-difference,difference),2*difference) for i in range(randint(1,10000))]
    f.write(str(len(a)) + "\n")
    for i in a:
        f.write(str(i) + "\n")
    a.sort()
    for i in a:
        f.write(str(i) + "\n")


def test3_2():
    difference = 50
    a = [randint(randint(-difference,difference),2*difference) for i in range(randint(1,10))]
    f.write(str(len(a)) + "\n")
    for i in a:
        f.write(str(i) + "\n")
    b = [randint(randint(-difference,difference),2*difference) for i in range(randint(1,10))]
    f.write(str(len(b)) + "\n")
    for i in b:
        f.write(str(i) + "\n")

    c = []
    for i in a:
        if i in b:
            c.append(i)
    f.write(str(len(c)) + "\n")
    c.sort()
    for i in c:
        f.write(str(i) + "\n")



test3_2()

f.close()