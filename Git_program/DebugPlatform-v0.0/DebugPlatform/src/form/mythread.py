# coding=utf-8
import time
import threading
import serial
import os 
import tkMessageBox as tkmes
import urllib2 
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
        self.stopcar = rootframe
        self.menu = rootframe.rootmenu
        self.carstoproot = self.menu.carstop
        
        self.count = 0
        self.filename = filename
        
        
        self.file = open(self.filename,'w')
        self.radiovalue = 0
        self.netreceive = threading.Thread(target = self.netupdate)
        self.netreceive.setDaemon(True)
        self.threadstartflag = 0
        self.content={}
         
        
    def run(self):                   
        print "thread " + self.name
        currenttab = 1
        fastmodecount = 0
        fastmodedatabuf=''
        datatoshow=''
        a=0
        while(1):
            while(self.thread_stop == False):
                self.count = self.count + 1
                '''暂时测试用'''
#                 databuf = self.uart.read(self.uart.inWaiting())
                databuf = self.uart.read(8);
                datatoshow=''
                for i in databuf:
                    a+=1
                    if(a%2==1):
                        datatoshow =  datatoshow+str(ord(i))+"|"
                    else:
                        datatoshow =  datatoshow+str(ord(i))+","
                
                '''datatoshow暂时测试用'''
                showbuf = 'RX:'+ datatoshow[:-1] + "    count:" + str(self.count)
                
                self.statusbar.status.setdata('%s',showbuf)
                try:
                    currenttab = self.showdata.appFrame.index('current')
                except:
                    pass

#                 print self.showdata.appFrame.tabs()
                self.radiovalue  = self.showdata.appFrame.radiovalue.get()
                if(currenttab == 2):
#                   低速模式
                    if self.radiovalue  == 0:  
                        '''datatoshow暂时测试用'''
                        self.showdata.appFrame.updatetext(datatoshow[:-1]+"\n")
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
                elif currenttab==0:
                    if self.stopcar.appFrame.carnum==0:
                        self.statusbar.status.setstatus('%s',"未配置停车个数")
                    else:
                        if self.carstoproot.datamode == 0:
                            self.stopcar.appFrame.stopcar(datatoshow[:-1])
                            self.statusbar.status.setstatus('%s',"串口数据")
                        else:
                            if self.threadstartflag == 0:
                                self.threadstartflag = 1
                                self.netreceive.start()
                            comtent=self.content
                            try:
                                databuf=''
                                if comtent['err_code'] == 0: 
                                    for items in comtent['data']:
                                        databuf = databuf+str(items['name']+'|'+items['value']+',')   
                                    self.stopcar.appFrame.stopcar(databuf[:-1])  
                                     
                                    self.statusbar.status.setstatus('%s',"网络数据:"+databuf[:-1])
                                else:
                                    self.statusbar.status.setstatus('%s',"数据返回错误")
                            except:
                                pass
                    

                    if self.carstoproot.updatamode == 0:
                        urllib2.urlopen("http://123.57.11.98:8080/mm/set_new?data="+datatoshow[:-1])
                        urllib2.urlopen("http://123.57.11.98:8080/mm/set?data=" + datatoshow[:-1])
                    time.sleep(0.05)
                else:
                    time.sleep(0.05)
                
    def closeuart(self):
        self.uart.close()
        
    def clsoefile(self):
        self.file.close()
        
    def openfile(self):
        self.file = open(self.filename,'w')
    
    def netupdate(self):
        while(1):
            response=urllib2.urlopen("http://123.57.11.98:8080/mm/get_new")
            content=eval(response.read())
            self.content = content
            time.sleep(1)




