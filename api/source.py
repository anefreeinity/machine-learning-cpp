from flask import Flask, request
from flask_cors import CORS
from ctypes import cdll, c_int
import platform
import sys

os_name = platform.system()
lib_path = '../shared/hand_written_digit_lib'

if(os_name == 'Linux'):
    lib = cdll.LoadLibrary(f"{lib_path}.so")
elif(os_name == 'Windows'):
    lib = cdll.LoadLibrary(f"{lib_path}.dll")
elif(os_name == 'Darwin'):
    lib = cdll.LoadLibrary(f"{lib_path}.dylib")
else:
    print("Unsupported shared OS")
    sys.exit(1)

class PredictDigit(object):
    def __init__(self):
        pass
    def bar(self, nums):
        pixels = (c_int * len(nums))(*nums)
        return lib.HandWrittenDigitShared_C(pixels, len(nums))

app = Flask(__name__)
CORS(app)

@app.route('/api/hello', methods=['GET'])
def hello():
    return {'message': 'Hello, World!'}

@app.route('/api/predict', methods=['POST'])
def predict():
    data = request.get_json()
    if(len(data) != 784):
        return {'error': 'Invalid data size'}, 400
    f = PredictDigit()
    PredictedDigit = f.bar(data)
    if(PredictedDigit == -1):
        return {'error': 'Invalid data size dll error'}, 400
    return {'predictedDigit': PredictedDigit}, 200

if __name__ == '__main__':
    app.run(debug=True)
