import numpy as np
import matplotlib.pyplot as plt

test_0 = np.genfromtxt('const_temp_up_Humudity.txt', dtype= None)
# test
test_p0 = []
test_p1 = []
test_p2 = []
for i in test_0:
    V = i.decode('UTF-8').split(";")
    test_p0.append(int(V[0]))
    test_p1.append(int(V[1]))
    test_p2.append(int(V[2]))

test_certo_p2 = [i for i in test_p2 if i < 150]
test_certo_p1 = [i for i in test_p1 if i < 150]
test_certo_p0 = [i for i in test_p0 if i < 150]

x = np.linspace(start=0, stop=len(test_certo_p1*5)/60, num=len(test_certo_p1))
y = test_certo_p1
plt.plot(x, y)
plt.show()
print("Umidade")

x = np.linspace(start=0, stop=len(test_certo_p2*5)/60, num=len(test_certo_p2))
y = test_certo_p2
plt.plot(x, y)
plt.show()
print("Temperatura")