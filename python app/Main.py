import time
import threading
from PyQt5 import QtWidgets, uic
import socket

app = QtWidgets.QApplication([])

ui = uic.loadUi("design.ui")

s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
s.connect(('98:D3:21:F7:B4:95', 1))

def get_Data(data):
    while True:
        receivedData = s.recv(1)              
        if receivedData != b'0':
            ui.progressBar.setValue(int.from_bytes(receivedData, "big"))
        time.sleep(0.2)
         


thr = threading.Thread(target=get_Data, args=(str(time.time()),), name="b")
thr.start()


def redSliderControl(value):
    s.send(b'1')
    s.send(value.to_bytes(1, 'big'))

def greenSliderControl(value):
    s.send(b'3')
    s.send(value.to_bytes(1, 'big'))

def yellowSliderControl(value):
    s.send(b'4')
    s.send(value.to_bytes(1, 'big'))

ui.redColorSlider.valueChanged.connect(redSliderControl)
ui.greenColorSlider.valueChanged.connect(greenSliderControl)
ui.yellowColorSlider.valueChanged.connect(yellowSliderControl)

ui.show()
app.exec()