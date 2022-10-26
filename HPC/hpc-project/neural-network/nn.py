import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

X = [1, 0.7, 1.2]
W = [[0.5, 1.5, 0.8, 0.9, -1.7, 1.6], [0.8, 0.2, -1.6, 1.2, 2.1, -0.2]]
true = [1, 0]

loss = []


def mse( y, y_pred ):  
    y = np.array(y) 
    y_pred = np.array(y_pred)   
    return  np.sum((y-y_pred)**2)/np.size(y)

for iter in range(100):
    layer1 = [1]

    for j in range(len(W)):
        sum = 0
        # for k in range(int(len(W[j])/2)):
        for i in range(len(X)):
            prod = X[i]*W[j][i]
            # print(str(X[i])+"---------"+str(W[j][i]))
            sum = sum + prod
            z = 1/(1 + np.exp(-sum))
        layer1.append(z)


    layer2 = []

    for j in range(len(W)):
        sum = 0
        # for k in range(int(len(W[j])/2)):
        for i in range(len(layer1)):
            prod = layer1[i]*W[j][3+i]
            # print(str(layer1[i])+"---------"+str(W[j][3+i]))
            sum = sum + prod
        z = 1/(1 + np.exp(-sum))
        layer2.append(z)

    del12 = (layer2[0]-true[0])*layer2[0]*(1-layer2[0])
    del22 = (layer2[1]-true[1])*layer2[1]*(1-layer2[1])

    del11 = layer1[1]*(1-layer1[1])*((del12*W[0][3+1])+(del22*W[1][3+1]))
    del21 = layer1[2]*(1-layer1[2])*((del12*W[0][3+2])+(del22*W[1][3+2]))

    delta = [[del11, del21], [del12, del22]]
    #WEIGHT UPDATION:
    # W = [[0.5, 1.5, 0.8, 0.9, -1.7, 1.6], [0.8, 0.2, -1.6, 1.2, 2.1, -0.2]]
    # print("****************************************")
    for i in range(len(W)):
        for j in range(int(len(W[i])/2)):
            # print(str(X[j])+"---------"+str(delta[0][i])+"------------"+str(W[i][j]))
            W[i][j] = W[i][j] - 0.5*(delta[0][i]*X[j]) 
            
    # print("****************************************")
    for i in range(len(W)):
        for j in range(int(len(W[i])/2)):
            # print(str(layer1[j])+"---------"+str(delta[1][i])+"------------"+str(W[i][3+j]))
            W[i][3+j] = W[i][3+j] - 0.5*(delta[1][i]*layer1[j]) 

    val = mse(true,layer2)
    loss.append(val)

    print("****************************************")
    print("Weight Vector after iteration: "+str(iter+1))
    print(W)
    print("****************************************")


print(layer2)
print(loss)
plt.plot(loss)
plt.show()