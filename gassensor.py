from flask import Flask, request

app = Flask(__name__)

@app.route('/gassensor/data', methods=['POST'])
def post():
    gas = request.form.get("gas")
    print(f"Received gas value: {gas}")
    if gas is not None:
        return 'Sensor gas data received', 200
    else:
        return 'Failed to receive data', 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
