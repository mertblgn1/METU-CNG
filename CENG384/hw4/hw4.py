import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile

def fft(x):
    N = len(x)
    if N <= 1:
        return x
    even = fft(x[0::2])
    odd = fft(x[1::2])
    T = [np.exp(-2j * np.pi * k / N) * odd[k] for k in range(N // 2)]
    return [even[k] + T[k] for k in range(N // 2)] + [even[k] - T[k] for k in range(N // 2)]

def ifft(X):
    N = len(X)
    if N <= 1:
        return X
    even = ifft(X[0::2])
    odd = ifft(X[1::2])
    T = [np.exp(2j * np.pi * k / N) * odd[k] for k in range(N // 2)]
    return np.array([(even[k] + T[k]) / 2 for k in range(N // 2)] + [(even[k] - T[k]) / 2 for k in range(N // 2)])

# Read the encoded voice message
sample_rate, encoded_audio = wavfile.read('encoded.wav')
# Convert the audio to a mono channel if needed
if len(encoded_audio.shape) > 1:
    encoded_audio = encoded_audio[:, 0]

# Apply the decoding process using custom FFT and IFFT
frequency_domain = fft(encoded_audio)
midpoint = len(frequency_domain) // 2
positive_frequencies = frequency_domain[midpoint:]
negative_frequencies = frequency_domain[:midpoint]
reversed_domain = np.concatenate((negative_frequencies[::-1], positive_frequencies[::-1]))
decoded_audio = ifft(reversed_domain).real

# Plot the frequency domain magnitude of the encoded and decoded signals
frequency_bins = np.arange(len(encoded_audio))
frequency_bins = frequency_bins * sample_rate / len(encoded_audio)
plt.figure(figsize=(12, 4))
plt.subplot(1, 2, 1)
plt.plot(frequency_bins, np.abs(frequency_domain))
plt.title('Frequency Domain Magnitude (Encoded)')
plt.xlabel('Frequency')
plt.ylabel('Magnitude')
plt.subplot(1, 2, 2)
plt.plot(frequency_bins, np.abs(reversed_domain))
plt.title('Frequency Domain Magnitude (Decoded)')
plt.xlabel('Frequency')
plt.ylabel('Magnitude')
plt.tight_layout()
plt.show()

# Plot the time domain signals of the encoded and decoded audio
time = np.arange(len(encoded_audio)) / sample_rate
plt.figure(figsize=(12, 4))
plt.subplot(1, 2, 1)
plt.plot(time, encoded_audio)
plt.title('Encoded Audio (Time Domain)')
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.subplot(1, 2, 2)
plt.plot(time, decoded_audio)
plt.title('Decoded Audio (Time Domain)')
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.tight_layout()
plt.show()

# Listen to the decoded audio message
# Write the decoded audio to a file
wavfile.write('decoded.wav', sample_rate, np.int16(decoded_audio))

print("Decoding complete! Decoded audio saved as 'decoded.wav'.")

