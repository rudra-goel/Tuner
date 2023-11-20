import numpy as np

# Input signal
x = np.array([3, 1, 2, 4])

# Apply FFT
X = np.fft.fft(x)

# Frequency domain representation (complex values)
print("Frequency domain representation:")
print(X)

# Magnitude of the frequency components
magnitude = np.abs(X)
print("\nMagnitude of frequency components:")
print(magnitude)

# Phase of the frequency components
phase = np.angle(X)
print("\nPhase of frequency components:")
print(phase)
