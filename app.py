from flask import Flask, request, render_template
import numpy as np
import joblib

app = Flask(__name__)

# Load the pre-trained model
model = joblib.load('car_price_prediction_model.pkl')

@app.route('/')
def home():
    return render_template('index.html')  # Assuming you have a form in index.html for input

@app.route('/predict', methods=['POST'])
def predict():
    # Get input data from the form
    year = int(request.form['year'])
    present_price = float(request.form['present_price'])
    kms_driven = int(request.form['kms_driven'])
    fuel_type = int(request.form['fuel_type'])
    seller_type = int(request.form['seller_type'])
    transmission = int(request.form['transmission'])
    owner = int(request.form['owner'])

    # Prepare input array for model prediction
    input_data = np.array([[year, present_price, kms_driven, fuel_type, seller_type, transmission, owner]])

    # Get the prediction from the model
    predicted_price = model.predict(input_data)[0]

    # Render the result in 'result.html'
    return render_template('result.html', prediction_text=f"Estimated Selling Price: ₹{predicted_price:.2f} Lakhs")

if __name__ == "__main__":
    app.run(debug=True)
