#!/usr/bin/env python

import matplotlib.pyplot as plt

probs = [ .1, 0.2, 0.1, 0.1, 0.3, 0.2]
plt.title("Biased dice")
plt.bar(range(1,7),probs)
plt.xlabel("Dice face")
plt.ylabel("Probability of occurrence")
plt.savefig("discrete_distribution.pdf")

