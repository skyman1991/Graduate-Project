#coding=utf-8
import Tkinter as tk
import ttk
import uart
import serial


class MainRoot(tk.Tk):
    """Container for all frames within the application"""
    
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        
        #initialize menu
        self.config(menu=MenuBar(self))
        self.title("小虾米")

        #居中显示
        self.update() # update window ,must do
        curWidth = self.winfo_screenwidth() # get current width
        curHeight = self.winfo_screenheight() # get current height
        scnWidth = (curWidth-1280)/2
        scnHeight = (curHeight-768)/2 # get screen width and height
        # now generate configuration information
        tmpcnf = '%dx%d+%d+%d'%(1280,768,scnWidth,scnHeight)
        self.geometry(tmpcnf)

        self.appFrame = Application(self)
        self.appFrame.pack(side='top', fill='both', expand='True')
    def ShowData(self):
        self.appFrame.ShowData() 
         
    def NetStatus(self):
        self.appFrame.NetStatus()
        
    def StopStatus(self):
        self.appFrame.StopStatus()
    
    def NetSniffer(self):
        self.appFrame.NetSniffer()
        
    def SysStatus(self):
        self.status = StatusBar(self)
        self.status.pack(side='bottom', fill='x')
        
class MenuBar(tk.Menu):
    portlistsort=[]
    def __init__(self, parent):
        tk.Menu.__init__(self, parent)

        filemenu = tk.Menu(self, tearoff=False)
        self.add_cascade(label="选项",underline=0, menu=filemenu)
        filemenu.add_command(label="串口配置...", command=self.Uartettings)
#         filemenu.add_separator()
        filemenu.add_command(label="退出", underline=1, command=self.quit)

        helpmenu = tk.Menu(self, tearoff=False)
        self.add_cascade(label="帮助", menu=helpmenu)
        helpmenu.add_command(label="完善中", command=self.callback)

    def callback(self):
        print "called the callback!"
    
    def Uartettings(self):
        self.portlistsort=[]
        uartportlist = uart.GetSerialPorts()
        uartportlist.enumerate_serial_ports()
        for portnum in range(len(uartportlist.portList)):
            self.portlistsort.append(str(uartportlist.portList[portnum][1]))
        self.portlistsort=sorted(self.portlistsort)
        self.uartform = UartRoot(self.portlistsort)
        self.uartform.protocol("WM_DELETE_WINDOW", self.shutdown_ttk_repeat)  #防止退出报错
        self.uartform.mainloop()
    
    #防止退出报错
    def shutdown_ttk_repeat(self):
        self.uartform.eval('::ttk::CancelRepeat')
        self.uartform.destroy()


class StatusBar(ttk.Frame):

    def __init__(self, master):
        ttk.Frame.__init__(self, master)
        self.label = ttk.Label(self, relief='sunken', anchor='w')
        self.label.pack(fill='x')

    def set(self, format, *args):
        self.label.config(text=format % args)
        self.label.update_idletasks()

    def clear(self):
        self.label.config(text="")
        self.label.update_idletasks()

class Application(ttk.Notebook):
    def __init__(self, root):
        ttk.Notebook.__init__(self, root)
        
        self.tab1 = ttk.Frame(self)
        self.tab2 = ttk.Frame(self)
        self.tab3 = ttk.Frame(self)
        self.tab4 = ttk.Frame(self)
         
        self.add(self.tab1, text = "停车状态")
        self.add(self.tab2, text = "网络拓扑")
        self.add(self.tab3, text = "数据显示")
        self.add(self.tab4, text = "网络抓包")
    def StopStatus(self):
        label1 = ttk.Label(self.tab1,text="停车状态").grid()
    
    def NetStatus(self):
        label2 = ttk.Label(self.tab2,text="网络拓扑").grid()
    
    def ShowData(self):
        
        self.tab3.rowconfigure(0, weight=4)
        self.tab3.rowconfigure(1, weight=1)
        self.tab3.columnconfigure(0, weight=1)
        self.tab3.columnconfigure(1, weight=1)
        self.tab3.columnconfigure(2, weight=1)
        self.tab3.columnconfigure(3, weight=1)
#         接收frame        
        receivegroup = tk.LabelFrame(self.tab3, text="接收区")
        receivegroup.grid(row=0, column=0,columnspan =2,sticky=tk.N+tk.S+tk.E+tk.W)
#         停止键
        stopbutton = ttk.Button(self.tab3, text='暂停')
        stopbutton.grid(row=1,column=1,sticky = tk.W)
#         继续键
        runbutton = ttk.Button(self.tab3, text='继续')
        runbutton.grid(row=1,column=0,sticky = tk.E)
#         接收显示区
        receivegroup.rowconfigure(0, weight=1)
        receivegroup.columnconfigure(0, weight=1)
        receivebuf = tk.Entry(self.tab3)
        receivebuf.grid(row=1,column=2,sticky=tk.E)
        receivelb = tk.Listbox(receivegroup)
        receivelb.grid(row=0, column=0,sticky=tk.N+tk.S+tk.E+tk.W)
#         发送Frame
        sendgroup = tk.LabelFrame(self.tab3, text="发送区")
        sendgroup.grid(row=0, column=2,columnspan =2,sticky=tk.N+tk.S+tk.E+tk.W)
#         发送键
        sendbutton = ttk.Button(self.tab3, text='发送')
        sendbutton.grid(row=1,column=3,sticky=tk.W)
#         发送输入框
        sendgroup.rowconfigure(0, weight=1)
        sendgroup.columnconfigure(0, weight=1)
        inputbuf = tk.Entry(self.tab3)
        inputbuf.grid(row=1,column=2,sticky=tk.E)
#         发送显示区
        inputlb = tk.Listbox(sendgroup)
        inputlb.grid(row=0, column=0,sticky=tk.N+tk.S+tk.E+tk.W)

    def NetSniffer(self):
        label4 = ttk.Label(self.tab4,text="网络抓包").grid()
    
    def SendData(self):
        pass
opened_uart=[]
class UartRoot(tk.Tk):
    """Container for all frames within the application"""
    newuart = serial.Serial()
    errtext='没有错'
    def __init__(self,comnum, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        self.title("串口配置")
        self.geometry('200x400')
        ttk.Label(self, text="串口号:", padding=5).grid(row=0)
        self.comnumbox = ttk.Combobox(self, width=10,exportselection=0)
        self.comnumbox.bind("<<ComboboxSelected>>", self.IsOpen)
#         comnum.append('com2')
        self.comnumbox['value'] = comnum
        if len(comnum)>0:
            self.comnumbox.set(comnum[0])
        else:
            self.comnumbox.set('未发现串口')
        self.comnumbox.grid(row=0, column=1)
        
        ttk.Label(self, text="波特率:", padding=5).grid(row=1)
        bordrate = ['9600', '14400', '19200', '28800', '38400', '56000', '57600', '115200']
        self.bordratebox = ttk.Combobox(self, width=10)
        self.bordratebox['value'] = bordrate
        self.bordratebox.set('115200')
        self.bordratebox.grid(row=1, column=1)
        
        ttk.Label(self, text="数据位:", padding=5).grid(row=2)
        databit = ['8bit', '7bit']
        self.databitbox = ttk.Combobox(self, width=10)
        self.databitbox['value'] = databit
        self.databitbox.set('8bit')
        self.databitbox.grid(row=2, column=1)
        
        ttk.Label(self, text="停止位:", padding=5).grid(row=3)
        stopbit = ['1bit', '2bit']
        self.stopbitbox = ttk.Combobox(self, width=10)
        self.stopbitbox['value'] = stopbit
        self.stopbitbox.set('1bit')
        self.stopbitbox.grid(row=3, column=1)
        
        
#         s = ttk.Style()
#         s.configure('TButton',
# #         background='black',
# #         foreground='white',
#         highlightthickness='10',
#         font=('黑体', 14))
#         s.map('TButton',
#         foreground=[('disabled', 'yellow'),('pressed', 'red'), ('active', 'blue')],
#         background=[('disabled', 'magenta'),('pressed', '!focus', 'cyan'),('active', 'green')],
#         highlightcolor=[('focus', 'green'),('!focus', 'red')],
#         relief=[('pressed', 'groove'),('!pressed', 'ridge')]
#         )
        
        uartopenbutton = ttk.Button(self, text='打开串口', command=self.OpenUart)
        uartopenbutton.grid(row=4, column=1)
        uartclosebutton = ttk.Button(self, text='关闭串口', command=self.CloseUart)
        uartclosebutton.grid(row=5, column=1)

        
        self.uartstatus = tk.Canvas(self,width=20,height=20,background='black')
        self.statusrec = self.uartstatus.create_rectangle(0,0,20,20,fill='red')      
        self.uartstatus.grid(row = 5,column=0)
        self.IsOpen(0)
    
    def OpenUart(self):
#         mainform.root.status.set("%s",'sdf')

        try:
            self.newuart.port = self.comnumbox.get()
            self.newuart.baudrate = self.bordratebox.get()
            self.newuart.open()
            opened_uart.append(self.comnumbox.get())
            self.IsOpen(0)
        except serial.SerialException,error:
            self.errtext = str(error)
            text = tk.Label(self,text = "串口被占用！")
            text.grid(row=7,column=1)
            print str(error)

    def CloseUart(self):
        self.newuart.close()
        opened_uart.remove(self.comnumbox.get())
        self.IsOpen(0)
        
    def IsOpen(self,event):
        comnunm=self.comnumbox.get()
        if comnunm in opened_uart:
            self.uartstatus.itemconfig(self.statusrec, fill='green')
        else:
            self.uartstatus.itemconfig(self.statusrec, fill='red')

if __name__ == '__main__':
    root = MainRoot()
    root.ShowData()    #数据显示
    root.NetStatus()   #网络状态
    root.StopStatus()  #停车状态
    root.NetSniffer()  #网络抓包
    root.SysStatus()   #状态栏

    root.mainloop()
    
