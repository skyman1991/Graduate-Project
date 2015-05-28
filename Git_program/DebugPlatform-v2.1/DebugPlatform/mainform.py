# coding=utf-8
import Tkinter as tk
import ttk
import uart
import tkMessageBox as tkmes
import os
import tkFont
import carstop
import time
import win32ui





class MainRoot(tk.Tk):
    """Container for all frames within the application"""
    
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        
        # initialize menu
        self.rootmenu = MenuBar(self)
        self.config(menu=self.rootmenu)
        self.title("小虾米")

        # 居中显示
        curWidth = self.winfo_screenwidth()  # get current width
        curHeight = self.winfo_screenheight()  # get current height
        scnWidth = (curWidth - 1330) / 2
        scnHeight = (curHeight - 660) / 2  # get screen width and height
        # now generate configuration information
        tmpcnf = '%dx%d+%d+%d' % (1330, 660, scnWidth, scnHeight)
        self.geometry(tmpcnf)
        self.appcanvas = tk.Canvas(self)
        self.appFrame = Application(root=self)
        self.appFrame.pack(side='top', fill='both', expand='True')

    def ShowData(self):
        self.appFrame.ShowData() 
         
    def NetStatus(self):
        self.appFrame.NetStatus()
        
    def StopStatus(self):
        self.appFrame.StopStatus()
    
    def NetSniffer(self):
        self.appFrame.DrawSensor()
        
    def SysStatus(self):
        self.status = StatusBar(self)
        self.status.pack(side='bottom', fill='x')
        
    def Identify(self):
        self.appFrame.Identify()
        pass
        
class MenuBar(tk.Menu):
    portlistsort = []
    def __init__(self, parent):
        tk.Menu.__init__(self, parent)
        self.carlocatecboxbuf = '方兴大厦'
        self.updatamodecboxbuf = '开启'
        self.datamodecboxbuf = "串口数据"
        self.root = parent

    def show(self):
        
        self.carstoproot = carstop.CarStopRoot(rootframe=self.root)
        filemenu = tk.Menu(self, tearoff=False)
        self.add_cascade(label="选项", underline=0, menu=filemenu)
        filemenu.add_command(label="串口设置...", command=self.Uartettings)
        filemenu.add_command(label="网络设置...", command=self.netsettings)
        filemenu.add_command(label="停车设置...", command=self.carstopsettings)
        filemenu.add_command(label="退出", underline=1, command=self.quit)
        helpmenu = tk.Menu(self, tearoff=False)
        self.add_cascade(label="帮助", menu=helpmenu)
        helpmenu.add_command(label="完善中", command=self.callback)
        self.bordratecboxbuf = '115200'
        self.datasourcecboxbuf = '识别'
        self.datasourcecboxvalue = 5
        self.opened_uart = []

    def callback(self):
        print "called the callback!"
    
    def Uartettings(self):
        self.portlistsort = []
        
        uartportlist = uart.GetSerialPorts()
        uartportlist.enumerate_serial_ports()
        for portnum in range(len(uartportlist.portList)):
            self.portlistsort.append(str(uartportlist.portList[portnum][1]))
            
        import re
        re_digits = re.compile("(\d+)")
        def emb_numbers(s):  
            pieces = re_digits.split(s)  
            pieces[1::2] = map(int, pieces[1::2])    
            return pieces  

        def sort_strings_with_emb_numbers(alist):  
            aux = [(emb_numbers(s), s) for s in alist]
            aux.sort()  
            return [s for __, s in aux]  
        self.portlistsort = sort_strings_with_emb_numbers(self.portlistsort)
        
        global root
        
        self.uartform = uart.UartRoot(comnum=self.portlistsort, frame=root)
        self.uartform.showupdate()
        self.uartform.protocol("WM_DELETE_WINDOW", self.uart_shutdown_ttk_repeat)  # 防止退出报错
        '''删掉了mainloop'''
        self.uartform.mainloop()
    
    def netsettings(self):
        pass
    
    def carstopsettings(self):
        
        self.carstoproot.show()
        self.carstoproot.showupdata()
        self.carnum = self.carstoproot.carnum
        self.carstoproot.protocol("WM_DELETE_WINDOW", self.carstop_shutdown_ttk_repeat)  # 防止退出报错
        '''删掉了mainloop'''
        self.carstoproot.mainloop()
        
    # 防止退出报错
    
    def uart_shutdown_ttk_repeat(self):
        self.uartform.eval('::ttk::CancelRepeat')
        self.uartform.destroy()
    
    def carstop_shutdown_ttk_repeat(self):
        self.carstoproot.eval('::ttk::CancelRepeat')
        self.carstoproot.destroy()

class StatusBar(ttk.Frame):

    def __init__(self, master):
        ttk.Frame.__init__(self, master)
        self.label = ttk.Label(self, relief='sunken', anchor='w')
        self.columnconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)
        self.rowconfigure(0, weight=1)
        self.label.grid(row=0, column=0, sticky=tk.W + tk.E + tk.N + tk.S)
        
        self.labelicon = ttk.Label(self, relief='sunken', anchor='w')
        self.labelicon.grid(row=0, column=1, sticky=tk.W + tk.E + tk.N + tk.S)
       
    def setstatus(self, defformat, *args):
        self.label.config(text=defformat % args)
#         self.label.update_idletasks()
    
    def setdata(self, defformat, *args):
        self.labelicon.config(text=defformat % args)

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

        self.add(self.tab1, text="停车状态")
        self.add(self.tab2, text="网络拓扑")
        self.add(self.tab3, text="数据显示")
        self.add(self.tab4, text="数据识别")
        self.topline = []
        self.bottomline = []
        self.carnum = 0
        self.width = 1320
        self.height = 600
        self.carmove = []
        self.stoptext = []
        self.loacname = []
        self.front = tkFont.Font(size=50, family="黑体")
        
        self.root = root
        self.menu = root.rootmenu
        
        
        
        self.bind("<<NotebookTabChanged>>", self.updatetab)
        self.ADValue = []
        self.rooterimage = tk.PhotoImage(file="image//rooter.gif")
        self.sensorimage = tk.PhotoImage(file="image//sensor.gif")
        self.canvasline = []  # 绘图曲线
        self.cavasverticalline = []  # 绿色竖线
        self.canvasidentifyline = []  # 识别出竖线
        self.canvasoval=[] #识别画出的圆点
        self.identifyuartopen = 0
        self.drawonceym = 0
    
    def updatetab(self, event):
        try:
            self.menu.uartform.snifferthread.currenttab = self.index('current')
            
        except:
            print "7"
        try:
            self.menu.uartform.identifythread.currenttab = self.index('current')
        except:
            print "7"
        
    def StopStatus(self):             
        self.canvas = tk.Canvas(self.tab1, width=self.width, height=self.height)
        self.canvas.grid(sticky=tk.W + tk.E)
        self.canvas.create_line(0, self.height / 2, self.width, self.height / 2, fill='black', dash=(100, 80), width=5)
        self.canvas.create_line(0, self.height / 3, self.width, self.height / 3, fill='black', width=5)
        self.canvas.create_line(0, self.height / 3 * 2, self.width, self.height / 3 * 2, fill='black', width=5)
    
    def DrawParking(self):
        global root
        self.carnum = root.rootmenu.carstoproot.carnum

        if len(self.topline) > 0:
            for line in self.topline:
                self.canvas.delete(line)
        if len(self.bottomline) > 0:
            for line in self.bottomline:
                self.canvas.delete(line)
        if len(self.stoptext) > 0:
            for text in self.stoptext:
                self.canvas.delete(text)
        if len(self.loacname) > 0:
            for text in self.loacname:
                self.canvas.delete(text)
        
        self.loacname.append(self.canvas.create_text(self.width / 2, self.height / 2, text=root.rootmenu.carlocatecboxbuf, font=tkFont.Font(size=50, family="黑体"), fill='purple'))

        if self.carnum % 2 == 0:
            topnum = self.carnum / 2
            bottomnum = self.carnum / 2
        else:
            topnum = (self.carnum + 1) / 2
            bottomnum = (self.carnum - 1) / 2
        everytopx = self.width / topnum + 1
        everybottomx = self.width / bottomnum + 1
        for i in range(1, topnum):
            self.topline.append(self.canvas.create_line(everytopx * i, 0, everytopx * i, self.height / 3, fill='black', width=5))
            
        for i in range(1, bottomnum):
            self.bottomline.append(self.canvas.create_line(everybottomx * i, self.height / 3 * 2, everybottomx * i, self.height, fill='black', width=5))
                
    def stopcar(self, move):
        count = 0
        try:
            if len(self.stoptext) > 0:
                for text in self.stoptext:
                    self.canvas.delete(text)
        except:
            print "5"
#         for i in range(self.carnum):
#             self.stoptext.append(self.canvas.create_text(0,0))
        if self.carnum > 20:
            self.front.configure(size=10)
        elif self.carnum > 14:
            self.front.configure(size=20)
        elif self.carnum > 8:
            self.front.configure(size=32)
        
        if self.carnum % 2 == 0:
            topwidth = self.width / (self.carnum / 2)
            bottomwidth = topwidth
            topnum = self.carnum / 2
#             bottomnum = topnum
        else:
            topwidth = self.width / ((self.carnum + 1) / 2)
            bottomwidth = self.width / ((self.carnum - 1) / 2)
            topnum = (self.carnum + 1) / 2
#             bottomnum = (self.carnum - 1) / 2
        buf = move.split(",")
        self.carmove = []
        for i in buf:
            self.carmove.append(i.split("|"))
        for num, act in self.carmove:
            if count < topnum:
                if act == '1':
                    self.stoptext.append(self.canvas.create_text(count * topwidth + topwidth / 2, self.height / 6, text=num + ":\n已停车", font=self.front, fill='red'))
                
                else:
                    self.stoptext.append(self.canvas.create_text(count * topwidth + topwidth / 2, self.height / 6, text=num + ":\n未停车", font=self.front, fil='green'))
            else:
                if act == '1':
                    self.stoptext.append(self.canvas.create_text((count - topnum) * bottomwidth + bottomwidth / 2, self.height - self.height / 6, text=num + ":\n已停车", font=self.front, fill='red'))
                else:
                    self.stoptext.append(self.canvas.create_text((count - topnum) * bottomwidth + bottomwidth / 2, self.height - self.height / 6, text=num + ":\n未停车", font=self.front, fill='green'))        
            count = count + 1 
        
    def NetStatus(self):
        canv = tk.Canvas(self.tab2, width=1320, height=600, bg="white")
        canv.grid()
        
        canv.create_image(1320 / 2, 50, image=self.rooterimage)
        canv.create_image(100, 400, image=self.sensorimage)
        canv.create_line(1320 / 2, 50, 100, 400, fill='green', dash=(100, 80))
        canv.create_text(100, 480, text="01")
        canv.create_image(400, 400, image=self.sensorimage)
        canv.create_line(1320 / 2, 50, 400, 400, fill='green', dash=(100, 80))
        canv.create_text(400, 480, text="02")
        canv.create_image(800, 400, image=self.sensorimage)
        canv.create_line(1320 / 2, 50, 800, 400, fill='green', dash=(100, 80))
        canv.create_text(800, 480, text="03")
        canv.create_image(1200, 400, image=self.sensorimage)
        canv.create_line(1320 / 2, 50, 1200, 400, fill='red', dash=(100, 80))
        canv.create_text(1200, 480, text="04")
        
    def ShowData(self):
        
        self.tab3.rowconfigure(0, weight=60)
        self.tab3.rowconfigure(1, weight=1)
        self.tab3.columnconfigure(0, weight=1)
        self.tab3.columnconfigure(1, weight=1)
        self.tab3.columnconfigure(2, weight=1)
        self.tab3.columnconfigure(3, weight=1)
        self.tab3.columnconfigure(4, weight=1)
#         接收frame        
        receivegroup = tk.LabelFrame(self.tab3, text="接收区")
        receivegroup.grid(row=0, column=0, columnspan=4, sticky=tk.N + tk.S + tk.E + tk.W)
#         继续键
        runbutton = ttk.Button(self.tab3, text='继续', command=self.restart)
        runbutton.grid(row=1, column=0, sticky=tk.E)
#         停止键
        stopbutton = ttk.Button(self.tab3, text='暂停', command=self.pause)
        stopbutton.grid(row=1, column=1, sticky=tk.W)
#         打开键
        openbutton = ttk.Button(self.tab3, text='打开txt数据', command=self.opentxt)
        openbutton.grid(row=1, column=2, sticky=tk.E)
#         清空键
        clearbutton = ttk.Button(self.tab3, text='清空', command=self.cleartext)
        clearbutton.grid(row=1, column=2, sticky=tk.W)
#         接收显示区
        receivegroup.rowconfigure(0, weight=1)
        receivegroup.columnconfigure(0, weight=1)
#         receivegroup.columnconfigure(1, weight=1)
        self.receivetext = tk.Text(receivegroup)
        receivesb = tk.Scrollbar(self.receivetext)
        receivesb.pack(side=tk.RIGHT, fill=tk.Y)
        receivesb.config(command=self.receivetext.yview)
        self.receivetext.grid(row=0, column=0, sticky=tk.N + tk.S + tk.E + tk.W)
        self.receivetext.config(yscrollcommand=receivesb.set)
#         receivelb = tk.Listbox(receivegroup)
#         receivelb.grid(row=0, column=0,sticky=tk.N+tk.S+tk.E+tk.W)
#         发送Frame
        sendgroup = tk.LabelFrame(self.tab3, text="发送区")
        sendgroup.grid(row=0, column=4, columnspan=2, sticky=tk.N + tk.S + tk.E + tk.W)
#         发送键
        sendbutton = ttk.Button(self.tab3, text='发送', command=self.SendData)
        sendbutton.grid(row=1, column=4, sticky=tk.E)
#         发送输入框
        sendgroup.rowconfigure(0, weight=1)
        sendgroup.columnconfigure(0, weight=1)
        inputbuf = tk.Entry(self.tab3, width=15)
        inputbuf.grid(row=1, column=4, sticky=tk.W)
#         发送显示区
        inputtext = tk.Text(sendgroup)
        inputtext.grid(row=0, column=0, sticky=tk.N + tk.S + tk.E + tk.W)
        inputsb = tk.Scrollbar(inputtext)
        inputsb.pack(side=tk.RIGHT, fill=tk.Y)
        inputsb.config(command=inputtext.yview)
        inputtext.config(yscrollcommand=inputsb.set)
#         速率选择
        speedgroup = tk.LabelFrame(self.tab3, text="接收速率选择")
        speedgroup.grid(row=1, column=3, columnspan=1, sticky=tk.W)
        speedgroup.rowconfigure(0)
        speedgroup.rowconfigure(1)
        
        self.radiovalue = tk.IntVar()
        self.radiovalue.set(0)     
        tk.Radiobutton(speedgroup, variable=self.radiovalue, text='低速：接收区显示数据', value=0).grid()
        tk.Radiobutton(speedgroup, variable=self.radiovalue, text='高速：数据存储在txt中', value=1).grid()

#         inputlb = tk.Listbox(sendgroup)
#         inputlb.grid(row=0, column=0,sticky=tk.N+tk.S+tk.E+tk.W)

    def DrawSensor(self):
        pass
    
    def SendData(self):
        print self.radiovalue.get()
    
    def pause(self):
        snifferthread = self.menu.uartform.snifferthread
        try:
            snifferthread.thread_stop = True
        except NameError:
            tkmes.showwarning("错误", "串口未启动!")
        time.sleep(1)
        self.menu.snifferthread.uart.close()
  
    def restart(self):
        snifferthread = self.menu.uartform.snifferthread
        try:
            self.menu.snifferthread.openuart()
            snifferthread.thread_stop = False
            snifferthread.data = []
            self.menu.uartform.snifferthread.openfile()
#             uartthread.openfile()
        except NameError:
            tkmes.showwarning("错误", "串口未启动!")
   
    def updatetext(self, chars, type):
        try:
            self.receivetext.insert(1.0, chars)
        except:
            print "6"
        
    def cleartext(self):
        self.receivetext.delete(1.0, tk.END)
    
    def opentxt(self):
        self.pause()
        self.menu.uartform.snifferthread.closefile()
        print self.menu.uartform.txtfilname
        os.startfile(self.menu.uartform.txtfilname)
#         try:
#             self.menu.uartform.snifferthread.clsoefile()
#             print self.menu.uartform.txtfilname
#             os.startfile(self.menu.uartform.txtfilname)
#         except:
#             pass
     
#     识别界面   
    def Identify(self):
        self.statusbar = root.status
        
        self.tab4.rowconfigure(0, weight=60)
        self.tab4.rowconfigure(1, weight=1)
        self.tab4.columnconfigure(0, weight=1)
        self.tab4.columnconfigure(1, weight=1)
        self.tab4.columnconfigure(2, weight=1)
        self.tab4.columnconfigure(3, weight=1)
        self.tab4.columnconfigure(4, weight=1)
        self.datapathentry = tk.Entry(self.tab4)
        self.datapathentry.grid(row=1, column=0, sticky=tk.E + tk.W)
        self.datapathbutton = ttk.Button(self.tab4, text="选择文件", command=self.Selectdata)
        self.datapathbutton.grid(row=1, column=1, sticky=tk.W)
        self.dataopenbutton = ttk.Button(self.tab4, text="读取并识别文件", command=self.Opendata)
        self.dataopenbutton.grid(row=1, column=1, sticky=tk.E)
        self.dataidentifybutton = ttk.Button(self.tab4, text="识别", command=self.Identifydata)
#         self.dataidentifybutton.grid(row=1, column=2, sticky=tk.W)
        
#         self.dataautobutton = ttk.Button(self.tab4,text="自动",command = self.Autodata,bg="green")
#         self.dataautobutton.grid(row=1,column=2,sticky=tk.E)
        
        self.dataRPbutton = tk.Button(self.tab4, command=self.RPdata, background="red", text="开启自动识别")
        self.dataRPbutton.grid(row=1, column=3, sticky=tk.W)
        self.dataclearbutton = tk.Button(self.tab4, text="清屏", command=self.Cleardata)
        self.dataclearbutton.grid(row=1, column=3, sticky=tk.E, padx=70)
        
        
        receivegroup = tk.LabelFrame(self.tab4, text="识别结果")
        receivegroup.grid(row=0, column=0, columnspan=4, sticky=tk.N + tk.S + tk.E + tk.W)

        receivegroup.rowconfigure(0, weight=1)
        receivegroup.columnconfigure(0, weight=1)
   
        self.datacavas = tk.Canvas(receivegroup)
        self.datacavas.grid(row=0, column=0, sticky=tk.N + tk.S + tk.E + tk.W)
        self.cancassbx = tk.Scrollbar(self.datacavas, orient=tk.HORIZONTAL)
        self.cancassbx.pack(side=tk.BOTTOM, fill=tk.X)
        self.cancassbx.config(command=self.datacavas.xview)
        self.datacavas.config(xscrollcommand=self.cancassbx.set)
        
        cancassby = tk.Scrollbar(self.datacavas)
        cancassby.pack(side=tk.RIGHT, fill=tk.Y)
        cancassby.config(command=self.datacavas.yview)
        self.datacavas.config(yscrollcommand=cancassby.set)
        

        readgroup = tk.LabelFrame(self.tab4, text="数据读取")
        readgroup.grid(row=0, column=4, columnspan=2, sticky=tk.N + tk.S + tk.E + tk.W)

        readgroup.rowconfigure(0, weight=1)
        readgroup.columnconfigure(0, weight=1)

        self.datatext = tk.Text(readgroup)
        self.datatext.grid(row=0, column=0, sticky=tk.N + tk.S + tk.E + tk.W)
        
        inputsb = tk.Scrollbar(self.datatext)
        inputsb.pack(side=tk.RIGHT, fill=tk.Y)
        inputsb.config(command=self.datatext.yview)
        self.datatext.config(yscrollcommand=inputsb.set)

#   识别界面清空按钮    
    def Cleardata(self):
        for v in self.canvasidentifyline:  
            self.datacavas.delete(v)
        self.canvasidentifyline = []
        for v in self.canvasline:
            self.datacavas.delete(v)
        self.canvasline = []
        for v in self.canvasoval:
            self.datacavas.delete(v)
        self.canvasoval=[]
        self.datacavas.config(scrollregion=(0, 0, 0, 512))
        self.datatext.delete(0.0, tk.END)
        
#   暂停继续按钮    
    def RPdata(self):
        if(self.identifyuartopen == 0):
            tkmes.showerror("错误！", "串口没有打开，无法开启自动模式！\n请手动载入数据或打开串口！")
            return 
        self.identifythread = self.menu.uartform.identifythread
        if self.identifythread.thread_stop == False:
            self.identifythread.thread_stop = True
            self.dataRPbutton.configure(background="red", text="开启自动识别")
            self.dataidentifybutton.configure(state=tk.NORMAL)
            self.dataopenbutton.configure(state=tk.NORMAL)
        else:
            self.identifythread.thread_stop = False
            self.dataRPbutton.configure(background="green", text="停止自动识别")
            self.dataidentifybutton.configure(state=tk.DISABLED)
            self.dataopenbutton.configure(state=tk.DISABLED)
        
#   选择文件按钮
    def Selectdata(self):
        dlg = win32ui.CreateFileDialog(1)  # 1表示打开文件对话框
        dlg.SetOFNInitialDir('F:\\Graduate\\Test\\data\\')  # 设置打开文件对话框中的初始显示目录
        dlg.DoModal()
        self.datapath = dlg.GetPathName()  # 获取选择的文件名称
        self.datapathentry.delete(0, tk.END)
        self.datapathentry.insert(1, self.datapath)
    
       
#   显示数据图像按钮 
    def Opendata(self):
        data = []
        
        
#         self.datapath = "F:\\Graduate\\Test\\data\\1.txt"
        try:
            self.data_file_object = open(self.datapath)
        except:
            tkmes.showerror("错误！", "未能找到文件，请检查文件路径！")
            return
        try:
            all_the_text = self.data_file_object.read()
        finally:
            self.data_file_object.close()
        datastr = all_the_text.split(" ")
        data = []
        #删除遗留图像
        for v in self.canvasidentifyline:  
            self.datacavas.delete(v)
        self.canvasidentifyline = []
        for v in self.canvasline:
            self.datacavas.delete(v)
        self.canvasline = []
        for v in self.canvasoval:
            self.datacavas.delete(v)
        self.canvasoval=[]
        
        for v in datastr:
            if v != "":
                data.append(int(v, 16))
            
        if "sensor" in self.datapath:
            self.ADValue = []
            for value in range(len(data)):
                if data[value] == 0x7D:
                    self.ADValue.append(data[value + 1] << 8 | data[value + 2])
            self.dataidentifybutton.configure(state=tk.NORMAL)
        elif "identify" in self.datapath:
            self.dataidentifybutton.configure(state=tk.DISABLED)
            
            self.ADValue = []
            databuf=[]
            count =0
            for value in range(len(data)):
                if data[value] == 0x7D:
                    # 不是采集5位需要改的
                    self.ADValue.append(data[value + 1] << 8 | data[value + 2])
                    self.ADValue.append(data[value + 3] << 8 | data[value + 4])
                    self.ADValue.append(data[value + 5] << 8 | data[value + 6])
                    self.ADValue.append(data[value + 7] << 8 | data[value + 8])
                    self.ADValue.append(data[value + 9] << 8 | data[value + 10])
                    databuf.append(data[value + 1] << 8 | data[value + 2])
                    databuf.append(data[value + 3] << 8 | data[value + 4])
                    databuf.append(data[value + 5] << 8 | data[value + 6])
                    databuf.append(data[value + 7] << 8 | data[value + 8])
                    databuf.append(data[value + 9] << 8 | data[value + 10])
                    self.Drawonce(count = count,value=databuf)
                    count+=5
                    databuf=[]
        self.datatext.delete(0.0, tk.END)
        i = 0
        for v in self.ADValue:  
            self.datatext.insert(tk.END, str(i) + ":" + str(v) + "\n")
            i += 1
        
        offset = 10
        # 画布宽度为data长度  高度为512
        self.datacavas.config(scrollregion=(0, 0, len(self.ADValue*offset), 512))
        
        
        xm = 0
        ym = 0
        j = 0
        if "sensor" in self.datapath:
            for v in self.ADValue:
                j += 1
                if(v > 1024):
                    v = self.ADValue[j - 2]
                y = 512 - v / 2
                self.canvasline.append(self.datacavas.create_line(xm, ym, xm + offset, y, fill="red"))
                xm += offset
                ym = y
            self.Identifydata()
        self.datacavas.bind("<Button-1>", self.Showdetaildata)
        self.datacavas.bind("<B1-Motion>", self.Showdetaildata)
        

    def Drawonce(self, count, value):
        
        offset = 10
        for v in value:
            if(v > 1024):
                v = 1024
            y = 512 - v / 2
            xm = count * offset
            ym = self.drawonceym
            
            self.canvasline.append(self.datacavas.create_line(xm, ym, xm + offset, y, fill="red"))
            self.drawonceym = y
            count += 1
        self.datacavas.config(scrollregion=(0, 0, count * offset, 512))
        self.datacavas.xview(tk.MOVETO, 1.0)
        self.Identifyonce(Magnet_Value=value, x=xm, y=ym)

#     求斜率的算法
    def Slop(self,Magnet_Value):
        # 不是采集5位需要改的
        Ave_Slop = ((Magnet_Value[1] - Magnet_Value[0])) + ((Magnet_Value[2] - Magnet_Value[0])) / 2 + ((Magnet_Value[3] - Magnet_Value[0])) / 3 + ((Magnet_Value[4] - Magnet_Value[0])) / 4
        Ave_Slop = Ave_Slop / 5
        return Ave_Slop
# 自动模式使用的识别
    def Identifyonce(self, Magnet_Value, x, y):
        Ave_Slop = self.Slop(Magnet_Value)
        if(Ave_Slop > 10):
            self.canvasoval.append(self.datacavas.create_oval(x - 10, y - 10, x + 10, y + 10, fill="blue"))
        elif(Ave_Slop < -10):
            self.canvasoval.append(self.datacavas.create_oval(x - 10, y - 10, x + 10, y + 10, fill="yellow"))

# 需要较多空间的识别
    def Identifydata(self):
        offset = 10
        width = 8
        threshold = 100
        thresholdk = 10
        self.ADindexP = []
        self.ADindexvalueP = []
        self.ADindexN = []
        self.ADindexvalueN = []
        i = 0
        if len(self.ADValue) == 0:
            tkmes.showerror("错误！", "没有数据！")
            return
        if("identify" in self.datapath):
            
            return
        ''' 识别算法1 检测跳变沿
        while (i<len(self.ADValue)-offset):
            if(((self.ADValue[i] - self.ADValue[i+offset]>threshold)and(self.ADValue[i] - self.ADValue[i+offset]<4096)) or ((self.ADValue[i] - self.ADValue[i+offset]<-threshold)and(self.ADValue[i] - self.ADValue[i+offset]>-4096))):
                print self.ADValue[i]
                print self.ADValue[i+offset]
                print i 
                print "\n"
                self.ADindex.append(i+offset/2)
                self.ADindexvalue.append(self.ADValue[i+offset/2])
                i=i+offset
            else:
                i+=1
        '''
        '''识别算法2 检测斜率
        '''
        while (i < len(self.ADValue) - width):
            if(self.ADValue[i] < 4096 and self.ADValue[i + width] < 4096):
                if((self.ADValue[i + width] - self.ADValue[i]) / width > thresholdk):  # 检测上升沿
                    j = i
                    i += 1
                    while((self.ADValue[i + width] - self.ADValue[i]) / (width) > thresholdk):  # 一直计算到上升沿结束
                        i += 1
                    if(i - j > 5):  # 上升沿长度要足够长
                        self.ADindexP.append(i)
                        self.ADindexvalueP.append(i)
                elif(((self.ADValue[i] - self.ADValue[i + width]) / width > thresholdk)):  # 检测下降沿
                    j = i
                    i += 1
                    while((self.ADValue[i] - self.ADValue[i + width]) / width > thresholdk):  # 一直计算到下降沿结束
                        i += 1
                    if(i - j > 5):  # 下降沿长度要足够长
                        self.ADindexN.append(i)
                        self.ADindexvalueN.append(i)
            i += 1


        for v in self.canvasidentifyline:  
                self.datacavas.delete(v)
        self.canvasidentifyline = []
        for v in self.ADindexP:
            self.canvasidentifyline.append(self.datacavas.create_line(v*offset, 0, v*offset, 512, fill="orange"))
        for v in self.ADindexN:
            self.canvasidentifyline.append(self.datacavas.create_line(v*offset, 0, v*offset, 512, fill="purple"))
        
# 绿色竖线查看数据               
    def Showdetaildata(self, event):
        offset=10
        x1 = event.x + int(self.cancassbx.get()[0] * len(self.ADValue)*offset)
        if(x1 >= 0 and x1 <= len(self.ADValue)*offset):
            for v in self.cavasverticalline:  
                self.datacavas.delete(v)
            self.cavasverticalline = []
            self.cavasverticalline.append(self.datacavas.create_line(x1, 0, x1, 512, fill="green"))
            self.statusbar.setdata("%s", "X:" + str(x1/offset) + ",Y:" + str(self.ADValue[x1/offset]))
            self.datatext.see(float(str(x1/offset) + ".0"))

        
if __name__ == '__main__':
    global root
    root = MainRoot()
    root.rootmenu.show()
    root.ShowData()  # 数据显示
    root.NetStatus()  # 网络状态
    root.StopStatus()  # 停车状态
    root.NetSniffer()  # 网络抓包
    root.SysStatus()  # 状态栏
    root.Identify()

    root.mainloop()

    
