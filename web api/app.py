from flask import Flask, render_template, Response, request
import cv2

app = Flask(__name__)

camera = cv2.VideoCapture(1)  # use 0 for web camera
#  for cctv camera use rtsp://username:password@ip_address:554/user=username_password='password'_channel=channel_number_stream=0.sdp' instead of camera
# for local webcam use cv2.VideoCapture(0)

def gen_frames():  # generate frame by frame from camera
    while True:
        # Capture frame-by-frame
        success, frame = camera.read()  # read the camera frame
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')  # concat frame one by one and show result


@app.route('/video_feed')
def video_feed():
    #Video streaming route. Put this in the src attribute of an img tag
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/')
def index():
    """Video streaming home page."""
    if request.method == 'POST':
        if request.form.get('action1') == 'MODE1':
            pass  # do something
        elif request.form.get('action2') == 'MODE2':
            pass  # do something else
        elif request.form.get('action3') == 'MODE3':
            pass  # do something else
        elif request.form.get('action4') == 'MODE4':
            pass  # do something else
        else:
            pass  # unknown
    elif request.method == 'GET':
        return render_template('index.html', form="form")
    return render_template("index.html")


if __name__ == '__main__':
    app.run(debug=True)