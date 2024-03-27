
import cv2
from gaze_tracking import GazeTracking
import serial
import time

# Blink threshold for avoiding the unnecessary forward motion.
# Count will count the blinking and more than 15 count will drive the Wheelchair.
#serial setup




blink_thresh = 5
count = 0


gaze = GazeTracking()
webcam = cv2.VideoCapture(0)

while True:
    # new frame from the webcam.
    _, frame = webcam.read()
    # sending the frame to the gazeTracking to analyze.
    gaze.refresh(frame)

    frame = gaze.annotated_frame()
    text = ""

    if gaze.is_blinking():
        text = "Blinking"
        count += 1
        if blink_thresh < count:
            text = "Half Closed"
    elif gaze.is_right():
        text = "Looking right"
    elif gaze.is_left():
        text = "Looking left"
    elif gaze.is_center():
        text = "Looking center"
        count = 0
    else:
        count = 0

    cv2.putText(frame, text, (90, 60), cv2.FONT_HERSHEY_DUPLEX, 1.6, (147, 58, 31), 2)

    left_pupil = gaze.pupil_left_coords()
    right_pupil = gaze.pupil_right_coords()
    cv2.putText(frame, "Left pupil:  " + str(left_pupil), (90, 130), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
    cv2.putText(frame, "Right pupil: " + str(right_pupil), (90, 165), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)

    cv2.imshow("GazeRide", frame)

    if cv2.waitKey(1) == 27:
        break

webcam.release()
cv2.destroyAllWindows()
