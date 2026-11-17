# 535-Takehome3
TakeHome3 is trying to simulate a traffic controller and proccesing that data through a queue accepting info from multiple sources 
Currently there are two issues.


There is an issue with the queue that after I enqueue the data from the traffic text file it does not output it. What happened was this error is new I was trying to reduce the amount of data structures. I originally
Had two of the trafficPthread struct but this is bad coding practice so I moved it into a header file and am now using it but its leading to some error I will fix this eventually just need to find the bug. 

The main logic issue I have been having is when I get the data from the traffic controller and queue it I have a queue full of trafficPthreadobjects. Some logic questions are how do I process if I do not know the amount
of traffic controllers, lets say I want to split the task up I need to know the amount of traffic Ids to split the task per traffic ID. This seems to be the only way to split it but this information wouldn't be knowen in a real world situation. Then when trying to process each hour how do I store and compare the results for each hour efficiently and not have the subsequent hour over right the result. my solution to this is to make a vector that is numbered 1-9 (to represent the 9 traffic ids which I arbitrarly assigned first with 9). Currently it adds up the amount of cars per hour and then every hour it adds the hourly result onto a hourly results vector. This method seems inefficient and relies on there being 9 traffic ids. Any help with this would be appreciated.
