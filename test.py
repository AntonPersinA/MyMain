# all = 52
# with_out_tyz = all - 4
# p = 1
# o = 48/52*47/51*46/50*45/49*44/48*43/47
# a = [0]*5
# print(o)
# for i in range(6):
#     k = 1
#     for j in range(1,k + 1):
#         p *= with_out_tyz/all
#         all-=1
#         with_out_tyz-=1
# a[0] = p
# print("p(0) = ", a[0])
# p = 1
# a[1] = 4/52 + 48/52*47/51*4/52 + 48/52*47/51*46/50*4/52 + 48/52*47/51*46/50*45/49*4/52 + 48/52*47/51*46/50*45/49*44/48*4/52
# a[2] = 4/52(3/51 + 47/51*3/50*4/52 + 48/52*47/51*46/50*4/52 + 48/52*47/51*46/50*45/49*4/52)
# print(a)
# def f(podbras, kolv_kart, kolv_v_kolode):
# print(7392265542/(52*51*50*49*48*47))
#
































# print(4/52 +
#       48/52*4/51 +
#       48*47*4/52/51/50 +
#       48*47*46*4/52/51/50/49 +
#       48*47*46*45*4/52/51/50/49/48 +
#       48*47*46*45*44*4/52/51/50/49/48/47)


# print(4/52 +
#       48/52*4/51 +
#       48*47*4/52/51/50 +
#       48*47*46*4/52/51/50/49 +
#       48*47*46*45*4/52/51/50/49/48 +
#       48*47*46*45*44*4/52/51/50/49/48/47)
k = 52
def s2(k, t): #k, 4
    s2 = (k-4)/k*t/(k-1)
def s3(k, t):
    s3 = (k-4)*(k-5)*t/k/(k-1)/(k-2)
def s4(k, t):
    s4 = (k-4)*(k-5)*t/k/(k-1)/(k-2)*(k-6)/(k-2)
def s5(k, t):
    s5 = (k-4)*(k-5)*t/k/(k-1)/(k-2)*(k-6)/(k-2)*(k-7)/(k-3)
def s6(k, t):
    s6 = (k-4)*(k-5)*t/k/(k-1)/(k-2)*(k-6)/(k-2)*(k-7)/(k-3)























