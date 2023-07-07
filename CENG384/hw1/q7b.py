import numpy as np
import matplotlib.pyplot as plt

# read CSV file and store values into numpy array
xn = np.genfromtxt('chirp_part_b.csv', delimiter=',')

# set the second and the third elements of xn as variables a and b
a = int(xn[1])
b = int(xn[2])

# calculate shifted and scaled xn
n = np.arange(len(xn))
shiftedScaledxn = xn * (n - b) / a
# plot original and shifted/scaled signals
fig = plt.figure(num='chirp_part_b')
plt.plot(n, xn, label='Original')
plt.plot(n, shiftedScaledxn, label='Shifted/Scaled')
plt.legend()
plt.show()
