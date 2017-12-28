def det2(a):
    return a[0][0] * a[1][1] -  a[0][1] * a[1][0]
 
def det3(a):
    m1, m2, m3 = [], [], []
    for i in range(1, 3):
        m1.append(a[i][1:3])
        m2.append(a[i][0:1] + a[i][2:3])
        m3.append(a[i][0:2])
    return a[0][0] * det2(m1) - a[0][1] * det2(m2) + a[0][2] * det2(m3)
 
def det4(a):
    m1, m2, m3, m4 = [], [], [], []
    for i in range(1, 4):
        m1.append(a[i][1:4])
        m2.append(a[i][0:1] + a[i][2:4])
        m3.append(a[i][0:2] + a[i][3:4])
        m4.append(a[i][0:3])
    return a[0][0] * det3(m1) - a[0][1] * det3(m2) + a[0][2] * det3(m3) - a[0][3] * det3(m4)

matrix = eval(input())
ans = det4(matrix)
print(ans)
