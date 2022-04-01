#! /usr/bin/python3
# Parse the XML file and return important information
# Usage: python3 analyse.py <path to xml file>
import matplotlib.pyplot as plt
import numpy as np
import sys
import re
import csv

lst = []
with open(sys.argv[1]) as f:
    read = csv.reader(f, delimiter=",")
    for row in read:
        lst = row
for i in range(len(lst)):
    tpm = str(lst[i]).split(" ")
    lst = tpm
    lst.remove('')
for i in range(len(lst)):
    lst[i] = np.float32(lst[i])
#print(len(lst))

tpmNp = np.array(lst, dtype= np.float32)
#print(tpmNp)


axisX = [x for x in range(2, 31)]
#rint(axisX)
plt.plot(axisX, lst, 'xr')
plt.title("Visualization")
plt.xlabel("Nodes")
plt.ylabel("Client Loss Ratio")
plt.savefig(sys.argv[1].replace("csv", "pdf"))
plt.show()


