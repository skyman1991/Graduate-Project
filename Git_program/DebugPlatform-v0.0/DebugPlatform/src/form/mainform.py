#coding=utf-8
import Tkinter as tk
import ttk
import user
from cgitb import text
import uartsettingsform

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
        
    def SysStatus(self):
        self.appFrame.SysStatus()  
        self.status = StatusBar(self)
        self.status.pack(side='bottom', fill='x')
        
class MenuBar(tk.Menu):
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
        uartform = uartsettingsform.UartRoot()
        uartform.mainloop()

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
         
        self.add(self.tab1, text = "数据显示")
        self.add(self.tab2, text = "网络状态")
        self.add(self.tab3, text = "系统状态")
    def ShowData(self):
        label1 = ttk.Label(self.tab1,text="数据显示").grid()
    
    def NetStatus(self):
        label2 = ttk.Label(self.tab2,text="网络状态").grid()
    
    def SysStatus(self):
        label3 = ttk.Label(self.tab3,text="系统状态").grid()
        
if __name__ == '__main__':
    mainvalue = 2
    global root 
    root = MainRoot()
    root.ShowData()
    root.NetStatus()
    root.SysStatus()
    root.status.set("%s",'sdf')
    root.mainloop()
    
