#!/usr/bin/env python3
import requests
from out.protodemo_pb2 import Add1Req, Add1Resp

if __name__ == '__main__':
    req = Add1Req()
    req.val = 100
    print(req.SerializeToString())
    response = requests.post("http://127.0.0.1:6666/add_1_api", data=req.SerializeToString())

    resp = Add1Resp()
    resp.ParseFromString(response.content)
    assert(resp.result == 101)
    print("SUCCESS")
