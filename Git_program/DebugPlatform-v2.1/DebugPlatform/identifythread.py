# coding=utf-8
import threading
import serial
import time
class myThread (threading.Thread):   
    def __init__(self, threadID, name, port, baud,rootframe):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.root = rootframe
        self.app = self.root.appFrame
        self.currenttab = 0
        self.thread_stop = True
        
    def run(self):
        count = 0
        self.app.identifyuartopen = 1
        while(1):
            while(self.thread_stop == False):
                if self.currenttab == 3:
                    time.sleep(0.5)
                    count+=1
                    print count