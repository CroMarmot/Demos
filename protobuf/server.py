#!/usr/bin/env python3
from flask import Flask, request
from out.protodemo_pb2 import Add1Req, Add1Resp
app=Flask(__name__)

@app.route('/add_1_api',methods=["POST"])
def add_1_api():
    req= Add1Req()
    req.ParseFromString(request.get_data())
    print("val:", req.val)

    resp = Add1Resp()
    resp.result = req.val + 1
    return resp.SerializeToString(), 200

if __name__ == '__main__':
    app.run("127.0.0.1", port=6666)
