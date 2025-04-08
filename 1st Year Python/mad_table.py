'''import matplotlib as plt
import numpy as np

def MAD(key):
    return (13*key+5)%23%20

keys=41, 28, 11, 82, 40, 75, 21, 0,  90, 52, 96, 70, 83, 98, 1, 43, 4, 85, 79, 87.

def plot(function,keys,N):
    
    indices=[function(key,N) for key in keys]
    print(indices)
    # Create histogram
    plt.hist(indices, bins=np.arange(0, N+1.5)-0.5, edgecolor='black')

    # Set x-axis label
    plt.xlabel('Hash Value')
    # Set y-axis label
    plt.ylabel('Frequency')
    # Set plot title
    plt.title('Histogram')

    # Display plot
    plt.show()
plot(MAD,keys,20)'''
