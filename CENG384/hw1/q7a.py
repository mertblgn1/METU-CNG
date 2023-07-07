import numpy as np
import matplotlib.pyplot as plt

# read CSV file and store values into numpy array
xn = np.genfromtxt('chirp_part_a.csv', delimiter=',')

# calculate x[-n] and store it into a new numpy array x_n
x_n = xn[::-1]

# calculate the even component of the signal and store it into a new numpy array evenPart
evenPart = 0.5 * (xn + x_n)
# calculate the odd component of the signal and store it into a new numpy array oddPart
oddPart = 0.5 * (xn - x_n)


# create a figure with two subplots
fig, axs = plt.subplots(2, 1)
fig.suptitle('chirp_part_a')


# plot evenPart in the first subplot
axs[0].plot(evenPart)
axs[0].set_title('Even Part of the Signal')
axs[0].set_xlabel('Values')
axs[0].set_ylabel('Amplitude')

# plot oddPart in the second subplot
axs[1].plot(oddPart)
axs[1].set_title('Odd Part of the Signal')
axs[1].set_xlabel('Values')
axs[1].set_ylabel('Amplitude')

# adjust the layout of the subplots
fig.tight_layout()

# display the plot
plt.show()
