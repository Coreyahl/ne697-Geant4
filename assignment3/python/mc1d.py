import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as plt
#
run1 = np.genfromtxt('hits_run1.csv',delimiter=',',skip_header=0,skip_footer=0)
#run2 = np.genfromtxt('hits_run2.csv',delimiter=',',skip_header=0,skip_footer=0)
#run3 = np.genfromtxt('hits_run3.csv',delimiter=',',skip_header=0,skip_footer=0)
#
plt.figure()
plt.hist(run1,density=True)
plt.xlabel('Tracklength', fontsize=12)
plt.ylabel('Number of Absorptions', fontsize=12)
#plt.xlim(0,1000)
#plt.ylim(0,20)
#plt.legend((plt1),('Trap 1'),fontsize=10)
plt.tight_layout()
plt.savefig('run1.png')
plt.show()
plt.close()