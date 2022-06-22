from matplotlib import pyplot as plt

f = open("out_com.txt", "r")
plt.rcParams["figure.figsize"] = [7.00, 3.50]
plt.rcParams["figure.autolayout"] = True
x = []
y = []
for j in range (10000):
    x.append(j)
for i in f:
    y.append(i)
#x = [i for i in range(50)]
#y = [i for i in range(50)]
plt.xlim(0, 10000)
plt.ylim(0, 15)
plt.grid()
plt.plot(x, y, marker="o", markersize=3, markeredgecolor="red", markerfacecolor="green")
plt.savefig("/home/pcedrim/codes/Filas/grafico_com.png")
#plt.show()