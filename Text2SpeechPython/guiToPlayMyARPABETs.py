from tkinter import *
#from ttk import *
from tkinter.ttk import *
import subprocess  #to play sound # https://www.youtube.com/watch?v=OMP3EozC5Zw

'''
import re
import wave
import pyaudio
import _thread
import time
#https://stackoverflow.com/questions/307305/play-a-sound-with-python
import time, wave, pymedia.audio.sound as sound


https://stackoverflow.com/questions/3080918/why-cant-i-use-ttk-in-python

There is nothing wrong with the case. As other answer specified - its Tkinter in Python 2.x and tkinter in Python 3.x version.

In addition ttk was a separate module in Python 2.x and its a submodule of Tkinter in Python 3.x

So in Python 2.x you would import ttk as

from Tkinter import *
import ttk

And in Python 3.x you would import ttk as

from tkinter import *
from tkinter.ttk import *

or

from tkinter import ttk

'''


def rand_func(eff=None,a=1,b=2,c=3):
    print (a+b+c)

'''
def _play_audio(sound):
    f = wave.open("sounds/"+sound+".wav", 'rb')
    #f= wave.open( 'YOUR FILE NAME', 'rb' )
    sampleRate= f.getframerate()
    channels= f.getnchannels()
    format= sound.AFMT_S16_LE
    snd= sound.Output( sampleRate, channels, format )
    s= f.readframes( 300000 )
    snd.play( s )
'''

#def play_ARPAbet(eff=None,sound="Hi"):
def play_ARPAbet(event):
    #https://stackoverflow.com/questions/26765218/get-the-text-of-a-button-widget
    #sound = event.widget['text']
    sound = event.widget.cget('text')
    print ('fn: ', sound)
    #delay = 0.145
    #_play_audio(sound)#, delay)
    soundfullpath = "sounds/"+sound+".wav"
    subprocess.call(["afplay",soundfullpath])

root = Tk()
root.configure(background='DimGray')
root.geometry('600x200')
root.resizable(width=False, height=False)

#scheduledimage=PhotoImage("AnimatedGIF_Art_mindWarping.gif")
note = Notebook(root)

tab1 = Frame(note)
tab2 = Frame(note)
tab3 = Frame(note)
tab4 = Frame(note)
Button(tab4, text='Exit', command=root.destroy).pack(padx=100, pady=100)

#note.add(tab1, text = "Vowels",image=scheduledimage, compound=TOP)
note.add(tab1, text = "Vowels")
note.add(tab2, text = "Consonants")
note.add(tab3, text = "Test1")
note.add(tab4, text = "Test2")
note.pack(fill=BOTH, expand=True)
#note.pack()

#=========== kp: Filling tab3 with some test elements ======
colours = ['red','green','white','yellow','blue']
labels = []
entries = []
r = 0
for c in colours:
    #Label(text=c, relief=RIDGE,width=15).grid(row=r,column=0)
    #Entry(bg=c, relief=SUNKEN,width=10).grid(row=r,column=1)
    labels.append(Label(tab3,text=c, relief=RIDGE,width=15))
    labels[r].grid(row=r,column=0)
    entries.append(Entry(tab3, width=10))
    entries[r].grid(row=r,column=1)
    #entries[r].config(bg=c, relief=SUNKEN, width=10)
    r = r + 1


#=========== kp: Filling tab1 with buttons for the Vowels ======
vowels = ['AA','AE','AH','AO','AW','AX','AXR','AY',
          'EH','ER','EY','IH','IX','IY','OW','OY','UH','UW','UX']
# missing sounds for now: EY, IH
print(len(vowels))
vbuttons = []
rv = 0
cv = 0
iv = 0
for vo in vowels:
    rv = int(iv/6)
    cv = int(iv%6)
    #print iv
    #print(rv,cv)

    #vbuttons.append(Button(tab1,command=lambda:play_ARPAbet(None,vowels[iv])))
    vbuttons.append(Button(tab1))#,command=play_ARPAbet))#, text=v, relief=RIDGE))
    vbuttons[iv].bind('<Button-1>', play_ARPAbet)
    vbuttons[iv]["text"] = vo
    #vbuttons[iv].bind('<Button-1>',play_ARPAbet(None,vo))
    #vbuttons[iv]["relief"] = RIDGE
    vbuttons[iv].grid(row=rv,column=cv)
    iv = iv + 1



#=========== kp: Filling tab1 with buttons for the Consonants ======
consonants = ['B','CH','D','DH','DX','EL','EM','EN','F','G','HH','JH','K','L','M',
              'N','NG','NX','P','Q','R','S','SH','T','TH','V','W','WH','Y','Z','ZH']
print(len(consonants))

cbuttons = []
rc = 0
cc = 0
ic = 0
for co in consonants:
    rc = int(ic/6)
    cc = int(ic%6)
    #print(rc,cc)
    cbuttons.append(Button(tab2))#, text=v, relief=RIDGE))
    cbuttons[ic].bind('<Button-1>', play_ARPAbet)
    cbuttons[ic]["text"] = co
    #cbuttons[iv]["relief"] = RIDGE
    cbuttons[ic].grid(row=rc,column=cc)
    ic = ic + 1


root.mainloop()
exit() #kp: not necessary
