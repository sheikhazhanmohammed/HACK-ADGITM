# -*- coding: utf-8 -*-
"""
Created on Wed Oct  9 20:57:32 2019

@author: 91935
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data=pd.read_excel("C:\\Users\\91935\\Desktop\\HealthWatch.xlsx")
print(data.head())
x=data.BPM
col_mean = np.nanmean(x, axis = 0)
x = x.replace(0, np.nan)
res = np.where(np.isnan(x), np.ma.array(x, 
               mask = np.isnan(x)).mean(axis = 0), x)

plt.plot(res, color="green", linestyle='dashed')
plt.ylabel("Pulse Count")
plt.xlabel("Time")
data=data.rename(columns={"Alcohol Value": "AlVal", "Smoke Sensor": "SmSen"," Temperature":"Temp"})
y=data.SmSen
z=data.AlVal
a=data.Temp
y_mean=y.mean()  
"""Mean of Smoke Value"""
z_mean=z.mean()  
"""Mean of Alcohol Value"""
a_mean=a.mean()  
"""Mean of Temperature"""
x_mean=x.mean()  
"""Mean of BPM"""

if y_mean>=275 and x_mean<=65:
    print("The Air Quality is very low, please move to a safer area")
if z_mean>=250 and x_mean>=80:
    print("You have been drinking quite a lot of alcohol, please stop")
elif z_mean>=300 and x_mean>=80:
    print("You are no longer safe to drive a vehicle")
if x_mean<=60 and a_mean>=38:
    print("Your blood pressure is increasing, you should take a break and drink some water")
if x_mean>=80 and a_mean<=34:
    print("Blood pressure if falling below safe limit, take a break")







