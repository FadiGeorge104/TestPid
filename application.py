import sys
import serial
from serial import Serial
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel
from PyQt5.QtCore import QTimer

ser = serial.Serial('COM3', 9600)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Arduino Direction Control")
        self.setGeometry(100, 100, 300, 200)

        # Create a label to display the current direction
        self.direction_label = QLabel(self)
        self.direction_label.setGeometry(0, 0, 200, 50)
        self.direction_label.setText("Current direction: None")

        # Create buttons for each direction
        self.left_button = QPushButton("Left", self)
        self.left_button.setGeometry(0, 100, 100, 50)
        self.left_button.clicked.connect(lambda: self.send_direction("a"))

        self.right_button = QPushButton("Right", self)
        self.right_button.setGeometry(200, 100, 100, 50)
        self.right_button.clicked.connect(lambda: self.send_direction("d"))

        self.stop_button = QPushButton("Stop", self)
        self.stop_button.setGeometry(100, 100, 100, 50)
        self.stop_button.clicked.connect(lambda: self.send_direction("x"))

        self.up_button = QPushButton("Up", self)
        self.up_button.setGeometry(100, 50, 100, 50)
        self.up_button.clicked.connect(lambda: self.send_direction("s"))

        self.down_button = QPushButton("Down", self)
        self.down_button.setGeometry(100, 150, 100, 50)
        self.down_button.clicked.connect(lambda: self.send_direction("w"))

    def send_direction(self, direction):
        # Send the direction to the Arduino via serial communication
        ser.write(direction.encode())
        # Update the direction label to reflect the current direction
        self.direction_label.setText(f"Current direction: {direction}")

    def start_up_timer(self):
        # Start the timer for sending the "up" command repeatedly
        self.up_timer = QTimer()
        self.up_timer.timeout.connect(lambda: self.send_direction("w"))
        self.up_timer.start(100)  # Change the interval (in ms) based on your needs

    def stop_up_timer(self):
        # Stop the timer for sending the "up" command repeatedly
        self.up_timer.stop()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
