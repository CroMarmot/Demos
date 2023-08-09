# Quick Start

[Download protobuf compiler](https://protobuf.dev/downloads/)

Python3

```sh
pip install -r requirements.txt

protoc --python_out=./out/ protodemo.proto
protoc --pyi_out=./out/ protodemo.proto

python3 server.py
python3 client.py
```

TS

```sh
yarn
protoc --plugin=./node_modules/.bin/protoc-gen-ts_proto --ts_proto_out=./out/ ./protodemo.proto

npx ts-node index.ts
```

## From Scratch

Install `protoc`

python:

```
pip install flask requests
```

TS:

```
yarn init
yarn add @types/node ts-node typescript
yarn add --dev axios ts-proto
```
