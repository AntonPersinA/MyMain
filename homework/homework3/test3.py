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
    difference = 3
    a = [randint(randint(-difference,difference),2*difference) for i in range(randint(1,100000))]
    f.write(str(len(a)) + "\n")
    for i in a:
        f.write(str(i) + "\n")
    b = [randint(randint(-difference,difference),2*difference) for i in range(randint(1,10))]
    f.write(str(len(b)) + "\n")
    for i in b:
        f.write(str(i) + "\n")

    c = []
    a.sort()
    for i in b:
        if i in a:
            c.append(i)
    f.write(str(len(c)) + "\n")
    c.sort()
    # print(a);
    # print(b);
    # print(c);
    for i in c:
        f.write(str(i) + "\n")


def test3_3():
    difference = 3
    a = [randint(randint(-difference,difference),2*difference) for i in range(randint(1,5000))]
    f.write(str(len(a)) + "\n")

    a.sort(reverse = 1)

    maximum = 1
    element = a[0]
    for i in a:
        max_now = a.count(i)
        if(maximum<=max_now):
            element = i
            maximum = max_now

    f.write(str(element) + "\n")

    for i in a:
        f.write(str(i) + "\n")



test3_3()

f.close()