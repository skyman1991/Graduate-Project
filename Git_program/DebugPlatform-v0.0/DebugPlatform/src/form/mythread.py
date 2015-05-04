# coding=utf-8
import time
import threading
import serial
import os 
class myThread (threading.Thread):   
    
    def __init__(self, threadID, name, port, baud,rootframe,filename):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.thread_stop = True
        self.port = port
        self.baud = baud
        self.uart= serial.Serial(port = self.port,baudrate = self.baud)
        self.statusbar = rootframe
        self.showdata = rootframe
        self.count = 0
        self.filename = filename
        
        
        self.file = open(self.filename,'w')
        self.radiovalue = 0
        
        
    def run(self):                   
        print "thread " + self.name
        currenttab = 2
        fastmodecount = 0
        fastmodedatabuf=''
        while(1):
            while(self.thread_stop == False):
                self.count = self.count + 1
                self.uart.write("hello this is my fisrt uart")
                databuf = self.uart.read(self.uart.inWaiting())
                showbuf = 'RX:'+ databuf + "    count:" + str(self.count)
                
                self.statusbar.status.setdata('%s',showbuf)
                try:
                    currenttab = self.showdata.appFrame.index('current')
                except:
                    currenttab = 2

#                 print self.showdata.appFrame.tabs()
                self.radiovalue  = self.showdata.appFrame.radiovalue.get()
                if(currenttab == 2):
#                   低速模式
                    if self.radiovalue  == 0:  
                        self.showdata.appFrame.updatetext(databuf+"\n")
                        try:
                            self.file.write(showbuf+'\n')
                        except:
                            pass
                        time.sleep(0.05)
                        
#                   高速模式      
                    elif self.radiovalue  == 1:
                        try:
                            self.file.write(showbuf+'\n')
                        except:
                            pass
                        fastmodecount = fastmodecount + 1
                        if(fastmodecount == 200):
                            fastmodecount = 0
                            print len(fastmodedatabuf)
#                             self.showdata.appFrame.updatetext(fastmodedatabuf)
                            fastmodedatabuf = ''
                        else:
                            fastmodedatabuf = fastmodedatabuf + databuf +"\n"
                            
                        time.sleep(0.005)
                else:
                    time.sleep(0.05)
                
    def closeuart(self):
        self.uart.close()
        
    def clsoefile(self):
        self.file.close()
        
    def openfile(self):
        self.file = open(self.filename,'w')
    



