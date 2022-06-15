import random
import numpy as np
import math
import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
#num_str = input("enter the numebr of aircrafts: ")
print("enter the numebr of planes")
num = input()
num = int(num)
#print("there are",num,"planes")
length_airspace = 1000
width_airspace = 1000
height_airspace = 11
length_unit = 20
width_unit = 20
height_unit = 1
min_speed = 150
max_speed = 250

aircraft_length = []
aircraft_width = []
aircraft_height = []

aircraft_dir_x = []
aircraft_dir_y = []
aircraft_dir_z = []
aircraft_speed = []
danger_x = []
danger_y = []
initial_x = 0
initial_y = 0
initial_z = 7
x = 0
while x < num:
    aircraft_length.append(random.randint(0,length_airspace))
    aircraft_width.append(random.randint(0,width_airspace))
    aircraft_height.append(random.randint(initial_z,height_airspace))
    aircraft_speed.append(random.randint(min_speed,max_speed))
    aircraft_dir_x.append(random.randint(0-length_airspace,length_airspace))
    aircraft_dir_y.append(random.randint(0-width_airspace,width_airspace))
    aircraft_dir_z.append(random.randint(0,height_airspace))
    x=x+1
x = initial_x
y = initial_y
z = initial_z
planecount = 0
num_x = int(length_airspace/length_unit)
num_y = int(width_airspace/width_unit)
num_z = int((height_airspace-initial_z)/height_unit)
unitblock = [[[[0] for i in range (num_z)]for j in range(num_y)]for k in range (num_x)]


totaltime = 0
# fig,ax = plt.subplots()
# ax.set_xticks(np.arange(0,length_airspace+length_unit,length_unit), minor=False)
# ax.set_yticks(np.arange(0,width_airspace+width_unit,width_unit), minor=False)
# plt.grid(color='r', linestyle='-', linewidth=0.1)
for k in range (100):                                                          #total frame number
    starttime = time.time()                      
    #print("k is %s" %k)  
    danger_x = []
    danger_y = []   
    collisioncount = 0
    num_x = int(length_airspace/length_unit)
    num_y = int(width_airspace/width_unit)
    num_z = int((height_airspace-initial_z)/height_unit)
    unitblock.clear()
    unitblock = [[[[0] for i in range (num_z)]for j in range(num_y)]for k in range (num_x)]
    
    for i in range (planecount):                                            #update plane position
        if aircraft_length[i] != 0 and aircraft_width != 0:
            aircraft_length[i] = aircraft_length[i]+aircraft_dir_x[i]*0.001
            aircraft_width[i] = aircraft_width[i]+aircraft_dir_y[i]*0.001
  
    planecount = 0
    while planecount < num:                                             #check collision
        if aircraft_length[planecount] > length_airspace or aircraft_length[planecount] < 0 or aircraft_width[planecount] > width_airspace or aircraft_width[planecount] < 0:
            aircraft_length[planecount] = 0
            aircraft_width[planecount] = 0
        else:
            tem_x = int(aircraft_length[planecount] // length_unit)
            tem_y = int(aircraft_width[planecount] // width_unit)
            tem_z = int((aircraft_height[planecount] - initial_z) // height_unit)
            unitblock[tem_x-1][tem_y-1][tem_z-1].append(planecount)
            if len(unitblock[tem_x-1][tem_y-1][tem_z-1]) > 2:
                repeat = len(unitblock[tem_x-1][tem_y-1][tem_z-1])
                for i in range (repeat-2):
                        compareplane = unitblock[tem_x-1][tem_y-1][tem_z-1][i+1]
                        dis1 = math.sqrt((aircraft_length[compareplane]-aircraft_length[planecount])**2 + (aircraft_width[compareplane]-aircraft_width[planecount])**2 + (aircraft_height[compareplane]-aircraft_height[planecount])**2)
                        moved1_x = aircraft_length[planecount]+aircraft_dir_x[planecount]*0.001
                        moved1_y = aircraft_width[planecount]+aircraft_dir_y[planecount]*0.001
                        moved1_z = aircraft_height[planecount]+aircraft_dir_z[planecount]*0.001
                        moved2_x = aircraft_length[compareplane]+aircraft_dir_x[compareplane]*0.001
                        moved2_y = aircraft_width[compareplane]+aircraft_dir_y[compareplane]*0.001
                        moved2_z = aircraft_height[compareplane]+aircraft_dir_z[compareplane]*0.001
                        dis2 = math.sqrt((moved1_x-moved2_x)**2 +(moved1_y-moved2_y)**2+(moved1_z-moved2_z)**2)
                        if dis1 > dis2:
                            danger_x.append(aircraft_length[planecount])
                            danger_x.append(aircraft_length[compareplane])
                            danger_y.append(aircraft_width[planecount])
                            danger_y.append(aircraft_width[compareplane])
                            collisioncount+=1
        planecount+=1
    print("number of collision %s" %collisioncount)
    collisioncount = 0
    #print("time used %f" %(time.time()-starttime))
    totaltime+=(time.time()-starttime)
print("average caluculation time is %s" %(totaltime/100))
print("press any key and enter to end")
k = input()
    # plt.xlim((0,1000))
    # plt.ylim((0,1000))z``
    # plt.scatter(aircraft_length, aircraft_width, color= "blue",marker= ".", s=1)
    # plt.scatter(danger_x, danger_y, color= "red",marker= ".", s=3)
    # # if k != 0:
    # #     fig.canvas.draw()
    # # else:
    # #     plt.show()
    # fig.canvas.draw()
    # plt.pause(0.2)                                                             #number of time per frame
    # #plt.cla()
    # ax.set_xticks(np.arange(0,length_airspace+length_unit,length_unit), minor=False)
    # ax.set_yticks(np.arange(0,width_airspace+width_unit,width_unit), minor=False)
    # plt.grid(color='r', linestyle='-', linewidth=0.1)
 


    
   