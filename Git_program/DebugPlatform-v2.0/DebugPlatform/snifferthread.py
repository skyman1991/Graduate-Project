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
        self.thread_stop = False
        self.port = port
        self.baud = baud
        self.uart= serial.Serial(port = self.port,baudrate = self.baud)
        self.statusbar = rootframe
        self.showdata = rootframe
        self.stopcar = rootframe
        self.root = rootframe
        self.menu = rootframe.rootmenu
        self.app = self.root.appFrame
        self.carstoproot = self.menu.carstoproot
        self.data=[]
        self.datatoshow=''
        self.filename = filename
        self.file = open(self.filename,'w')
        self.radiovalue = self.app.radiovalue.get()
        self.currenttab = 0
        self.dataintext = ""
        self.dataintextbuf=""
        self.datatype = 0
        
    
    def openuart(self):
        self.uart= serial.Serial(port = self.port,baudrate = self.baud) 
           
    def closefile(self):
        self.file.close()
            
    def openfile(self):
        self.file = open(self.filename,'w')
    
    def beacon(self):
        return "Beacon: 应答:" + str((self.data[1]&0x02)>>1) + \
            "  能耗:" + str(self.data[1]&0x01)+\
            "  目的簇ID:" + str(self.data[2])+\
            "  目的编号:"+str(self.data[3])+\
            '  簇ID:'+str(self.data[4]) + \
            '  编号；'+str(self.data[5]) + \
            '  空闲负载:'+str(self.data[6])+\
            "  RSSI:"+str(self.data[12])
            
    def JoinRequest(self):
        return "JoinRQ: 应答:" + str((self.data[1]&0x02)>>1)+\
             "  目的簇ID:" + str(self.data[2]) + \
             "  目的编号:" + str(self.data[3]) + \
             "  物理地址:" + str(self.data[4]) + str(self.data[5])
           
    def JoinRequestACK(self):
        return "JoinRQACK:应答:"+ str((self.data[1]&0x02)>>1) + \
            "  接受:"+str(self.data[1]&0x01) +\
            "  目的地址:" + str(self.data[2]) + str(self.data[3]) + \
            "  源簇ID:"+str(self.data[4])+\
            "  源编号:"+str(self.data[5])+\
            "  分配簇ID:"+str(self.data[6])+\
            "  分配编号:" + str(self.data[7])
    
    def JoinRequestACKOK(self):
        return "JoinRQACKOK:应答:" + str((self.data[1]&0x02)>>1)+\
            "  目的簇ID:"+str(self.data[2])+\
            "  目的编号:"+str(self.data[3])+\
            "  源簇ID:" + str(self.data[4])+\
            "  源编号:"+str(self.data[5])
                 
    def Data(self):
        return "Data: 应答:" + str((self.data[1]&0x02)>>1)+\
            "  目的簇ID:"+str(self.data[2])+\
            "  目的编号:"+str(self.data[3])+\
            "  源簇ID:" + str(self.data[4])+\
            "  源编号:"+str(self.data[5])+\
            "  绝对时隙号:"+str(self.data[6]<<8|self.data[7])+\
            "  数据:"+str(self.data[8])
            
    def DataACK(self):
        return "DataACK: 应答:" + str((self.data[1]&0x02)>>1)+\
            "  目的簇ID:"+str(self.data[2])+\
            "  目的编号:"+str(self.data[3])+\
            "  源簇ID:" + str(self.data[4])+\
            "  源编号:"+str(self.data[5])+\
            "  时间戳:"+str(self.data[6]<<8|self.data[7])
            
    def unpack(self):
        type = (self.data[1]&0xFC)>>2
        if type == 1:
            self.datatype = 1
            return self.beacon()
        elif type == 2:
            self.datatype = 2
            return self.JoinRequest()
        elif type == 3:
            self.datatype = 3
            return self.JoinRequestACK()
        elif type == 4:
            self.datatype = 4
            return self.JoinRequestACKOK()
        elif type == 5:
            self.datatype = 5
            return self.Data()
        elif type == 6:
            self.datatype = 6
            return self.DataACK()
        else:
            return 'unkonw type:'+str(self.data)
    
    def run(self):
        self.count = 0         
        while(1): 
            while(self.thread_stop == False):
#                 try:
#                     self.currenttab = self.root.appFrame.index('current')
#                 except TclError:
#                     print "3"+error
#                     self.currenttab = 2
#                 print type(self.root.appFrame.index('current'))
#                 if self.root.appFrame.index('current')==type(3):
#                     self.currenttab = self.root.appFrame.index('current')
                if self.currenttab == 1:
                    buf = self.uart.read(1)
                    if len(buf)!= 0:
                        if ord(buf)==0x7D:
                            buf = self.uart.read(1)
                            if len(buf)!= 0:
                                if ord(buf)==0x7E:
                                    buf = self.uart.read(13)
                                    self.data=[]
                                    self.count+=1
                                    for v in buf:
                                        self.data.append(ord(v))
                                    self.statusbar.status.setdata('RX:%s Count:%s',self.data,self.count) 
                                    self.radiovalue = self.app.radiovalue.get()
                                    self.unpack()
                                    
                if self.currenttab == 2:
#                     self.uart.write("type:beacon,freenum:16")
                    buf = self.uart.read(1)
                    if len(buf)!= 0:
                        if ord(buf)==0x7D:
                            buf = self.uart.read(1)
                            if len(buf)!= 0:
                                if ord(buf)==0x7E:
                                    buf = self.uart.read(13)

                                    self.data=[]
                                    self.count+=1
                                    for v in buf:
                                        self.data.append(ord(v))
                                    self.statusbar.status.setdata('RX:%s Count:%s',self.data,self.count) 
                                    self.radiovalue = self.app.radiovalue.get()
                                    if self.radiovalue  == 0:
#                                         try:
#                                             self.showdata.appFrame.updatetext(str(count)+"--"+self.unpack()+"\n")
#                                         except:
#                                             print "update error"
                                        self.dataintext = self.unpack()
                                        self.dataintextbuf=str(self.count)+"--"+self.dataintext+"\n"+self.dataintextbuf
#                                         print str(self.count)+"--"+self.dataintext
                                        self.file.write(self.dataintext+"\n")
                                        self.file.write('RX:%s Count:%s\n' % (self.data,self.count))
                                        if self.count%1000==0:
                                            self.showdata.appFrame.cleartext()
                                    else:
                                        try:
                                            self.file.write(self.dataintext+"\n")
                                            self.file.write('RX:%s Count:%s\n' % (self.data,self.count))
                                        except:
                                            print "4"
   
    def updatetext(self):
        while(1):
            if self.currenttab == 2:
                self.showdata.appFrame.updatetext(self.dataintextbuf,self.datatype)
                self.dataintextbuf=""
            time.sleep(0.5)
                            
                            
                            
                            

                
        
        