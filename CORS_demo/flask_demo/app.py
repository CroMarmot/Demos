#!/usr/bin/env python3
from flask import Flask
from flask_cors import CORS

app = Flask(__name__)
# CORS(app) <-----------------------

@app.route("/")
def hello_world():
  print("execute")
  return "<p>Hello, World!</p>"

@app.route("/xxx",methods = ['POST'])
def post_test():
  print("execute")
  return "yyyyyy"

app.run(host='0.0.0.0', port=5000, debug=True)

