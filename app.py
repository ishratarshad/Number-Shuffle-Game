from flask import Flask, render_template, request, jsonify
import random

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/game', methods=['POST'])
def game():
    size = int(request.form.get('boardSize', 4))  # Default to 4x4 if no size is selected
    return render_template('game.html', size=size)

if __name__ == '__main__':
    app.run(debug=True)
