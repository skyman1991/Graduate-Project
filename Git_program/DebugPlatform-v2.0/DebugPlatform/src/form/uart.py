# coding=utf-8
import _winreg as winreg
import itertools
import Tkinter as tk
import ttk
import serial
import time
import relaythread
import snifferthread

class GetSerialPorts(object):
    # list contains all port device info
    portList = []
    IterationError=''
    def enumerate_serial_ports(self):
        """ Uses the Win32 registry to return a iterator of serial 
            (COM) ports existing on this computer.
        """
        path = 'HARDWARE\\DEVICEMAP\\SERIALCOMM'
        try:
            key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, path)
        except WindowsError:
            raise self.IterationError
        self.portList=[]
        for i in itertools.count():
            try:
                val = winreg.EnumValue(key, i)
                self.portList.append(val)
            except EnvironmentError:
                break

        winreg.CloseKey(key)

    def port_list(self):
        self.portList=[]
        for x in range(len(self.portList)):
            tmp = self.portList[x]
            print tmp[0]
            print str(tmp[1])

class UartRoot(tk.Tk):
    """Container for all frames within the application"""
    
    errtext = '没有错'
    def __init__(self, comnum, frame, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)  
        self.stopbitcboxbuf='1bit'
        self.databitcboxbuf='8bit'
        self.parent = frame
        self.parent_menu = self.parent.rootmenu
        self.title("串口配置")
        self.geometry('250x400')
        ttk.Label(self, text="串口号:", padding=5).grid(row=0)
        self.comnumbox = ttk.Combobox(self, width=10, exportselection=0)
        self.comnumbox.bind("<<ComboboxSelected>>", self.IsOpen)
#         comnum.append('com2')
        self.comnumbox['value'] = comnum
        if len(comnum) > 0:
            self.comnumbox.set(comnum[0])
        else:
            self.comnumbox.set('未发现串口')
        self.comnumbox.grid(row=0, column=1)
        
        ttk.Label(self, text="波特率:", padding=5).grid(row=1)
        bordrate = ['9600', '14400', '19200', '28800', '38400', '56000', '57600', '115200']
        self.bordratecbox = ttk.Combobox(self, width=10)
        self.bordratecbox['value'] = bordrate
        self.bordratecbox.set(self.parent_menu.bordratecboxbuf)
        self.bordratecbox.grid(row=1, column=1)
        
        ttk.Label(self, text="数据位:", padding=5).grid(row=2)
        databit = ['8bit', '7bit']
        self.databitcbox = ttk.Combobox(self, width=10)
        self.databitcbox['value'] = databit
        self.databitcbox.set(self.databitcboxbuf)
        self.databitcbox.grid(row=2, column=1)
        
        ttk.Label(self, text="停止位:", padding=5).grid(row=3)
        stopbit = ['1bit', '2bit']
        self.stopbitcbox = ttk.Combobox(self, width=10)
        self.stopbitcbox['value'] = stopbit
        self.stopbitcbox.set(self.stopbitcboxbuf)
        self.stopbitcbox.grid(row=3, column=1)
        
        ttk.Label(self, text="数据源类型:", padding=5).grid(row=4)
        self.datasourcecbox = ttk.Combobox(self, width=10)
        self.datasourcecbox['value'] = ("中继","Sniffer")
        self.datasourcecbox.set(self.parent_menu.datasourcecboxbuf)
        self.datasourcecbox.grid(row=4, column=1)
        
        uartopenbutton = ttk.Button(self, text='打开串口', command=self.OpenUart)
        uartopenbutton.grid(row=5, column=1)
        uartclosebutton = ttk.Button(self, text='关闭串口', command=self.CloseUart)
        uartclosebutton.grid(row=6, column=1)

        self.uartstatus = tk.Canvas(self, width=20, height=20, background='black')
        self.statusrec = self.uartstatus.create_rectangle(0, 0, 20, 20, fill='red')      
        self.uartstatus.grid(row=6, column=0)
        self.IsOpen(0)
        self.txtfilname = "sniffer-"+time.strftime('%Y-%m-%d_%H-%M-%S', time.localtime(time.time())) + '.txt'

        
    def showupdate(self):
        self.bordratecbox.set(self.parent_menu.bordratecboxbuf)
        self.datasourcecbox.set(self.parent_menu.datasourcecboxbuf)
        self.IsOpen(0)
    
    def OpenUart(self):
#         mainform.root.status.set("%s",'sdf')
        try:
            self.parent_menu.opened_uart.append(self.comnumbox.get())
            self.IsOpen(0)
            self.parent.status.setstatus('%s', self.comnumbox.get() + '已打开')
            self.parent_menu.bordratecboxbuf = self.bordratecbox.get()
            self.parent_menu.datasourcecboxbuf = self.datasourcecbox.get()
            self.parent_menu.datasourcecboxvalue = self.datasourcecbox.current()
#             中继
            if self.datasourcecbox.current() == 0:
                self.relaythread = relaythread.myThread(rootframe=self.parent,threadID=0, name='relay', port=self.comnumbox.get(), baud=self.bordratecbox.get())
                self.relaythread.setDaemon(True)
                self.relaythread.start()
               
            else:
                self.snifferthread = snifferthread.myThread(rootframe=self.parent,threadID=1, name='sniffer', port=self.comnumbox.get(), baud=self.bordratecbox.get(),filename = self.txtfilname)
                self.snifferthread.setDaemon(True)
                self.snifferthread.start()
#                 self.uartthread.thread_stop = False
#             self.uartthread = mythread.myThread(rootframe=self.parent, filename=self.txtfilname, threadID=1, name='uart', port=self.comnumbox.get(), baud=self.bordratecbox.get())
#             self.uartthread.setDaemon(True)
#             self.uartthread.start()
            
        except serial.SerialException, error:
            self.errtext = str(error)
            text = tk.Label(self, text="串口被占用！")
            text.grid(row=7, column=1)
            print str(error)

    def CloseUart(self):
        try:
            if self.comnumbox.get() in self.parent_menu.opened_uart:
                self.parent_menu.opened_uart.remove(self.comnumbox.get())
            self.IsOpen(0)
            if self.datasourcecbox.current() == 0:
                self.relaythread.uart.close()
            else:
                self.snifferthread.thread_stop = True
                self.snifferthread.uart.close()
                
            self.parent.status.setstatus('%s', self.comnumbox.get() + '已关闭')
        except NameError:
            self.parent.status.setstatus('%s', '串口未打开')

    def IsOpen(self, event):
        comnunm = self.comnumbox.get()
        if comnunm in self.parent_menu.opened_uart:
            self.uartstatus.itemconfig(self.statusrec, fill='green')
        else:
            self.uartstatus.itemconfig(self.statusrec, fill='red')